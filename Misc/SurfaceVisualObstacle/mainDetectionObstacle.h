#ifndef MAINDETECTIONOBSTACLE_H
#define MAINDETECTIONOBSTACLE_H

#include "Horizon.h"
#include "Obstacle.h"
#include "ToolsObs.h"

cv::Point2f detectObstacle(cv::Mat src, char weather, int boatSize);

#endif // MAINDETECTIONOBSTACLE_H
