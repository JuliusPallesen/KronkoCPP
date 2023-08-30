#include "SquareLayouter.h"

SquareLayouter::SquareLayouter()
{
}

SquareLayouter::~SquareLayouter()
{
}

std::vector<cv::Point> SquareLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	int circ_px = (int)(((float)imgDims.width / (float)frameWidth) * CAP_SIZE);
	std::vector<cv::Point> positions;
	if (circ_px <= 0) {
		throw std::runtime_error("Width too small.");
	}
	else {
		for (int x = circ_px / 2; x < imgDims.width - (circ_px / 2); x = x + circ_px)
		{
			for (int y = circ_px / 2; y < imgDims.height - (circ_px / 2); y = y + circ_px)
			{
				positions.push_back(cv::Point(x, y));
			}
		}
	}
	return positions;
}
