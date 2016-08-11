#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "CvUtils.h"

cv::Mat obsInit(cv::Mat srcCroppedHD, bool show, char weather);

cv::Point2f seaContour(cv::Mat srcFiltered, cv::Mat srcCroppedToDraw);

float obstacleDetected(cv::Point2f massCenter, cv::Mat srcCroppedHorizon);

#endif // OBSTACLE_H
