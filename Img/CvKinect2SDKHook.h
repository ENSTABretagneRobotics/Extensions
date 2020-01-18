#ifndef CVKINECT2SDKHOOK_H
#define CVKINECT2SDKHOOK_H

// To use this way :
//#pragma push_macro("cvCreateFileCapture")
//#pragma push_macro("cvSetCaptureProperty")
//#pragma push_macro("cvGetCaptureProperty")
//#pragma push_macro("cvQueryFrame")
//#pragma push_macro("cvReleaseCapture")
//#include "CvKinect2SDKHook.h"
// Your code (with cvCreateFileCapture("Kinect2Color"), cvCreateFileCapture("Kinect2Depth") or cvCreateFileCapture("Kinect2Infrared"))...
//#pragma pop_macro("cvReleaseCapture")
//#pragma pop_macro("cvQueryFrame")
//#pragma pop_macro("cvGetCaptureProperty")
//#pragma pop_macro("cvSetCaptureProperty")
//#pragma pop_macro("cvCreateFileCapture")

#ifndef INCLUDE_HEADERS_OUTSIDE_CVKINECT2SDKHOOK
#include <Kinect.h>
#pragma comment(lib, "Kinect20.lib")

#include "opencv2/core/version.hpp"

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#if (CV_MAJOR_VERSION == 3)
#include "opencv2/imgcodecs/imgcodecs_c.h"
#include "opencv2/videoio/videoio_c.h"
#endif // (CV_MAJOR_VERSION == 3)
#if (CV_MAJOR_VERSION >= 4)
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include "opencv2/videoio/legacy/constants_c.h"
#include "opencv2/videoio/videoio_c.h"
#endif // (CV_MAJOR_VERSION >= 4)

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#if (CV_MAJOR_VERSION >= 3)
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#endif // (CV_MAJOR_VERSION >= 3)
#endif // !INCLUDE_HEADERS_OUTSIDE_CVKINECT2SDKHOOK

#define KINECT_TYPE_COLOR 16
#define KINECT_TYPE_DEPTH 32
#define KINECT_TYPE_INFRARED 64

struct KINECT
{
	int type;
	IKinectSensor* kinectSensor;
	IColorFrameReader* colorFrameReader;
	IDepthFrameReader* depthFrameReader;
	IInfraredFrameReader* infraredFrameReader;
	IplImage* colorimg;
	IplImage* depthimg;
	IplImage* infraredimg;
};
typedef struct KINECT KINECT;

template<class Interface>
inline void SAFERELEASEKINECT2SDK(Interface *& pInterfaceToRelease) 
{
	if (pInterfaceToRelease != nullptr) 
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = nullptr;
	}
}

inline void _ReleaseKinect2SDK(KINECT** ppKinect)
{
	if (*ppKinect)
	{
		if ((*ppKinect)->infraredimg) 
		{
			cvReleaseImage(&(*ppKinect)->infraredimg);
			(*ppKinect)->infraredimg = NULL;
		}
		if ((*ppKinect)->depthimg) 
		{
			cvReleaseImage(&(*ppKinect)->depthimg);
			(*ppKinect)->depthimg = NULL;
		}
		if ((*ppKinect)->colorimg) 
		{
			cvReleaseImage(&(*ppKinect)->colorimg);
			(*ppKinect)->colorimg = NULL;
		}
		SAFERELEASEKINECT2SDK((*ppKinect)->infraredFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->depthFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->colorFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->kinectSensor);
		(*ppKinect)->type = 0;
		free(*ppKinect);
		*ppKinect = NULL;
	}
}

inline void _ProcessIncomingColorDataKinect2SDK(KINECT* pKinect) 
{ 
	IColorFrame *data = nullptr;
	IFrameDescription *frameDesc = nullptr;
	HRESULT hr = E_FAIL;
	RGBQUAD *colorBuffer = nullptr;

	hr = pKinect->colorFrameReader->AcquireLatestFrame(&data); 
	if (SUCCEEDED(hr)) hr = data->get_FrameDescription(&frameDesc);
	if (SUCCEEDED(hr)) {
		int height = 1080, width = 1920;
		if (SUCCEEDED(frameDesc->get_Height(&height)) && 
			SUCCEEDED(frameDesc->get_Width(&width))) {
				colorBuffer = new RGBQUAD[height * width];
				hr = data->CopyConvertedFrameDataToArray(height * width * sizeof(RGBQUAD),
					reinterpret_cast<BYTE*>(colorBuffer), ColorImageFormat_Bgra);
				if (SUCCEEDED(hr)) {
					cv::Mat img1(height, width, CV_8UC4, reinterpret_cast<void*>(colorBuffer));
					IplImage im = img1;
					cvCvtColor(&im, pKinect->colorimg, CV_BGRA2BGR);
				}
		}
	}
	if (colorBuffer != nullptr) {
		delete[] colorBuffer;
		colorBuffer = nullptr;
	}
	SAFERELEASEKINECT2SDK(data);
}

inline void _ProcessIncomingDepthDataKinect2SDK(KINECT* pKinect) 
{
	IDepthFrame *data = nullptr;
	IFrameDescription *frameDesc = nullptr;
	HRESULT hr = E_FAIL;
	UINT16 *depthBuffer = nullptr;
	USHORT nDepthMinReliableDistance = 0;
	USHORT nDepthMaxReliableDistance = 0;
	int height = 424, width = 512;

	hr = pKinect->depthFrameReader->AcquireLatestFrame(&data);
	if (SUCCEEDED(hr)) hr = data->get_FrameDescription(&frameDesc);
	if (SUCCEEDED(hr)) hr = data->get_DepthMinReliableDistance(
		&nDepthMinReliableDistance);
	if (SUCCEEDED(hr)) hr = data->get_DepthMaxReliableDistance(
		&nDepthMaxReliableDistance);

	if (SUCCEEDED(hr)) {
		if (SUCCEEDED(frameDesc->get_Height(&height)) &&
			SUCCEEDED(frameDesc->get_Width(&width))) {
				depthBuffer = new UINT16[height * width];
				hr = data->CopyFrameDataToArray(height * width, depthBuffer);
				if (SUCCEEDED(hr)) {
					cv::Mat depthMap = cv::Mat(height, width, CV_16U, depthBuffer);
					cv::Mat img0 = cv::Mat::zeros(height, width, CV_8UC1);
					cv::Mat img0_threshold;

					//double scale = -255.0/(nDepthMaxReliableDistance-nDepthMinReliableDistance);
					double scale = -255.0/8000.0;
					depthMap.convertTo(img0, CV_8UC1, scale, 255.0);
					cv::threshold(img0, img0_threshold, 254, 255, CV_THRESH_BINARY_INV);
					cv::bitwise_and(img0, img0_threshold, img0);

					////double scale = 255.0/(nDepthMaxReliableDistance-nDepthMinReliableDistance);
					//double scale = 255.0/8000.0;
					//depthMap.convertTo(img0, CV_8UC1, scale, 0);
					//cv::threshold(img0, img0_threshold, 254, 255, CV_THRESH_BINARY_INV);
					//cv::bitwise_and(img0, img0_threshold, img0);

					//cv::applyColorMap(img0, img0, cv::COLORMAP_JET);

					IplImage im = img0;
					cvCvtColor(&im, pKinect->depthimg, CV_GRAY2BGR);
				}
		}
	}
	if (depthBuffer != nullptr) {
		delete[] depthBuffer;
		depthBuffer = nullptr;
	}
	SAFERELEASEKINECT2SDK(data);
}

inline void _ProcessIncomingInfraredDataKinect2SDK(KINECT* pKinect) 
{ 
	IInfraredFrame *data = nullptr;
	IFrameDescription *frameDesc = nullptr;
	HRESULT hr = E_FAIL;
	UINT16 *infraredBuffer = nullptr;
	int height = 424, width = 512;

	hr = pKinect->infraredFrameReader->AcquireLatestFrame(&data); 
	if (SUCCEEDED(hr)) hr = data->get_FrameDescription(&frameDesc);
	if (SUCCEEDED(hr)) {
		if (SUCCEEDED(frameDesc->get_Height(&height)) && 
			SUCCEEDED(frameDesc->get_Width(&width))) {
				infraredBuffer = new UINT16[height * width];
				hr = data->CopyFrameDataToArray(height * width, infraredBuffer);
				if (SUCCEEDED(hr)) {
					cv::Mat infraredMap = cv::Mat(height, width, CV_16U, infraredBuffer);
					cv::Mat img0 = cv::Mat::zeros(height, width, CV_8UC1);
					cv::Mat img0_gamma;
					double scale = 1.0/65535.0;
					double gain = 1.0, gamma = 0.32;
					infraredMap.convertTo(img0_gamma, CV_64FC1, scale);
					pow(img0_gamma, gamma, img0_gamma);
					img0_gamma.convertTo(img0, CV_8UC1, gain*255.0);
					//cv::applyColorMap(img0, img0, cv::COLORMAP_BONE);
					IplImage im = img0;
					cvCvtColor(&im, pKinect->infraredimg, CV_GRAY2BGR);
				}
		}
	}
	if (infraredBuffer != nullptr) {
		delete[] infraredBuffer;
		infraredBuffer = nullptr;
	}
	SAFERELEASEKINECT2SDK(data);
}

inline CvCapture* cvCreateFileCaptureKinect2SDK(const char* filename)
{
	KINECT* pKinect = NULL;
	HRESULT hr = E_FAIL;

	if (strncmp(filename, "Kinect2", strlen("Kinect2")) == 0)
	{
		// Code common to all Kinect 2 sources.
		pKinect = (KINECT*)calloc(1, sizeof(KINECT));
		if (!pKinect) 
		{
			printf("calloc() failed.\n");
			return NULL;
		}
		hr = GetDefaultKinectSensor(&pKinect->kinectSensor);
		if (FAILED(hr)||!pKinect->kinectSensor) 
		{
			printf("GetDefaultKinectSensor() failed.\n");
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		hr = pKinect->kinectSensor->Open();
		if (FAILED(hr))
		{
			printf("IKinectSensor::Open() failed.\n");
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
	}
	if (strncmp(filename, "Kinect2Color", strlen("Kinect2Color")) == 0)
	{
		IColorFrameSource* colorFrameSource = nullptr;
		hr = pKinect->kinectSensor->get_ColorFrameSource(&colorFrameSource);
		if (FAILED(hr))
		{
			printf("IKinectSensor::get_ColorFrameSource() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		hr = colorFrameSource->OpenReader(&pKinect->colorFrameReader);
		if (FAILED(hr)) 
		{
			printf("IColorFrameSource::OpenReader() failed.\n");
			SAFERELEASEKINECT2SDK(colorFrameSource);
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		SAFERELEASEKINECT2SDK(colorFrameSource);
		pKinect->colorimg = cvCreateImage(cvSize(1920,1080), IPL_DEPTH_8U, 3);
		if (!pKinect->colorimg)
		{
			printf("cvCreateImage() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->colorFrameReader) pKinect->type = KINECT_TYPE_COLOR;
		return (CvCapture*)pKinect;
	}
	else if (strncmp(filename, "Kinect2Depth", strlen("Kinect2Depth")) == 0)
	{
		IDepthFrameSource* depthFrameSource = nullptr;
		hr = pKinect->kinectSensor->get_DepthFrameSource(&depthFrameSource);
		if (FAILED(hr))
		{
			printf("IKinectSensor::get_DepthFrameSource() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		hr = depthFrameSource->OpenReader(&pKinect->depthFrameReader);
		if (FAILED(hr)) 
		{
			printf("IDepthFrameSource::OpenReader() failed.\n");
			SAFERELEASEKINECT2SDK(depthFrameSource);
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		SAFERELEASEKINECT2SDK(depthFrameSource);
		pKinect->depthimg = cvCreateImage(cvSize(512,424), IPL_DEPTH_8U, 3);
		if (!pKinect->depthimg)
		{
			printf("cvCreateImage() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->depthFrameReader) pKinect->type = KINECT_TYPE_DEPTH;
		return (CvCapture*)pKinect;
	}
	else if (strncmp(filename, "Kinect2Infrared", strlen("Kinect2Infrared")) == 0)
	{
		IInfraredFrameSource* infraredFrameSource = nullptr;
		hr = pKinect->kinectSensor->get_InfraredFrameSource(&infraredFrameSource);
		if (FAILED(hr))
		{
			printf("IKinectSensor::get_InfraredFrameSource() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		hr = infraredFrameSource->OpenReader(&pKinect->infraredFrameReader);
		if (FAILED(hr)) 
		{
			printf("IInfraredFrameSource::OpenReader() failed.\n");
			SAFERELEASEKINECT2SDK(infraredFrameSource);
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		SAFERELEASEKINECT2SDK(infraredFrameSource);
		pKinect->infraredimg = cvCreateImage(cvSize(512,424), IPL_DEPTH_8U, 3);
		if (!pKinect->infraredimg)
		{
			printf("cvCreateImage() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->infraredFrameReader) pKinect->type = KINECT_TYPE_INFRARED;
		return (CvCapture*)pKinect;
	}
	else return cvCreateFileCapture(filename);
}

inline int cvSetCapturePropertyKinect2SDK(CvCapture* capture, int property_id, double value)
{
	KINECT* pKinect = (KINECT*)capture;

	if ((pKinect->type == KINECT_TYPE_COLOR)||(pKinect->type == KINECT_TYPE_DEPTH)||(pKinect->type == KINECT_TYPE_INFRARED))
	{
		return 0;
	}
	else return cvSetCaptureProperty(capture, property_id, value);
}

inline double cvGetCapturePropertyKinect2SDK(CvCapture* capture, int property_id)
{
	KINECT* pKinect = (KINECT*)capture;

	switch (pKinect->type)
	{
	case KINECT_TYPE_COLOR:
		switch (property_id)
		{
		case CV_CAP_PROP_FRAME_WIDTH:
			return 1920;
		case CV_CAP_PROP_FRAME_HEIGHT:
			return 1080;
		default:
			return 0;		
		}
	case KINECT_TYPE_DEPTH:
	case KINECT_TYPE_INFRARED:
		switch (property_id)
		{
		case CV_CAP_PROP_FRAME_WIDTH:
			return 512;
		case CV_CAP_PROP_FRAME_HEIGHT:
			return 424;
		default:
			return 0;		
		}
	default:
		return cvGetCaptureProperty(capture, property_id);
	}
}

inline IplImage* cvQueryFrameKinect2SDK(CvCapture* capture)
{
	KINECT* pKinect = (KINECT*)capture;

	switch (pKinect->type)
	{
	case KINECT_TYPE_COLOR:
		_ProcessIncomingColorDataKinect2SDK(pKinect);
		return pKinect->colorimg;
	case KINECT_TYPE_DEPTH:
		_ProcessIncomingDepthDataKinect2SDK(pKinect);
		return pKinect->depthimg;
	case KINECT_TYPE_INFRARED:
		_ProcessIncomingInfraredDataKinect2SDK(pKinect);
		return pKinect->infraredimg;
	default:
		return cvQueryFrame(capture);
	}
}

inline void cvReleaseCaptureKinect2SDK(CvCapture** capture)
{
	KINECT* pKinect = (KINECT*)*capture;
	HRESULT hr = E_FAIL;

	if ((pKinect->type == KINECT_TYPE_COLOR)||(pKinect->type == KINECT_TYPE_DEPTH)||(pKinect->type == KINECT_TYPE_INFRARED))
	{
		hr = pKinect->kinectSensor->Close();
		if (FAILED(hr)) 
		{
			printf("IKinectSensor::Close() failed.\n");
		}
		_ReleaseKinect2SDK(&pKinect);
	}
	else cvReleaseCapture(capture);
}

#define cvCreateFileCapture cvCreateFileCaptureKinect2SDK
#define cvSetCaptureProperty cvSetCapturePropertyKinect2SDK
#define cvGetCaptureProperty cvGetCapturePropertyKinect2SDK
#define cvQueryFrame cvQueryFrameKinect2SDK
#define cvReleaseCapture cvReleaseCaptureKinect2SDK

#endif // !CVKINECT2SDKHOOK_H
