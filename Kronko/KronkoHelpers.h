#pragma once
#include "Types.h"
#include <opencv2/opencv.hpp>

void conditionalResize(cv::Mat& img, int wdth_res);

int getCircleSizePx(cv::Mat img, int width_mm);

cv::Mat readimGBRA(std::string path);