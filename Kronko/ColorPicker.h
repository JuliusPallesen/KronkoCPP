#pragma once
#include <opencv2/core/core.hpp>
using namespace cv;

class ColorPicker
{
public:
	ColorPicker();
	virtual Vec3i getColorV(Mat &  img, Point p = Point(-1,-1), double radius = -1.0);
};

