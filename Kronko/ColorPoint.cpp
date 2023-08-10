#include "ColorPoint.h"

ColorPoint::ColorPoint()
{
}

Vec3i ColorPoint::getColorV(Mat &img, Point p, int diameter)
{
	Size sz = img.size();
	if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
	Vec3i color = Vec3i(img.at<Vec3b>(p));
	return color;
}
