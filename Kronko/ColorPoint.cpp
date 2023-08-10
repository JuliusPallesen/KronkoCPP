#include "ColorPoint.h"

ColorPoint::ColorPoint()
{
}

Vec3i ColorPoint::getColorV(Mat &img, Point p, int diameter)
{
	Size sz = img.size();
	if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
	if (p.x <= sz.width &&
		p.x >= 0		&&
		p.y <= sz.width &&
		p.x >= 0) 
	{
		return Vec3i(img.at<Vec3b>(p));
	}
	else {
		throw std::runtime_error("Index out of bounds!");
	}
}
