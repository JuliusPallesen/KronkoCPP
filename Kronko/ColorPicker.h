#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

class ColorPicker
{
public:
	ColorPicker();
	virtual cv::Vec3i getColorV(cv::Mat &  img, cv::Point p = cv::Point(-1,-1), int diameter = -1);
protected:
	bool isInBounds(cv::Size sz, cv::Point p, int diameter);
};

