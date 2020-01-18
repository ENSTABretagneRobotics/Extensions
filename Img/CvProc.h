/***************************************************************************************************************:')

CvProc.h

IplImage data processing.

Fabrice Le Bars

Created : 2009-03-27

***************************************************************************************************************:)*/

#ifndef CVPROC_H
#define CVPROC_H

#include "OSTime.h"
#include "CvInc.h"

inline void CvCycleColors(int* pColorid, CvScalar* pColor, CvScalar defaultcolor)
{
	(*pColorid)++;
	switch (*pColorid)
	{
	case 1:
		*pColor = CV_RGB_CvScalar(0, 255, 128); // Medium green.
		break;
	case 2:
		*pColor = CV_RGB_CvScalar(255, 128, 0); // Orange.
		break;
	case 3:
		*pColor = CV_RGB_CvScalar(128, 0, 255); // Violet.
		break;
	case 4:
		*pColor = CV_RGB_CvScalar(128, 255, 0); // Light green.
		break;
	case 5:
		*pColor = CV_RGB_CvScalar(255, 0, 128); // Pink.
		break;
	case 6:
		*pColor = CV_RGB_CvScalar(0, 128, 255); // Light blue.
		break;
	case 7:
		*pColor = CV_RGB_CvScalar(0, 255, 0); // Green.
		break;
	case 8:
		*pColor = CV_RGB_CvScalar(255, 0, 0); // Red.
		break;
	case 9:
		*pColor = CV_RGB_CvScalar(0, 0, 255); // Blue.
		break;
	case 10:
		*pColor = CV_RGB_CvScalar(255, 255, 0); // Yellow.
		break;
	case 11:
		*pColor = CV_RGB_CvScalar(255, 0, 255); // Magenta.
		break;
	case 12:
		*pColor = CV_RGB_CvScalar(0, 255, 255); // Cyan.
		break;
	case 13:
		*pColor = CV_RGB_CvScalar(0, 0, 0); // Black.
		break;
	case 14:
		*pColor = CV_RGB_CvScalar(128, 128, 128); // Grey.
		break;
	case 15:
		*pColor = CV_RGB_CvScalar(255, 255, 255); // White.
		break;
	default:
		*pColorid = 0;
		*pColor = defaultcolor;
		break;
	}
}

#ifdef __cplusplus
inline void CycleColorsMat(int& colorid, cv::Scalar& color, cv::Scalar defaultcolor)
{
	(colorid)++;
	switch (colorid)
	{
	case 1:
		color = CV_RGB(0, 255, 128); // Medium green.
		break;
	case 2:
		color = CV_RGB(255, 128, 0); // Orange.
		break;
	case 3:
		color = CV_RGB(128, 0, 255); // Violet.
		break;
	case 4:
		color = CV_RGB(128, 255, 0); // Light green.
		break;
	case 5:
		color = CV_RGB(255, 0, 128); // Pink.
		break;
	case 6:
		color = CV_RGB(0, 128, 255); // Light blue.
		break;
	case 7:
		color = CV_RGB(0, 255, 0); // Green.
		break;
	case 8:
		color = CV_RGB(255, 0, 0); // Red.
		break;
	case 9:
		color = CV_RGB(0, 0, 255); // Blue.
		break;
	case 10:
		color = CV_RGB(255, 255, 0); // Yellow.
		break;
	case 11:
		color = CV_RGB(255, 0, 255); // Magenta.
		break;
	case 12:
		color = CV_RGB(0, 255, 255); // Cyan.
		break;
	case 13:
		color = CV_RGB(0, 0, 0); // Black.
		break;
	case 14:
		color = CV_RGB(128, 128, 128); // Grey.
		break;
	case 15:
		color = CV_RGB(255, 255, 255); // White.
		break;
	default:
		colorid = 0;
		color = defaultcolor;
		break;
	}
}
#endif // __cplusplus

inline int CopyOverlay(IplImage* overlayimg, IplImage* destimg)
{
	int i = overlayimg->imageSize-3;

	while (i >= 0)
	{
		if (overlayimg->imageData[i]||overlayimg->imageData[i+1]||overlayimg->imageData[i+2]) 
		{
			destimg->imageData[i] = overlayimg->imageData[i];
			destimg->imageData[i+1] = overlayimg->imageData[i+1];
			destimg->imageData[i+2] = overlayimg->imageData[i+2];
		}
		i -= 3;
	}

	return EXIT_SUCCESS;
}

#ifdef __cplusplus
inline int CopyOverlayMat(cv::Mat& overlayimg, cv::Mat& destimg)
{
	int i = overlayimg.total()-3;

	while (i >= 0)
	{
		if (overlayimg.data[i]||overlayimg.data[i+1]||overlayimg.data[i+2])
		{
			destimg.data[i] = overlayimg.data[i];
			destimg.data[i+1] = overlayimg.data[i+1];
			destimg.data[i+2] = overlayimg.data[i+2];
		}
		i -= 3;
	}

	return EXIT_SUCCESS;
}
#endif // __cplusplus

inline int CopyResizeScale(IplImage* srcimg, IplImage* destimg, BOOL bCropOnResize)
{
	IplImage* resizedimg = NULL;
	IplImage* warpedimg = NULL;
	double m[6];
	CvMat M = cvMat(2, 3, CV_64F, m);
	double ratio = 1, hscale = 1, vscale = 1, hcenter = 0, vcenter = 0, hshift = 0, vshift = 0, angle = 0;

	if ((srcimg->width == destimg->width)&&(srcimg->height == destimg->height))
	{
		cvCopy(srcimg, destimg, 0);
	}
	else
	{
		resizedimg = cvCreateImage(cvSize(destimg->width, destimg->height), destimg->depth, destimg->nChannels);
		if (!resizedimg)
		{
			return EXIT_FAILURE;
		}

		cvResize(srcimg, resizedimg, CV_INTER_LINEAR);

		ratio = (double)srcimg->width*(double)resizedimg->height/((double)srcimg->height*(double)resizedimg->width);

		if (bCropOnResize)
		{
			if (ratio >= 1)
			{
				hscale = ratio;
				vscale = 1;
			}
			else
			{
				hscale = 1;
				vscale = ratio;
			}
		}
		else
		{
			if (ratio >= 1)
			{
				hscale = 1;
				vscale = 1/ratio;
			}
			else
			{
				hscale = 1/ratio;
				vscale = 1;
			}
		}

		if ((hscale == 1)&&(vscale == 1))
		{
			cvCopy(resizedimg, destimg, 0);
			cvReleaseImage(&resizedimg);
		}
		else
		{
			warpedimg = cvCreateImage(cvSize(destimg->width, destimg->height), destimg->depth, destimg->nChannels);
			if (!warpedimg)
			{
				cvReleaseImage(&resizedimg);
				return EXIT_FAILURE;
			}

			// Create a map_matrix, where the left 2x2 matrix is the transform and the right 2x1 is the dimensions.

			hcenter = resizedimg->width*0.5+hcenter;
			vcenter = resizedimg->height*0.5+vcenter;
			hshift = resizedimg->width*0.5+hshift;
			vshift = resizedimg->height*0.5+vshift;

			m[0] = cos(angle)/hscale;
			m[1] = sin(angle)/hscale;
			m[3] = -sin(angle)/vscale;
			m[4] = cos(angle)/vscale;
			m[2] = (1-cos(angle)/hscale)*hshift-(sin(angle)/hscale)*vshift+hcenter-hshift;
			m[5] = (sin(angle)/vscale)*hshift+(1-cos(angle)/vscale)*vshift+vcenter-vshift;
			cvWarpAffine(resizedimg, warpedimg, &M, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP, cvScalarAll(0));

			cvReleaseImage(&resizedimg);
			cvCopy(warpedimg, destimg, 0);
			cvReleaseImage(&warpedimg);
		}
	}

	return EXIT_SUCCESS;
}

#ifdef __cplusplus
inline int CopyResizeScaleMat(cv::Mat& srcimg, cv::Mat& destimg, bool bCropOnResize)
{
	double m[6];
	cv::Mat M = cv::Mat(2, 3, CV_64F, m);
	double ratio = 1, hscale = 1, vscale = 1, hcenter = 0, vcenter = 0, hshift = 0, vshift = 0, angle = 0;

	if ((srcimg.cols == destimg.cols)&&(srcimg.rows == destimg.rows))
	{
		srcimg.copyTo(destimg);
	}
	else
	{
		// Missing exception handling...
		cv::Mat resizedimg = cv::Mat(cv::Size(destimg.cols, destimg.rows), destimg.type());

		cv::resize(srcimg, resizedimg, resizedimg.size());

		ratio = (double)srcimg.cols*(double)resizedimg.rows/((double)srcimg.rows*(double)resizedimg.cols);

		if (bCropOnResize)
		{
			if (ratio >= 1)
			{
				hscale = ratio;
				vscale = 1;
			}
			else
			{
				hscale = 1;
				vscale = ratio;
			}
		}
		else
		{
			if (ratio >= 1)
			{
				hscale = 1;
				vscale = 1/ratio;
			}
			else
			{
				hscale = 1/ratio;
				vscale = 1;
			}
		}

		if ((hscale == 1)&&(vscale == 1))
		{
			resizedimg.copyTo(destimg);
		}
		else
		{
			// Missing exception handling...
			cv::Mat warpedimg = cv::Mat(cv::Size(destimg.cols, destimg.rows), destimg.type());

			// Create a map_matrix, where the left 2x2 matrix is the transform and the right 2x1 is the dimensions.

			hcenter = resizedimg.cols*0.5+hcenter;
			vcenter = resizedimg.rows*0.5+vcenter;
			hshift = resizedimg.cols*0.5+hshift;
			vshift = resizedimg.rows*0.5+vshift;

			m[0] = cos(angle)/hscale;
			m[1] = sin(angle)/hscale;
			m[3] = -sin(angle)/vscale;
			m[4] = cos(angle)/vscale;
			m[2] = (1-cos(angle)/hscale)*hshift-(sin(angle)/hscale)*vshift+hcenter-hshift;
			m[5] = (sin(angle)/vscale)*hshift+(1-cos(angle)/vscale)*vshift+vcenter-vshift;
#if (CV_MAJOR_VERSION < 3)
			cv::warpAffine(resizedimg, warpedimg, M, warpedimg.size(), cv::INTER_LINEAR+CV_WARP_FILL_OUTLIERS+cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT);
#else
			cv::warpAffine(resizedimg, warpedimg, M, warpedimg.size(), cv::INTER_LINEAR+cv::WARP_FILL_OUTLIERS+cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT);
#endif // (CV_MAJOR_VERSION < 3)

			warpedimg.copyTo(destimg);
		}
	}

	return EXIT_SUCCESS;
}
#endif // __cplusplus

inline int CopyResizeScaleOverlay(IplImage* overlayimg, IplImage* destimg, BOOL bCropOnResize)
{
	IplImage* resizedimg = NULL;
	IplImage* warpedimg = NULL;
	double m[6];
	CvMat M = cvMat(2, 3, CV_64F, m);
	double ratio = 1, hscale = 1, vscale = 1, hcenter = 0, vcenter = 0, hshift = 0, vshift = 0, angle = 0;

	if ((overlayimg->width == destimg->width)&&(overlayimg->height == destimg->height))
	{
		CopyOverlay(overlayimg, destimg);
	}
	else
	{
		resizedimg = cvCreateImage(cvSize(destimg->width, destimg->height), destimg->depth, destimg->nChannels);
		if (!resizedimg)
		{
			return EXIT_FAILURE;
		}

		cvResize(overlayimg, resizedimg, CV_INTER_LINEAR);

		ratio = (double)overlayimg->width*(double)resizedimg->height/((double)overlayimg->height*(double)resizedimg->width);

		if (bCropOnResize)
		{
			if (ratio >= 1)
			{
				hscale = ratio;
				vscale = 1;
			}
			else
			{
				hscale = 1;
				vscale = ratio;
			}
		}
		else
		{
			if (ratio >= 1)
			{
				hscale = 1;
				vscale = 1/ratio;
			}
			else
			{
				hscale = 1/ratio;
				vscale = 1;
			}
		}

		if ((hscale == 1)&&(vscale == 1))
		{
			CopyOverlay(resizedimg, destimg);
			cvReleaseImage(&resizedimg);
		}
		else
		{
			warpedimg = cvCreateImage(cvSize(destimg->width, destimg->height), destimg->depth, destimg->nChannels);
			if (!warpedimg)
			{
				cvReleaseImage(&resizedimg);
				return EXIT_FAILURE;
			}

			// Create a map_matrix, where the left 2x2 matrix is the transform and the right 2x1 is the dimensions.

			hcenter = resizedimg->width*0.5+hcenter;
			vcenter = resizedimg->height*0.5+vcenter;
			hshift = resizedimg->width*0.5+hshift;
			vshift = resizedimg->height*0.5+vshift;

			m[0] = cos(angle)/hscale;
			m[1] = sin(angle)/hscale;
			m[3] = -sin(angle)/vscale;
			m[4] = cos(angle)/vscale;
			m[2] = (1-cos(angle)/hscale)*hshift-(sin(angle)/hscale)*vshift+hcenter-hshift;
			m[5] = (sin(angle)/vscale)*hshift+(1-cos(angle)/vscale)*vshift+vcenter-vshift;
			cvWarpAffine(resizedimg, warpedimg, &M, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP, cvScalarAll(0));

			cvReleaseImage(&resizedimg);
			CopyOverlay(warpedimg, destimg);
			cvReleaseImage(&warpedimg);
		}
	}

	return EXIT_SUCCESS;
}

#ifdef __cplusplus
inline int CopyResizeScaleOverlayMat(cv::Mat& srcimg, cv::Mat& destimg, bool bCropOnResize)
{
	double m[6];
	cv::Mat M = cv::Mat(2, 3, CV_64F, m);
	double ratio = 1, hscale = 1, vscale = 1, hcenter = 0, vcenter = 0, hshift = 0, vshift = 0, angle = 0;

	if ((srcimg.cols == destimg.cols)&&(srcimg.rows == destimg.rows))
	{
		CopyOverlayMat(srcimg, destimg);
	}
	else
	{
		// Missing exception handling...
		cv::Mat resizedimg = cv::Mat(cv::Size(destimg.cols, destimg.rows), destimg.type());

		cv::resize(srcimg, resizedimg, resizedimg.size());

		ratio = (double)srcimg.cols*(double)resizedimg.rows/((double)srcimg.rows*(double)resizedimg.cols);

		if (bCropOnResize)
		{
			if (ratio >= 1)
			{
				hscale = ratio;
				vscale = 1;
			}
			else
			{
				hscale = 1;
				vscale = ratio;
			}
		}
		else
		{
			if (ratio >= 1)
			{
				hscale = 1;
				vscale = 1/ratio;
			}
			else
			{
				hscale = 1/ratio;
				vscale = 1;
			}
		}

		if ((hscale == 1)&&(vscale == 1))
		{
			CopyOverlayMat(resizedimg, destimg);
		}
		else
		{
			// Missing exception handling...
			cv::Mat warpedimg = cv::Mat(cv::Size(destimg.cols, destimg.rows), destimg.type());

			// Create a map_matrix, where the left 2x2 matrix is the transform and the right 2x1 is the dimensions.

			hcenter = resizedimg.cols*0.5+hcenter;
			vcenter = resizedimg.rows*0.5+vcenter;
			hshift = resizedimg.cols*0.5+hshift;
			vshift = resizedimg.rows*0.5+vshift;

			m[0] = cos(angle)/hscale;
			m[1] = sin(angle)/hscale;
			m[3] = -sin(angle)/vscale;
			m[4] = cos(angle)/vscale;
			m[2] = (1-cos(angle)/hscale)*hshift-(sin(angle)/hscale)*vshift+hcenter-hshift;
			m[5] = (sin(angle)/vscale)*hshift+(1-cos(angle)/vscale)*vshift+vcenter-vshift;
#if (CV_MAJOR_VERSION < 3)
			cv::warpAffine(resizedimg, warpedimg, M, warpedimg.size(), cv::INTER_LINEAR+CV_WARP_FILL_OUTLIERS+cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT);
#else
			cv::warpAffine(resizedimg, warpedimg, M, warpedimg.size(), cv::INTER_LINEAR+cv::WARP_FILL_OUTLIERS+cv::WARP_INVERSE_MAP, cv::BORDER_CONSTANT);
#endif // (CV_MAJOR_VERSION < 3)

			CopyOverlayMat(warpedimg, destimg);
		}
	}

	return EXIT_SUCCESS;
}
#endif // __cplusplus

inline void CorrectImageBorders(IplImage* image, int nbpixborder, unsigned char r0, unsigned char g0, unsigned char b0)
{
	int i = 0, j = 0, index = 0;

	// Convert image->imageData from char* to unsigned char* to work with color values in 0..255.
	//unsigned char* data = reinterpret_cast<unsigned char*>(image->imageData);
	unsigned char* data = (unsigned char*)image->imageData;

	for (j = 0; j < nbpixborder; j++)
	{
		for (i = 0; i < image->height; i++)
		{
			// For first columns.
			index = 3*(j+image->width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
			// For last columns.
			index = 3*((image->width-1-j)+image->width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
		}
	}

	for (i = 0; i < nbpixborder; i++)
	{
		for (j = nbpixborder; j < image->width-nbpixborder; j++)
		{
			// For first lines.
			index = 3*(j+image->width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
			// For last lines.
			index = 3*(j+image->width*(image->height-1-i));
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
		}
	}
}

inline void CorrectImageBordersRawBGR(unsigned char* data, int width, int height, int nbpixborder, unsigned char r0, unsigned char g0, unsigned char b0)
{
	int i = 0, j = 0, index = 0;

	for (j = 0; j < nbpixborder; j++)
	{
		for (i = 0; i < height; i++)
		{
			// For first columns.
			index = 3*(j+width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
			// For last columns.
			index = 3*((width-1-j)+width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
		}
	}

	for (i = 0; i < nbpixborder; i++)
	{
		for (j = nbpixborder; j < width-nbpixborder; j++)
		{
			// For first lines.
			index = 3*(j+width*i);
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
			// For last lines.
			index = 3*(j+width*(height-1-i));
			data[0+index] = b0;
			data[1+index] = g0;
			data[2+index] = r0;
		}
	}
}

/*
Returns the estimated position and dimensions of an orange ball in a picture.

uIplImage* pImg : (IN) pointer to the data of the picture
int *X : (OUT) pointer to the estimated position of the ball (x-axis, between 0 and width)
int *Y : (OUT) pointer to the estimated position of the ball (y-axis, between 0 and height)
int *W : (OUT) pointer to the estimated width
int *H : (OUT) pointer to the estimated height

Returns : EXIT_SUCCESS or EXIT_FAILURE if there is an error
*/
inline int orange_ball_detection(IplImage* pImg, int *X, int *Y, int *W, int *H)	{

	char *p = pImg->imageData;
	int i = 0, j = 0, r = 0, g = 0, b = 0;
	int foundflag = 0;
	int objflag = 0, objwidth = 0, objheight = 0;
	int objX = 0, objY = 0;//center of the object
	int x0 = 0, x1 = 0, y0 = 0, y1 = 0;

	for (i=0;i<pImg->height;i++)	{
		for (j=0;j<pImg->width;j++)	{
			r = (unsigned char)p[0+3*j+3*pImg->width*i];
			g = (unsigned char)p[1+3*j+3*pImg->width*i];
			b = (unsigned char)p[2+3*j+3*pImg->width*i];
			if ( (r>200) && (g<150) && (b<150) )	{//we are on the object
				if (!objflag)	{//it's the beginning of the object at the current line, we were not on it before
					objflag = 1;//we are entering in the object
					foundflag = 1;//says that we have found something in the picture
					x0 = j;//position of the beginning of the object at the current line
				}//else we are somewhere on the object
				else if (j == pImg->width-1)	{//we are on the object but we are at the end of the line, so we do as if we were at the end of the object
					objflag = 0;//we are leaving the object
					x1 = j;//position of the end of the object at the current line
					if ( x1-x0 > objwidth )	{//when objwidth is max, we are at the center of the object
						objwidth = x1-x0;
						objX = x0+objwidth/2;
						if (objY == 0)	{//we are at the beginning of the object on the Y axis
							y0 = i;
						}
						y1 = i;
						objheight = 2*(y1-y0);//*2 because the last time we will be here, we will be on the center
						objY = i;			//(y0 is the beginning of the object and the last value of y1 will be the center)
					}
				}
			}
			else	{
				if (objflag)	{//we were on the object just before, now we are not on it any more
					objflag = 0;//we are leaving the object
					x1 = j;//position of the end of the object at the current line
					if ( x1-x0 > objwidth )	{//when objwidth is max, we are at the center of the object
						objwidth = x1-x0;
						objX = x0+objwidth/2;
						if (objY == 0)	{//we are at the beginning of the object on the Y axis
							y0 = i;
						}
						y1 = i;
						objheight = 2*(y1-y0);//*2 because the last time we will be here, we will be on the center
						objY = i;			//(y0 is the beginning of the object and the last value of y1 will be the center)
					}
				}
			}
		}
	}

	if (foundflag)	{
		//Now we have the center of the object, at (objX,objY), assuming that (0,0) is in the top-left corner
		*X = objX;
		*Y = objY;
		*W = objwidth;
		*H = objheight;
	}
	else	{
		//We did not see any orange ball
		*X = -1;
		*Y = -1;
		*W = -1;
		*H = -1;
	}

	return EXIT_SUCCESS;
}

#endif // !CVPROC_H
