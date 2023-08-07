#pragma once
#include <vector>
#include <iostream>
#include <opencv2\core\core.hpp>

class CapLayoutManager
{
public:
	// returns the center points of all bottlecaps
	virtual std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth);
protected:
	// Size of a bottle cap in mm
	const int CAP_SIZE = 26; 
};

