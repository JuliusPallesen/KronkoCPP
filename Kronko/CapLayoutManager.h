#pragma once
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Types.h"

class CapLayoutManager
{
public:
	// returns the center points of all bottlecaps
	virtual std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth);
	virtual std::vector<cv::Point> createLayoutmm(cv::Mat & img, int frameWidth);
protected:
};

