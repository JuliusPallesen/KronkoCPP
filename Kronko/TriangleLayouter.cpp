#include "TriangleLayouter.h"

std::vector<cv::Point> TriangleLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	//TODO: Implement Triangular Circle Packing
	int circ_px = (int)(((double)imgDims.width / frameWidth) * CAP_SIZE);
	std::vector<cv::Point> positions;
	return positions;
}
std::vector<cv::Point> TriangleLayouter::createLayoutmm(cv::Mat& img, int frameWidth)
{
	return std::vector<cv::Point>();
}
;