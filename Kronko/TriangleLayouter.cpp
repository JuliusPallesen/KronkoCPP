#include "TriangleLayouter.h"

TriangleLayouter::TriangleLayouter()
{
}

std::vector<cv::Point> TriangleLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	int circ_px = (int)(((float)imgDims.width / (float)frameWidth) * CAP_SIZE);
	double radius = static_cast<double>(circ_px / 2.0);
	int horizontal_offset = static_cast<int>(radius*sqrt(3));
	int x_index = 0;
	std::cout << radius << std::endl;
	std::cout << horizontal_offset << std::endl;
	std::vector<cv::Point> positions;
	if (circ_px <= 0) {
		throw std::runtime_error("Width too small.");
	}
	else {
		for (int x = circ_px / 2; x < imgDims.width - (circ_px / 2); x += horizontal_offset)
		{
			for (int y = circ_px / 2; y < imgDims.height - (circ_px / 2) - static_cast<int>(radius * (x_index % 2)); y += circ_px)
			{
				positions.push_back(cv::Point(x ,y + static_cast<int>(radius * (x_index % 2))));
			}
			x_index++;
		}
	}
	return positions;
}
std::vector<cv::Point> TriangleLayouter::createLayoutmm(cv::Mat& img, int frameWidth)
{
	return std::vector<cv::Point>();
}
;