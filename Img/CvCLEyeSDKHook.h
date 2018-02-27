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

#define CLEYE_TYPE_COLOR_PROCESSED 128

struct CLEYE
{
	int type;
	GUID _cameraGUID;
	CLEyeCameraInstance _cam;
	PBYTE pCapBuffer;
	IplImage* pCapImage;
	IplImage* colorimg;
};
typedef struct CLEYE CLEYE;

inline void _ReleaseCLEyeSDK(CLEYE** ppCLEye)
{
	if (*ppCLEye)
	{
		if ((*ppCLEye)->colorimg)
		{
			cvReleaseImage(&(*ppCLEye)->colorimg);
			(*ppCLEye)->colorimg = NULL;
		}
		if ((*ppCLEye)->_cam)
		{
			// Stop camera capture
			CLEyeCameraStop((*ppCLEye)->_cam);
			// Destroy camera object
			CLEyeDestroyCamera((*ppCLEye)->_cam);
			(*ppCLEye)->_cam = NULL;
		}
		if ((*ppCLEye)->pCapImage)
		{
			cvReleaseImage(&(*ppCLEye)->pCapImage);
			(*ppCLEye)->pCapImage = NULL;
		}
		(*ppCLEye)->type = 0;
		free(*ppCLEye);
		*ppCLEye = NULL;
	}
}

inline void _ProcessIncomingColorDataCLEyeSDK(CLEYE* pCLEye)
{
	CLEyeCameraGetFrame(pCLEye->_cam, pCLEye->pCapBuffer);
	cvCvtColor(pCLEye->pCapImage, pCLEye->colorimg, CV_BGRA2BGR);
}

inline CvCapture* cvCreateFileCaptureCLEyeSDK(const char* filename)
{
	CLEYE* pCLEye = NULL;
	int id = 0, w = 0, h = 0;

	if (strncmp(filename, "CLEye", strlen("CLEye")) == 0)
	{
		pCLEye = (CLEYE*)calloc(1, sizeof(CLEYE));
		if (!pCLEye)
		{
			printf("calloc() failed.\n");
			return NULL;
		}
		if (sscanf(filename, "CLEye%d", &id) == 1) pCLEye->_cameraGUID = CLEyeGetCameraUUID(id);
		else pCLEye->_cameraGUID = CLEyeGetCameraUUID(0);
		pCLEye->_cam = CLEyeCreateCamera(pCLEye->_cameraGUID, CLEYE_COLOR_PROCESSED, CLEYE_VGA, 30);
		if (pCLEye->_cam == NULL)
		{
			printf("CLEyeCreateCamera() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}
		// Get camera frame dimensions.
		if (!CLEyeCameraGetFrameDimensions(pCLEye->_cam, w, h))
		{
			printf("CLEyeCameraGetFrameDimensions() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}
		// Depending on color mode chosen, create the appropriate OpenCV image.
		pCLEye->pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);
		if (!pCLEye->pCapImage)
		{
			printf("cvCreateImage() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}

		// Set some camera parameters.
		CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_GAIN, 0);
		CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_EXPOSURE, 511);

		// Start capturing.
		if (!CLEyeCameraStart(pCLEye->_cam))
		{
			printf("CLEyeCameraStart() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}
		cvGetImageRawData(pCLEye->pCapImage, &pCLEye->pCapBuffer);
		pCLEye->colorimg = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
		if (!pCLEye->colorimg)
		{
			printf("cvCreateImage() failed.\n");
			_ReleaseCLEyeSDK(&pCLEye);
			return NULL;
		}
		pCLEye->type = CLEYE_TYPE_COLOR_PROCESSED;
		return (CvCapture*)pCLEye;
	}
	else return cvCreateFileCapture(filename);
}

inline int cvSetCapturePropertyCLEyeSDK(CvCapture* capture, int property_id, double value)
{
	CLEYE* pCLEye = (CLEYE*)capture;

	switch (pCLEye->type)
	{
	case CLEYE_TYPE_COLOR_PROCESSED:
		switch (property_id)
		{
		case CV_CAP_PROP_GAIN:
			return CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_GAIN, (int)value);
		case CV_CAP_PROP_EXPOSURE:
			return CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_EXPOSURE, (int)value);
		case CV_CAP_PROP_BRIGHTNESS:
			return CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_LENSBRIGHTNESS, (int)value);
		case CV_CAP_PROP_ZOOM:
			return CLEyeSetCameraParameter(pCLEye->_cam, CLEYE_ZOOM, (int)value);
		default:
			return 0;
		}
	default:
		return cvSetCaptureProperty(capture, property_id, value);
	}
}

inline double cvGetCapturePropertyCLEyeSDK(CvCapture* capture, int property_id)
{
	CLEYE* pCLEye = (CLEYE*)capture;
	int w = 0, h = 0;

	switch (pCLEye->type)
	{
	case CLEYE_TYPE_COLOR_PROCESSED:
		switch (property_id)
		{
		case CV_CAP_PROP_FRAME_WIDTH:
			if (!CLEyeCameraGetFrameDimensions(pCLEye->_cam, w, h)) return 640;
			else return w;
		case CV_CAP_PROP_FRAME_HEIGHT:
			if (!CLEyeCameraGetFrameDimensions(pCLEye->_cam, w, h)) return 480;
			else return h;
		case CV_CAP_PROP_GAIN:
			return CLEyeGetCameraParameter(pCLEye->_cam, CLEYE_GAIN);
		case CV_CAP_PROP_EXPOSURE:
			return CLEyeGetCameraParameter(pCLEye->_cam, CLEYE_EXPOSURE);
		case CV_CAP_PROP_BRIGHTNESS:
			return CLEyeGetCameraParameter(pCLEye->_cam, CLEYE_LENSBRIGHTNESS);
		case CV_CAP_PROP_ZOOM:
			return CLEyeGetCameraParameter(pCLEye->_cam, CLEYE_ZOOM);
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

	switch (pCLEye->type)
	{
	case CLEYE_TYPE_COLOR_PROCESSED:
		_ProcessIncomingColorDataCLEyeSDK(pCLEye);
		return pCLEye->colorimg;
	default:
		return cvQueryFrame(capture);
	}
}

inline void cvReleaseCaptureCLEyeSDK(CvCapture** capture)
{
	CLEYE* pCLEye = (CLEYE*)*capture;

	if (pCLEye->type == CLEYE_TYPE_COLOR_PROCESSED)
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
