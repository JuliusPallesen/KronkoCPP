#include "ColorPoint.h"

ColorPoint::ColorPoint()
{
}

cv::Vec3i ColorPoint::getColorV(cv::Mat &img, cv::Point p, int diameter)
{
	cv::Size sz = img.size();
	if (p == cv::Point(-1, -1)) p = cv::Point(sz.width / 2, sz.height / 2);
	if (ColorPicker::isInBounds(sz,p,diameter)) {
		cv::Vec4b col = img.at<cv::Vec4b>(p);
		return cv::Vec3i(static_cast<int>(col[0]), static_cast<int>(col[1]), static_cast<int>(col[2]));
	}
	else {
		throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x) +
			" Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) +
			" Diameter: " + std::to_string(diameter));
	}
}
