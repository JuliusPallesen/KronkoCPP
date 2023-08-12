#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

class ColorPicker
{
public:
	ColorPicker();
	virtual Vec3i getColorV(Mat &  img, Point p = Point(-1,-1), int diameter = -1.0);
protected:
	bool isInBounds(Size sz, Point p, int diameter);
};

