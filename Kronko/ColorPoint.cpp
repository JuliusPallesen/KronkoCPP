#include "ColorPoint.h"

Vec3i ColorPoint::getColorV(Mat &img, Point p, double radius)
{
	Size sz = img.size();
	if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
	if (radius == -1) radius = std::min(sz.width,sz.height)/2;
    return img.at<Vec3i>(p);
}
