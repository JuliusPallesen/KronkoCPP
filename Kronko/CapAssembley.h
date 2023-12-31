#pragma once
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>
#include "Types.h"
#include "Cap.h"

void overlayImage(cv::Mat& img, cv::Mat& capimg, cv::Point position, bool scramble = false);

void assembleMapping(cv::Mat& img, CapMapping map, std::vector<Cap> caps, int circ_px, bool scramble = false);