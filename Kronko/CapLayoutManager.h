#pragma once
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Types.h"

class CapLayoutManager
{
public:
	~CapLayoutManager();
	virtual std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth);
protected:
};

