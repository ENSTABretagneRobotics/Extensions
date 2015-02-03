#ifndef MAINDETECTIONOBSTACLE_H
#define MAINDETECTIONOBSTACLE_H

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
////#include <unistd.h>
//#include <iostream>
#include "Horizon.h"
#include "Obstacle.h"
#include "ToolsObs.h"
cv::Point2f detectObstacle(cv::Mat src, char weather, int boatSize);
#endif // MAINDETECTIONOBSTACLE_H
