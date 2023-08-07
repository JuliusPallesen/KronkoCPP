#include "TriangleLayouter.h"

std::vector<cv::Point> TriangleLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	//TODO: Implement Triangular Circle Packing
	int circ_px = (int)(((double)imgDims.width / frameWidth) * this->CAP_SIZE);
	std::vector<cv::Point> positions;
	return positions;
};