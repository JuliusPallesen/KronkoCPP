#include "PackingLayouter.h"

PackingLayouter::PackingLayouter()
{
}

PackingLayouter::~PackingLayouter()
{
}

std::vector<cv::Point> PackingLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	// TODO: Optimal Algorithm for packing Circles of equal Radii in Rectangle
	int circ_px = imgDims.width / (frameWidth / CAP_SIZE);
	return std::vector<cv::Point>();
}