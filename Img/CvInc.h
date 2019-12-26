/***************************************************************************************************************:')

CvInc.h

Fabrice Le Bars

Created : 2018-08-07

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef CVINC_H
#define CVINC_H

#ifdef _MSC_VER
// Disable some Visual Studio warnings.
#pragma warning(disable : 4100) 
#pragma warning(disable : 4458) 
#pragma warning(disable : 4996)
#pragma warning(disable : 6204)
#pragma warning(disable : 6201)
#pragma warning(disable : 6294)
#pragma warning(disable : 6385)
#endif // _MSC_VER

#ifdef __BORLANDC__
// Disable some Borland C++ Builder warnings.
#pragma warn -8019
#endif // __BORLANDC__

#ifdef __GNUC__
// Disable some GCC warnings.
#if (__GNUC__ >= 9)
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif // (__GNUC__ >= 9)
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wunused-function"
//#pragma GCC diagnostic ignored "-Wunused"
//#pragma GCC diagnostic ignored "-Wcomment"
//#pragma GCC diagnostic ignored "-Wuninitialized"
//#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#pragma GCC diagnostic push
#endif // (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#endif // __GNUC__

// OpenCV headers.
#if defined(OPENCV249) || defined(OPENCV2413) || defined(OPENCV320) || defined(OPENCV342) || defined(OPENCV412)
// This header should only contain simple C code without dependencies on other headers...
#include "opencv2/core/version.hpp"
#else
#ifndef DISABLE_OPENCV_VERSION
// This header should only contain simple C code without dependencies on other headers...
#include "opencv2/core/version.hpp"
#else
// OpenCV 1.X.X...
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
#endif // !DISABLE_OPENCV_VERSION
#endif // defined(OPENCV249) || defined(OPENCV2413) || defined(OPENCV320) || defined(OPENCV342) || defined(OPENCV412)

#if (CV_MAJOR_VERSION >= 2)
// To try to solve cvRound() undefined problem in C mode in OpenCV 3.1.0...
// After OpenCV 3.2.0, C mode will probably not build any more due to several problems in core OpenCV headers...
// Starting with OpenCV 4.0.0, most of the C headers have been removed...
#if (CV_MAJOR_VERSION == 3)
#include "opencv2/core/fast_math.hpp"
#endif // (CV_MAJOR_VERSION == 3)
//#include "opencv/cv.h" // Sometimes cause strange errors in debug and C++ mode due to the redefinition of free()...
//#include "opencv/cvwimage.h"
//#include "opencv/cxcore.h"
//#include "opencv/highgui.h"
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
// The following headers do not build in C mode.
#ifdef __cplusplus
#if ((CV_MAJOR_VERSION == 2) || (CV_MAJOR_VERSION == 3))
//#include "opencv/cvaux.h" // Not found on Ubuntu 12.04...?
//#include "opencv/cxmisc.h"
//#include "opencv/ml.h"
#endif // ((CV_MAJOR_VERSION == 2) || (CV_MAJOR_VERSION == 3))
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#if (CV_MAJOR_VERSION >= 3)
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#endif // (CV_MAJOR_VERSION >= 3)
//#include "opencv2/contrib/contrib.hpp"
#endif // __cplusplus
#endif // (CV_MAJOR_VERSION >= 2)

// min and max may be undefined so we need to redefine them here...
#if (CV_MAJOR_VERSION >= 2)
#ifdef _MSC_VER
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif // !max
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif // !min
#endif // _MSC_VER
#endif // (CV_MAJOR_VERSION >= 2)

// Some macros might be missing depending on OpenCV versions...
#ifndef DISABLE_OPENCV_COMPAT_MACROS
#ifdef __cplusplus
#if (CV_MAJOR_VERSION < 3)
namespace cv
{
	enum
	{
		CAP_PROP_FRAME_WIDTH = CV_CAP_PROP_FRAME_WIDTH,
		CAP_PROP_FRAME_HEIGHT = CV_CAP_PROP_FRAME_HEIGHT
	};

	// Don't know how to define cv::VideoWriter::fourcc...

}
#endif // (CV_MAJOR_VERSION < 3)
#endif // __cplusplus
#endif // DISABLE_OPENCV_COMPAT_MACROS

// The ENTER key code seems to vary depending on OpenCV versions...
#ifndef CV_KEY_CODE_ENTER
#ifdef _WIN32
#define CV_KEY_CODE_ENTER 13 
#else
#if (CV_MAJOR_VERSION >= 4)
#define CV_KEY_CODE_ENTER 13 
#else
#ifdef __APPLE__
#define CV_KEY_CODE_ENTER 13 
#else
#define CV_KEY_CODE_ENTER 10
#endif // __APPLE__
#endif // (CV_MAJOR_VERSION >= 4)
#endif // _WIN32
#endif // !CV_KEY_CODE_ENTER

#if (CV_MAJOR_VERSION >= 4)
#ifndef USE_OPENCV_HIGHGUI_CPP_API
#define USE_OPENCV_HIGHGUI_CPP_API
#endif // !USE_OPENCV_HIGHGUI_CPP_API
#endif // (CV_MAJOR_VERSION >= 4)

#ifdef __GNUC__
// Restore the GCC warnings previously disabled.
#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#pragma GCC diagnostic pop
#else
//#pragma GCC diagnostic warning "-Wunknown-pragmas"
//#pragma GCC diagnostic warning "-Wuninitialized"
//#pragma GCC diagnostic warning "-Wcomment"
//#pragma GCC diagnostic warning "-Wunused"
#pragma GCC diagnostic warning "-Wunused-function"
//#pragma GCC diagnostic warning "-Wunused-value"
//#pragma GCC diagnostic warning "-Wunused-variable"
//#pragma GCC diagnostic warning "-Wunused-parameter"
//#if (__GNUC__ >= 9)
//#pragma GCC diagnostic warning "-Wclass-memaccess"
//#pragma GCC diagnostic warning "-Wdeprecated-copy"
//#endif // (__GNUC__ >= 9)
#endif // (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#endif // __GNUC__

#ifdef __BORLANDC__
// Restore the Borland C++ Builder warnings previously disabled.
#pragma warn .8019
#endif // __BORLANDC__

#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled.
#pragma warning(default : 6385)
#pragma warning(default : 6294)
#pragma warning(default : 6201)
#pragma warning(default : 6204)
#pragma warning(default : 4996)
#pragma warning(default : 4458) 
#pragma warning(default : 4100) 
#endif // _MSC_VER

#endif // !CVINC_H
