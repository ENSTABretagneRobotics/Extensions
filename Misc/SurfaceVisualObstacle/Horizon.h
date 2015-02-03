#ifndef HORIZON_H
#define HORIZON_H

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
////#include <unistd.h>
//#include <iostream>
#include "CvUtils.h"


using namespace cv;

cv::Mat initializeImage(cv::Mat src, int boatSize);

vector <Point> cannyHough(cv::Mat src, int line_length, int difference);

cv::Mat estimateHorizon(Vec2f houghCoef, cv::Mat src, int boatSize);


#endif // HORIZON_H
