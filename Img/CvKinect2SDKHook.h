#ifndef CVKINECT2SDKHOOK_H
#define CVKINECT2SDKHOOK_H

// To use this way :
//#pragma push_macro("VideoCapture")
//#include "CvKinect2SDKHook.h"
// Your code (with cv::VideoCapture("Kinect2Color"), cv::VideoCapture("Kinect2Depth") or cv::VideoCapture("Kinect2Infrared")), etc.
//#pragma pop_macro("VideoCapture")
// Or (only if OpenCV < 4) :
//#pragma push_macro("cvCreateFileCapture")
//#pragma push_macro("cvSetCaptureProperty")
//#pragma push_macro("cvGetCaptureProperty")
//#pragma push_macro("cvQueryFrame")
//#pragma push_macro("cvReleaseCapture")
//#include "CvKinect2SDKHook.h"
// Your code (with cvCreateFileCapture("Kinect2Color"), cvCreateFileCapture("Kinect2Depth") or cvCreateFileCapture("Kinect2Infrared")), etc.
//#pragma pop_macro("cvReleaseCapture")
//#pragma pop_macro("cvQueryFrame")
//#pragma pop_macro("cvGetCaptureProperty")
//#pragma pop_macro("cvSetCaptureProperty")
//#pragma pop_macro("cvCreateFileCapture")

#ifndef INCLUDE_HEADERS_OUTSIDE_CVKINECT2SDKHOOK
#ifdef _WIN32
#ifndef USE_LIBFREENECT2
#ifndef _MSC_VER
// In C++, GCC does not accept forward enum declaration without specifying a size, 
// while Visual Studio probably assumes int like in C...
// See https://stackoverflow.com/questions/71416/forward-declaring-an-enum-in-c.
#define _KinectCapabilities_
enum _KinectCapabilities
    {
        KinectCapabilities_None	= 0,
        KinectCapabilities_Vision	= 0x1,
        KinectCapabilities_Audio	= 0x2,
        KinectCapabilities_Face	= 0x4,
        KinectCapabilities_Expressions	= 0x8,
        KinectCapabilities_Gamechat	= 0x10
    } ;
typedef enum _KinectCapabilities KinectCapabilities;
#define _FrameSourceTypes_
enum _FrameSourceTypes
    {
        FrameSourceTypes_None	= 0,
        FrameSourceTypes_Color	= 0x1,
        FrameSourceTypes_Infrared	= 0x2,
        FrameSourceTypes_LongExposureInfrared	= 0x4,
        FrameSourceTypes_Depth	= 0x8,
        FrameSourceTypes_BodyIndex	= 0x10,
        FrameSourceTypes_Body	= 0x20,
        FrameSourceTypes_Audio	= 0x40
    } ;
typedef enum _FrameSourceTypes FrameSourceTypes;
#define _ColorImageFormat_
enum _ColorImageFormat
    {
        ColorImageFormat_None	= 0,
        ColorImageFormat_Rgba	= 1,
        ColorImageFormat_Yuv	= 2,
        ColorImageFormat_Bgra	= 3,
        ColorImageFormat_Bayer	= 4,
        ColorImageFormat_Yuy2	= 5
    } ;
typedef enum _ColorImageFormat ColorImageFormat;
#define _HandState_
enum _HandState
    {
        HandState_Unknown	= 0,
        HandState_NotTracked	= 1,
        HandState_Open	= 2,
        HandState_Closed	= 3,
        HandState_Lasso	= 4
    } ;
typedef enum _HandState HandState;
#define _Expression_
enum _Expression
    {
        Expression_Neutral	= 0,
        Expression_Happy	= 1,
        Expression_Count	= ( Expression_Happy + 1 ) 
    } ;
typedef enum _Expression Expression;
#define _DetectionResult_
enum _DetectionResult
    {
        DetectionResult_Unknown	= 0,
        DetectionResult_No	= 1,
        DetectionResult_Maybe	= 2,
        DetectionResult_Yes	= 3
    } ;
typedef enum _DetectionResult DetectionResult;
#define _TrackingConfidence_
enum _TrackingConfidence
    {
        TrackingConfidence_Low	= 0,
        TrackingConfidence_High	= 1
    } ;
typedef enum _TrackingConfidence TrackingConfidence;
#define _Activity_
enum _Activity
    {
        Activity_EyeLeftClosed	= 0,
        Activity_EyeRightClosed	= 1,
        Activity_MouthOpen	= 2,
        Activity_MouthMoved	= 3,
        Activity_LookingAway	= 4,
        Activity_Count	= ( Activity_LookingAway + 1 ) 
    } ;
typedef enum _Activity Activity;
#define _Appearance_
enum _Appearance
    {
        Appearance_WearingGlasses	= 0,
        Appearance_Count	= ( Appearance_WearingGlasses + 1 ) 
    } ;
typedef enum _Appearance Appearance;
#define _JointType_
enum _JointType
    {
        JointType_SpineBase	= 0,
        JointType_SpineMid	= 1,
        JointType_Neck	= 2,
        JointType_Head	= 3,
        JointType_ShoulderLeft	= 4,
        JointType_ElbowLeft	= 5,
        JointType_WristLeft	= 6,
        JointType_HandLeft	= 7,
        JointType_ShoulderRight	= 8,
        JointType_ElbowRight	= 9,
        JointType_WristRight	= 10,
        JointType_HandRight	= 11,
        JointType_HipLeft	= 12,
        JointType_KneeLeft	= 13,
        JointType_AnkleLeft	= 14,
        JointType_FootLeft	= 15,
        JointType_HipRight	= 16,
        JointType_KneeRight	= 17,
        JointType_AnkleRight	= 18,
        JointType_FootRight	= 19,
        JointType_SpineShoulder	= 20,
        JointType_HandTipLeft	= 21,
        JointType_ThumbLeft	= 22,
        JointType_HandTipRight	= 23,
        JointType_ThumbRight	= 24,
        JointType_Count	= ( JointType_ThumbRight + 1 ) 
    } ;
typedef enum _JointType JointType;
#define _TrackingState_
enum _TrackingState
    {
        TrackingState_NotTracked	= 0,
        TrackingState_Inferred	= 1,
        TrackingState_Tracked	= 2
    } ;
typedef enum _TrackingState TrackingState;
#define _FrameEdges_
enum _FrameEdges
    {
        FrameEdge_None	= 0,
        FrameEdge_Right	= 0x1,
        FrameEdge_Left	= 0x2,
        FrameEdge_Top	= 0x4,
        FrameEdge_Bottom	= 0x8
    } ;
typedef enum _FrameEdges FrameEdges;
#define _FrameCapturedStatus_
enum _FrameCapturedStatus
    {
        FrameCapturedStatus_Unknown	= 0,
        FrameCapturedStatus_Queued	= 1,
        FrameCapturedStatus_Dropped	= 2
    } ;
typedef enum _FrameCapturedStatus FrameCapturedStatus;
#define _AudioBeamMode_
enum _AudioBeamMode
    {
        AudioBeamMode_Automatic	= 0,
        AudioBeamMode_Manual	= 1
    } ;
typedef enum _AudioBeamMode AudioBeamMode;
#define _KinectAudioCalibrationState_
enum _KinectAudioCalibrationState
    {
        KinectAudioCalibrationState_Unknown	= 0,
        KinectAudioCalibrationState_CalibrationRequired	= 1,
        KinectAudioCalibrationState_Calibrated	= 2
    } ;
typedef enum _KinectAudioCalibrationState KinectAudioCalibrationState;
#define _PointerDeviceType_
enum _PointerDeviceType
    {
        PointerDeviceType_Touch	= 0,
        PointerDeviceType_Pen	= 1,
        PointerDeviceType_Mouse	= 2,
        PointerDeviceType_Kinect	= 3
    } ;
typedef enum _PointerDeviceType PointerDeviceType;
#define _HandType_
enum _HandType
    {
        HandType_NONE	= 0,
        HandType_LEFT	= ( HandType_NONE + 1 ) ,
        HandType_RIGHT	= ( HandType_LEFT + 1 ) 
    } ;
typedef enum _HandType HandType;
#define _KinectHoldingState_
enum _KinectHoldingState
    {
        KinectHoldingState_Started	= 0,
        KinectHoldingState_Completed	= 1,
        KinectHoldingState_Canceled	= 2
    } ;
typedef enum _KinectHoldingState KinectHoldingState;
#define _KinectGestureSettings_
enum _KinectGestureSettings
    {
        KinectGestureSettings_None	= 0,
        KinectGestureSettings_Tap	= 0x1,
        KinectGestureSettings_ManipulationTranslateX	= 0x40,
        KinectGestureSettings_ManipulationTranslateY	= 0x80,
        KinectGestureSettings_ManipulationTranslateRailsX	= 0x100,
        KinectGestureSettings_ManipulationTranslateRailsY	= 0x200,
        KinectGestureSettings_ManipulationScale	= 0x800,
        KinectGestureSettings_ManipulationTranslateInertia	= 0x1000,
        KinectGestureSettings_KinectHold	= 0x10000
    } ;
typedef enum _KinectGestureSettings KinectGestureSettings;
#define _KinectInteractionMode_
enum _KinectInteractionMode
    {
        KinectInteractionMode_Normal	= 0,
        KinectInteractionMode_Off	= 1,
        KinectInteractionMode_Media	= 2
    } ;
typedef enum _KinectInteractionMode KinectInteractionMode;
#define _KinectEngagementMode_
enum _KinectEngagementMode
    {
        KinectEngagementMode_None	= 0,
        KinectEngagementMode_SystemOnePerson	= 1,
        KinectEngagementMode_SystemTwoPerson	= 2,
        KinectEngagementMode_ManualOnePerson	= 3,
        KinectEngagementMode_ManualTwoPerson	= 4
    } ;
typedef enum _KinectEngagementMode KinectEngagementMode;
#endif // !_MSC_VER
#include <Kinect.h>
#ifdef _MSC_VER
#pragma comment(lib, "Kinect20.lib")
#endif // _MSC_VER
#else
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#ifdef _MSC_VER
#pragma comment(lib, "freenect2.lib")
#endif // _MSC_VER
#endif // USE_LIBFREENECT2
#else
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#endif // _WIN32

#include "opencv2/core/version.hpp"

// Temporary workaround because many conversions from C to C++ types are disabled by default after OpenCV 4.2.0...
#if (CV_MAJOR_VERSION >= 4)
#if (CV_MINOR_VERSION >= 2)
#ifndef CV__ENABLE_C_API_CTORS
#define CV__ENABLE_C_API_CTORS
#endif // !CV__ENABLE_C_API_CTORS
#ifndef CV__SKIP_MESSAGE_MALFORMED_C_API_CTORS
#define CV__SKIP_MESSAGE_MALFORMED_C_API_CTORS
#endif // !CV__SKIP_MESSAGE_MALFORMED_C_API_CTORS
#endif // (CV_MINOR_VERSION >= 2)
#endif // (CV_MAJOR_VERSION >= 4)

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

#define KINECT_COLOR_IMAGE_WIDTH 1920
#define KINECT_COLOR_IMAGE_HEIGHT 1080
#define KINECT_INFRARED_IMAGE_WIDTH 512
#define KINECT_INFRARED_IMAGE_HEIGHT 424

struct KINECT
{
	int type;
#ifndef USE_LIBFREENECT2
	IKinectSensor* kinectSensor;
	IColorFrameReader* colorFrameReader;
	IDepthFrameReader* depthFrameReader;
	IInfraredFrameReader* infraredFrameReader;
#else
	std::string serial;
	libfreenect2::Freenect2 freenect2;
	libfreenect2::Freenect2Device* dev;
#endif // USE_LIBFREENECT2
#if ((CV_MAJOR_VERSION < 4) || (defined(CV__ENABLE_C_API_CTORS)))
	IplImage colorim;
	IplImage depthim;
	IplImage infraredim;
	//IplImage* colorimg;
	//IplImage* depthimg;
	//IplImage* infraredimg;
#endif // ((CV_MAJOR_VERSION < 4) || (defined(CV__ENABLE_C_API_CTORS)))
	cv::Mat colorimgmat;
	cv::Mat depthimgmat;
	cv::Mat infraredimgmat;
};
typedef struct KINECT KINECT;

#ifndef USE_LIBFREENECT2
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
		(*ppKinect)->infraredimgmat.release();
		//if ((*ppKinect)->infraredimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->infraredimg);
		//	(*ppKinect)->infraredimg = NULL;
		//}
		(*ppKinect)->depthimgmat.release();
		//if ((*ppKinect)->depthimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->depthimg);
		//	(*ppKinect)->depthimg = NULL;
		//}
		(*ppKinect)->colorimgmat.release();
		//if ((*ppKinect)->colorimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->colorimg);
		//	(*ppKinect)->colorimg = NULL;
		//}
		SAFERELEASEKINECT2SDK((*ppKinect)->infraredFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->depthFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->colorFrameReader);
		SAFERELEASEKINECT2SDK((*ppKinect)->kinectSensor);
		(*ppKinect)->type = 0;
		delete (*ppKinect);
		*ppKinect = NULL;
	}
}

inline void _ReleaseKinect2(KINECT** ppKinect)
{
	HRESULT hr = E_FAIL;
	hr = (*ppKinect)->kinectSensor->Close();
	if (FAILED(hr))
	{
		printf("IKinectSensor::Close() failed.\n");
	}
	_ReleaseKinect2SDK(ppKinect);
}

inline KINECT* _InitKinect2(const char* filename)
{
	KINECT* pKinect = NULL;
	HRESULT hr = E_FAIL;

	// Code common to all Kinect 2 sources.
	pKinect = new KINECT();
	if (!pKinect)
	{
		printf("new failed.\n");
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
		//pKinect->colorimg = cvCreateImage(cvSize(KINECT_COLOR_IMAGE_WIDTH,KINECT_COLOR_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->colorimgmat = cv::Mat::zeros(cv::Size(KINECT_COLOR_IMAGE_WIDTH,KINECT_COLOR_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->colorimg)
		if (pKinect->colorimgmat.empty())
		{
			printf("cv::Mat::zeros() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->colorFrameReader) pKinect->type = KINECT_TYPE_COLOR;
		else
		{
			printf("Invalid colorFrameReader.\n");
			pKinect->colorimgmat.release();
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
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
		//pKinect->depthimg = cvCreateImage(cvSize(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->depthimgmat = cv::Mat::zeros(cv::Size(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->depthimg)
		if (pKinect->depthimgmat.empty())
		{
			printf("cv::Mat::zeros() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->depthFrameReader) pKinect->type = KINECT_TYPE_DEPTH;
		else
		{
			printf("Invalid depthFrameReader.\n");
			pKinect->depthimgmat.release();
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
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
		//pKinect->infraredimg = cvCreateImage(cvSize(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->infraredimgmat = cv::Mat::zeros(cv::Size(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->infraredimg)
		if (pKinect->infraredimgmat.empty())		
		{
			printf("cv::Mat::zeros() failed.\n");
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
		if (pKinect->infraredFrameReader) pKinect->type = KINECT_TYPE_INFRARED;
		else
		{
			printf("Invalid infraredFrameReader.\n");
			pKinect->infraredimgmat.release();
			pKinect->kinectSensor->Close();
			_ReleaseKinect2SDK(&pKinect);
			return NULL;
		}
	}
	else
	{
		pKinect->kinectSensor->Close();
		_ReleaseKinect2SDK(&pKinect);
		return NULL;
	}
	return pKinect;
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
		int height = KINECT_COLOR_IMAGE_HEIGHT, width = KINECT_COLOR_IMAGE_WIDTH;
		if (SUCCEEDED(frameDesc->get_Height(&height)) && 
			SUCCEEDED(frameDesc->get_Width(&width))) {
				colorBuffer = new RGBQUAD[height * width];
				hr = data->CopyConvertedFrameDataToArray(height * width * sizeof(RGBQUAD),
					reinterpret_cast<BYTE*>(colorBuffer), ColorImageFormat_Bgra);
				if (SUCCEEDED(hr)) {
					cv::Mat img1(height, width, CV_8UC4, reinterpret_cast<void*>(colorBuffer));
					cv::cvtColor(img1, pKinect->colorimgmat, CV_BGRA2BGR);
					//IplImage im = img1;
					//cvCvtColor(&im, pKinect->colorimg, CV_BGRA2BGR);
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
	int height = KINECT_INFRARED_IMAGE_HEIGHT, width = KINECT_INFRARED_IMAGE_WIDTH;

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

					cv::cvtColor(img0, pKinect->depthimgmat, CV_GRAY2BGR);
					//IplImage im = img0;
					//cvCvtColor(&im, pKinect->depthimg, CV_GRAY2BGR);
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
	int height = KINECT_INFRARED_IMAGE_HEIGHT, width = KINECT_INFRARED_IMAGE_WIDTH;

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
					cv::cvtColor(img0, pKinect->infraredimgmat, CV_GRAY2BGR);
					//IplImage im = img0;
					//cvCvtColor(&im, pKinect->infraredimg, CV_GRAY2BGR);
				}
		}
	}
	if (infraredBuffer != nullptr) {
		delete[] infraredBuffer;
		infraredBuffer = nullptr;
	}
	SAFERELEASEKINECT2SDK(data);
}
#else
inline void _ReleaseKinect2SDK(KINECT** ppKinect)
{
	if (*ppKinect)
	{
		(*ppKinect)->infraredimgmat.release();
		//if ((*ppKinect)->infraredimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->infraredimg);
		//	(*ppKinect)->infraredimg = NULL;
		//}
		(*ppKinect)->depthimgmat.release();
		//if ((*ppKinect)->depthimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->depthimg);
		//	(*ppKinect)->depthimg = NULL;
		//}
		(*ppKinect)->colorimgmat.release();
		//if ((*ppKinect)->colorimg) 
		//{
		//	cvReleaseImage(&(*ppKinect)->colorimg);
		//	(*ppKinect)->colorimg = NULL;
		//}
		(*ppKinect)->type = 0;
		delete (*ppKinect);
		*ppKinect = NULL;
	}
}

inline void _ReleaseKinect2(KINECT** ppKinect)
{
	dev->stop();
	dev->close();
	_ReleaseKinect2SDK(ppKinect);
}

inline KINECT* _InitKinect2(const char* filename)
{
	KINECT* pKinect = NULL;

	// Code common to all Kinect 2 sources.
	pKinect = new KINECT();
	if (!pKinect)
	{
		printf("new failed.\n");
		return NULL;
	}
	if (freenect2.enumerateDevices() == 0)
	{
		printf("enumerateDevices() failed.\n");
		_ReleaseKinect2SDK(ppKinect);
		return NULL;
	}
	pKinect->serial = freenect2.getDefaultDeviceSerialNumber();
	pKinect->dev = freenect2.openDevice(pKinect->serial);
	if (!pKinect->dev)
	{
		printf("openDevice() failed.\n");
		dev->close();
		_ReleaseKinect2SDK(ppKinect);
		return NULL;
	}
	if (strncmp(filename, "Kinect2Color", strlen("Kinect2Color")) == 0)
	{
		libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color);
		dev->setColorFrameListener(&listener);
		if (!dev->startStreams(true, false))
		{
			printf("startStreams() failed.\n");
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		//pKinect->colorimg = cvCreateImage(cvSize(KINECT_COLOR_IMAGE_WIDTH,KINECT_COLOR_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->colorimgmat = cv::Mat::zeros(cv::Size(KINECT_COLOR_IMAGE_WIDTH,KINECT_COLOR_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->colorimg)
		if (pKinect->colorimgmat.empty())
		{
			printf("cv::Mat::zeros() failed.\n");
			dev->stop();
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		pKinect->type = KINECT_TYPE_COLOR;
	}
	else if (strncmp(filename, "Kinect2Depth", strlen("Kinect2Depth")) == 0)
	{
		libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);
		dev->setIrAndDepthFrameListener(&listener);
		if (!dev->startStreams(false, true))
		{
			printf("startStreams() failed.\n");
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		//pKinect->depthimg = cvCreateImage(cvSize(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->depthimgmat = cv::Mat::zeros(cv::Size(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->depthimg)
		if (pKinect->depthimgmat.empty())
		{
			printf("cv::Mat::zeros() failed.\n");
			dev->stop();
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		pKinect->type = KINECT_TYPE_DEPTH;
	}
	else if (strncmp(filename, "Kinect2Infrared", strlen("Kinect2Infrared")) == 0)
	{
		libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);
		dev->setIrAndDepthFrameListener(&listener);
		if (!dev->startStreams(false, true))
		{
			printf("startStreams() failed.\n");
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		//pKinect->infraredimg = cvCreateImage(cvSize(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
		pKinect->infraredimgmat = cv::Mat::zeros(cv::Size(KINECT_INFRARED_IMAGE_WIDTH,KINECT_INFRARED_IMAGE_HEIGHT), CV_8UC3);
		//if (!pKinect->infraredimg)
		if (pKinect->infraredimgmat.empty())
		{
			printf("cv::Mat::zeros() failed.\n");
			dev->stop();
			dev->close();
			_ReleaseKinect2SDK(ppKinect);
			return NULL;
		}
		pKinect->type = KINECT_TYPE_INFRARED;
	}
	else
	{
		dev->close();
		_ReleaseKinect2SDK(ppKinect);
		return NULL;
	}
	return pKinect;
}

inline void _ProcessIncomingColorDataKinect2SDK(KINECT* pKinect)
{
	libfreenect2::FrameMap frames;

	if (!listener.waitForNewFrame(frames, 10*1000)) // 10 seconds
	{
		std::cout << "timeout!" << std::endl;
		return;
	}
	libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
	cv::Mat img1(rgb->height, rgb->width, CV_8UC4, reinterpret_cast<void*>(rgb->data));
	cv::cvtColor(img1, pKinect->colorimgmat, CV_BGRA2BGR);
	//IplImage im = img1;
	//cvCvtColor(&im, pKinect->colorimg, CV_BGRA2BGR);
	listener.release(frames);
}

inline void _ProcessIncomingDepthDataKinect2SDK(KINECT* pKinect)
{
	libfreenect2::FrameMap frames;

	if (!listener.waitForNewFrame(frames, 10*1000)) // 10 seconds
	{
		std::cout << "timeout!" << std::endl;
		return;
	}
	libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
	cv::Mat depthMap = cv::Mat(depth->height, depth->width, CV_16U, depth->data);
	cv::Mat img0 = cv::Mat::zeros(depth->height, depth->width, CV_8UC1);
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

	cv::cvtColor(img0, pKinect->depthimgmat, CV_GRAY2BGR);
	//IplImage im = img0;
	//cvCvtColor(&im, pKinect->depthimg, CV_GRAY2BGR);
	listener.release(frames);
}

inline void _ProcessIncomingInfraredDataKinect2SDK(KINECT* pKinect)
{
	libfreenect2::FrameMap frames;

	if (!listener.waitForNewFrame(frames, 10*1000)) // 10 seconds
	{
		std::cout << "timeout!" << std::endl;
		return;
	}
	libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
	cv::Mat infraredMap = cv::Mat(ir->height, ir->width, CV_16U, ir->data);
	cv::Mat img0 = cv::Mat::zeros(ir->height, ir->width, CV_8UC1);
	cv::Mat img0_gamma;
	double scale = 1.0/65535.0;
	double gain = 1.0, gamma = 0.32;
	infraredMap.convertTo(img0_gamma, CV_64FC1, scale);
	pow(img0_gamma, gamma, img0_gamma);
	img0_gamma.convertTo(img0, CV_8UC1, gain*255.0);
	//cv::applyColorMap(img0, img0, cv::COLORMAP_BONE);
	cv::cvtColor(img0, pKinect->infraredimgmat, CV_GRAY2BGR);
	//IplImage im = img0;
	//cvCvtColor(&im, pKinect->infraredimg, CV_GRAY2BGR);
	listener.release(frames);
}
#endif // USE_LIBFREENECT2

namespace cv
{
	class VideoCaptureKinect2SDK : VideoCapture // Should inherit or instead have an object of VideoCapture type...?
	{
		KINECT* pKinect;
	public:
		//using VideoCapture::VideoCapture;
		VideoCaptureKinect2SDK() : VideoCapture(), pKinect(NULL) { } 
		// https://stackoverflow.com/questions/50820198/conditional-call-to-base-constructor/50820367
#if (CV_MAJOR_VERSION > 3)
		VideoCaptureKinect2SDK(const String& filename, int apiPreference = CAP_ANY) : 
			VideoCapture{ ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))? VideoCapture{} : VideoCapture{filename, apiPreference} }, pKinect(NULL) 
		{ 
			if ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))
			{
				pKinect = _InitKinect2(filename.c_str()); 
			} 
		}
		VideoCaptureKinect2SDK(int index, int apiPreference = CAP_ANY) : VideoCapture(index, apiPreference), pKinect(NULL) { }
#else
		VideoCaptureKinect2SDK(const String& filename) : 
			VideoCapture{ ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))? VideoCapture{} : VideoCapture{filename} }, pKinect(NULL) 
		{ 
			if ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))
			{
				pKinect = _InitKinect2(filename.c_str()); 
			} 
		}
		VideoCaptureKinect2SDK(int index) : VideoCapture(index), pKinect(NULL) { }
#endif // (CV_MAJOR_VERSION > 3)

		~VideoCaptureKinect2SDK() { if (pKinect) { _ReleaseKinect2(&pKinect); } } 

		using VideoCapture::open;
#if (CV_MAJOR_VERSION > 3)
		bool open(const String& filename, int apiPreference = CAP_ANY)
		{
			if (pKinect) _ReleaseKinect2(&pKinect);
			if ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))
			{
				pKinect = _InitKinect2(filename.c_str()); 
				return pKinect? true : false;
			}
			else return VideoCapture::open(filename, apiPreference);
		}
		bool open(int index, int apiPreference = CAP_ANY)
		{
			if (pKinect) _ReleaseKinect2(&pKinect);
			return VideoCapture::open(index, apiPreference);
		}
#else
		bool open(const String& filename)
		{
			if (pKinect) _ReleaseKinect2(&pKinect);
			if ((filename.find("Kinect2Color") != std::string::npos)||(filename.find("Kinect2Depth") != std::string::npos)||(filename.find("Kinect2Infrared") != std::string::npos))
			{
				pKinect = _InitKinect2(filename.c_str()); 
				return pKinect? true : false;
			}
			else return VideoCapture::open(filename);
		}
		bool open(int index)
		{
			if (pKinect) _ReleaseKinect2(&pKinect);
			return VideoCapture::open(index);
		}
#endif // (CV_MAJOR_VERSION > 3)

		using VideoCapture::release;
		void release() { if (!pKinect) VideoCapture::release(); else _ReleaseKinect2(&pKinect); }

		using VideoCapture::isOpened;
		bool isOpened() { if (!pKinect) return VideoCapture::isOpened(); else return true; }

		using VideoCapture::set;
		bool set(int property_id, double value) { if (!pKinect) return VideoCapture::set(property_id, value); else return false; }

		using VideoCapture::get;
		double get(int property_id)
		{
			if (!pKinect) return VideoCapture::get(property_id);
			switch (pKinect->type)
			{
			case KINECT_TYPE_COLOR:
				switch (property_id)
				{
#if (CV_MAJOR_VERSION < 3)
				case CV_CAP_PROP_FRAME_WIDTH: return KINECT_COLOR_IMAGE_WIDTH;
				case CV_CAP_PROP_FRAME_HEIGHT: return KINECT_COLOR_IMAGE_HEIGHT;
#else
				case CAP_PROP_FRAME_WIDTH: return KINECT_COLOR_IMAGE_WIDTH;
				case CAP_PROP_FRAME_HEIGHT: return KINECT_COLOR_IMAGE_HEIGHT;
#endif // (CV_MAJOR_VERSION < 3)
				default: return 0;
				}
			case KINECT_TYPE_DEPTH:
			case KINECT_TYPE_INFRARED:
				switch (property_id)
				{
#if (CV_MAJOR_VERSION < 3)
				case CV_CAP_PROP_FRAME_WIDTH: return KINECT_INFRARED_IMAGE_WIDTH;
				case CV_CAP_PROP_FRAME_HEIGHT: return KINECT_INFRARED_IMAGE_HEIGHT;
#else
				case CAP_PROP_FRAME_WIDTH: return KINECT_INFRARED_IMAGE_WIDTH;
				case CAP_PROP_FRAME_HEIGHT: return KINECT_INFRARED_IMAGE_HEIGHT;
#endif // (CV_MAJOR_VERSION < 3)
				default: return 0;
				}
			default:
				return 0;
			}
		}

		using VideoCapture::grab;
		bool grab() { if (!pKinect) return VideoCapture::grab(); else return true; }

		using VideoCapture::retrieve;
		bool retrieve(Mat& image, int flag = 0)
		{
			if (!pKinect) return VideoCapture::retrieve(image, flag);
			else
			{
				switch (pKinect->type)
				{
				case KINECT_TYPE_COLOR:
					_ProcessIncomingColorDataKinect2SDK(pKinect);
					return true;
				case KINECT_TYPE_DEPTH:
					_ProcessIncomingDepthDataKinect2SDK(pKinect);
					return true;
				case KINECT_TYPE_INFRARED:
					_ProcessIncomingInfraredDataKinect2SDK(pKinect);
					return true;
				default:
					return false;
				}
			}
		}

		using VideoCapture::read;
		bool read(Mat& image) { if (!pKinect) return VideoCapture::read(image); else return retrieve(image); }

		using VideoCapture::operator >>;
		VideoCapture& operator >> (Mat& image) { if (!pKinect) return VideoCapture::operator>>(image); else { retrieve(image); return *this; } }

#if (CV_MAJOR_VERSION >= 4)
		using VideoCapture::getBackendName;
#endif // (CV_MAJOR_VERSION >= 4)
		String getBackendName() const { if (pKinect) return String("CvKinect2SDKHook");
#if (CV_MAJOR_VERSION >= 4)
			else return VideoCapture::getBackendName(); }
#else
			else return String(""); }
#endif // (CV_MAJOR_VERSION >= 4)
	};

#define VideoCapture VideoCaptureKinect2SDK
}

#if ((CV_MAJOR_VERSION < 4) || (defined(CV__ENABLE_C_API_CTORS)))
inline CvCapture* cvCreateFileCaptureKinect2SDK(const char* filename)
{
	KINECT* pKinect = NULL;

	if ((strncmp(filename, "Kinect2Color", strlen("Kinect2Color")) == 0)||(strncmp(filename, "Kinect2Depth", strlen("Kinect2Depth")) == 0)||(strncmp(filename, "Kinect2Infrared", strlen("Kinect2Infrared")) == 0))
	{
		pKinect = _InitKinect2(filename);
		if (!pKinect) return NULL;
		pKinect->colorim = pKinect->colorimgmat;
		pKinect->depthim = pKinect->depthimgmat;
		pKinect->infraredim = pKinect->infraredimgmat;
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
			return KINECT_COLOR_IMAGE_WIDTH;
		case CV_CAP_PROP_FRAME_HEIGHT:
			return KINECT_COLOR_IMAGE_HEIGHT;
		default:
			return 0;		
		}
	case KINECT_TYPE_DEPTH:
	case KINECT_TYPE_INFRARED:
		switch (property_id)
		{
		case CV_CAP_PROP_FRAME_WIDTH:
			return KINECT_INFRARED_IMAGE_WIDTH;
		case CV_CAP_PROP_FRAME_HEIGHT:
			return KINECT_INFRARED_IMAGE_HEIGHT;
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
		return &pKinect->colorim;
		//return pKinect->colorimg;
	case KINECT_TYPE_DEPTH:
		_ProcessIncomingDepthDataKinect2SDK(pKinect);
		return &pKinect->depthim;
		//return pKinect->depthimg;
	case KINECT_TYPE_INFRARED:
		_ProcessIncomingInfraredDataKinect2SDK(pKinect);
		return &pKinect->infraredim;
		//return pKinect->infraredimg;
	default:
		return cvQueryFrame(capture);
	}
}

inline void cvReleaseCaptureKinect2SDK(CvCapture** capture)
{
	KINECT* pKinect = (KINECT*)*capture;

	if ((pKinect->type == KINECT_TYPE_COLOR)||(pKinect->type == KINECT_TYPE_DEPTH)||(pKinect->type == KINECT_TYPE_INFRARED)) _ReleaseKinect2(&pKinect);
	else cvReleaseCapture(capture);
}

#define cvCreateFileCapture cvCreateFileCaptureKinect2SDK
#define cvSetCaptureProperty cvSetCapturePropertyKinect2SDK
#define cvGetCaptureProperty cvGetCapturePropertyKinect2SDK
#define cvQueryFrame cvQueryFrameKinect2SDK
#define cvReleaseCapture cvReleaseCaptureKinect2SDK
#endif // ((CV_MAJOR_VERSION < 4) || (defined(CV__ENABLE_C_API_CTORS)))

#endif // !CVKINECT2SDKHOOK_H
