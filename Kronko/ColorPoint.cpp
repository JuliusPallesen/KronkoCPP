#include "ColorPoint.h"

ColorPoint::ColorPoint()
{
}

Vec3i ColorPoint::getColorV(Mat &img, Point p, int diameter)
{
	Size sz = img.size();
	if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
	if (p.x <= sz.width  &&
		p.x >= 0		 &&
		p.y <= sz.height &&
		p.y >= 0) 
	{
		cv::Vec4b col = img.at<Vec4b>(p);
		return Vec3i(static_cast<int>(col[0]), static_cast<int>(col[1]), static_cast<int>(col[2]));
	}
	else {
		throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x) +
			" Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) +
			" Diameter: " + std::to_string(diameter));
	}
}
