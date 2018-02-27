#ifndef CVCLEYESDKHOOK_H
#define CVCLEYESDKHOOK_H

// To use this way :
//#pragma push_macro("cvCreateFileCapture")
//#pragma push_macro("cvSetCaptureProperty")
//#pragma push_macro("cvGetCaptureProperty")
//#pragma push_macro("cvQueryFrame")
//#pragma push_macro("cvReleaseCapture")
//#include "CvCLEyeSDKHook.h"
// Your code (with cvCreateFileCapture("CLEye0"))...
//#pragma pop_macro("cvReleaseCapture")
//#pragma pop_macro("cvQueryFrame")
//#pragma pop_macro("cvGetCaptureProperty")
//#pragma pop_macro("cvSetCaptureProperty")
//#pragma pop_macro("cvCreateFileCapture")

#ifndef INCLUDE_HEADERS_OUTSIDE_CVCLEYESDKHOOK
#include <stdio.h>
#include "CLEyeMulticam.h"
#pragma comment(lib, "CLEyeMulticam.lib")

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv/cvaux.h"
#endif // INCLUDE_HEADERS_OUTSIDE_CVCLEYESDKHOOK

#define CLEYE_TYPE_COLOR 128

struct CLEYE
{
	int type;
	GUID _cameraGUID;
	CLEyeCameraInstance _cam;
	CLEyeCameraColorMode _mode;
	CLEyeCameraResolution _resolution;
	PBYTE pCapBuffer;
	IplImage *pCapImage;
	IplImage* colorimg;
};
typedef struct CLEYE CLEYE;

inline void _ReleaseCLEyeSDK(CLEYE** ppCLEye)
{
	if (!*ppCLEye)
	{
		if ((*ppCLEye)->colorimg)
		{
			free((*ppCLEye)->colorimg);
			(*ppCLEye)->colorimg = NULL;
		}
		// Stop camera capture
		CLEyeCameraStop((*ppCLEye)->_cam);
		// Destroy camera object
		CLEyeDestroyCamera((*ppCLEye)->_cam);
		// Destroy the allocated OpenCV image
		cvReleaseImage(&(*ppCLEye)->pCapImage);
		(*ppCLEye)->_cam = NULL;
		free(*ppCLEye);
		*ppCLEye = NULL;
	}
}

inline void _ProcessIncomingColorDataCLEyeSDK(CLEYE* pCLEye)
{
	CLEyeCameraGetFrame(pCLEye->_cam, pCLEye->pCapBuffer);
	//int height = 640, width = 480;
	//cv::Mat img1(height, width, CV_8UC4, reinterpret_cast<void*>(pCLEye->pCapBuffer));
	//IplImage im = img1;
	//cvCvtColor(&im, pCLEye->colorimg, CV_BGRA2BGR);
	cvCvtColor(pCLEye->pCapImage, pCLEye->colorimg, CV_BGRA2BGR);
}

inline CvCapture* cvCreateFileCaptureCLEyeSDK(const char* filename)
{
	CLEYE* pCLEye = NULL;
	int w = 0, h = 0;
	int id = 0;

	if (sscanf(filename, "CLEye%d", &id) == 1)
	{
		// Code common to all Kinect 2 sources.
		pCLEye = (CLEYE*)calloc(1, sizeof(CLEYE));
		if (!pCLEye)
		{
			printf("calloc() failed.\n");
			return NULL;
		}
		pCLEye->_cameraGUID = CLEyeGetCameraUUID(id);
		pCLEye->_cam = CLEyeCreateCamera(pCLEye->_cameraGUID, CLEYE_COLOR_PROCESSED, CLEYE_VGA, 30);
		if (pCLEye->_cam == NULL)
		{
			printf("CLEyeCreateCamera() failed.\n");
			return NULL;
		}

		// Get camera frame dimensions
		CLEyeCameraGetFrameDimensions(pCLEye->_cam, w, h);
		// Depending on color mode chosen, create the appropriate OpenCV image
		pCLEye->pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);

		// Set some camera parameters
		CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_GAIN, 0);
		CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_EXPOSURE, 511);

		// Start capturing
		CLEyeCameraStart(pCLEye->_cam);
		cvGetImageRawData(pCLEye->pCapImage, &pCLEye->pCapBuffer);
		pCLEye->colorimg = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
		if (!pCLEye->colorimg)
		{
			printf("cvCreateImage() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}
		pCLEye->type = CLEYE_TYPE_COLOR;
		return (CvCapture*)pCLEye;
	}
	else return cvCreateFileCapture(filename);
}

inline int cvSetCapturePropertyCLEyeSDK(CvCapture* capture, int property_id, double value)
{
	CLEYE* pCLEye = (CLEYE*)capture;

	switch (pCLEye->type)
	{
	case CLEYE_TYPE_COLOR:
		return 0;
	default:
		return cvSetCaptureProperty(capture, property_id, value);
	}
}

inline double cvGetCapturePropertyCLEyeSDK(CvCapture* capture, int property_id)
{
	CLEYE* pCLEye = (CLEYE*)capture;

	switch (pCLEye->type)
	{
	case CLEYE_TYPE_COLOR:
		switch (property_id)
		{
		case CV_CAP_PROP_FRAME_WIDTH:
			return 640;
		case CV_CAP_PROP_FRAME_HEIGHT:
			return 480;
		default:
			return 0;
		}
	default:
		return cvGetCaptureProperty(capture, property_id);
	}
}

inline IplImage* cvQueryFrameCLEyeSDK(CvCapture* capture)
{
	CLEYE* pCLEye = (CLEYE*)capture;

	if (pCLEye->type == CLEYE_TYPE_COLOR)
	{
		_ProcessIncomingColorDataCLEyeSDK(pCLEye);
		//return pCLEye->pCapImage;
		return pCLEye->colorimg;
	}
	else return cvQueryFrame(capture);
}

inline void cvReleaseCaptureCLEyeSDK(CvCapture** capture)
{
	CLEYE* pCLEye = (CLEYE*)*capture;

	if (pCLEye->type == CLEYE_TYPE_COLOR)
	{
		_ReleaseCLEyeSDK(&pCLEye);
	}
	else cvReleaseCapture(capture);
}

#define cvCreateFileCapture cvCreateFileCaptureCLEyeSDK
#define cvSetCaptureProperty cvSetCapturePropertyCLEyeSDK
#define cvGetCaptureProperty cvGetCapturePropertyCLEyeSDK
#define cvQueryFrame cvQueryFrameCLEyeSDK
#define cvReleaseCapture cvReleaseCaptureCLEyeSDK

#endif // CVCLEYESDKHOOK_H
