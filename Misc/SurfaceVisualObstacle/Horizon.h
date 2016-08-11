#ifndef HORIZON_H
#define HORIZON_H

#include "CvUtils.h"

cv::Mat initializeImage(cv::Mat src, int boatSize);

std::vector<cv::Point> cannyHough(cv::Mat src, int line_length, int difference);

cv::Mat estimateHorizon(cv::Vec2f houghCoef, cv::Mat src, int boatSize);

#endif // HORIZON_H
