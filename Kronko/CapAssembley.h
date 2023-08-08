#pragma once
#include <opencv2/opencv.hpp>
#include "Types.h"
#include "Cap.h"

void overlayImage(cv::Mat& img1, cv::Mat& img2, cv::Point position, int size);

void assembleMapping(cv::Mat& img, CapMapping map, std::vector<Cap> caps, int circ_px);