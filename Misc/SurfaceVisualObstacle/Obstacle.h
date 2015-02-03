#ifndef OBSTACLE_H
#define OBSTACLE_H

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
////#include <unistd.h>
//#include <iostream>
#include "CvUtils.h"


using namespace cv;


cv::Mat obsInit(cv::Mat srcCroppedHD, bool show, char weather);

Point2f seaContour(cv::Mat srcFiltered, cv::Mat srcCroppedToDraw);

float obstacleDetected(Point2f massCenter, cv::Mat srcCroppedHorizon);


#endif // OBSTACLE_H
