#include "SquareLayouter.h"

std::vector<cv::Point> SquareLayouter::createLayout(cv::Size imgDims, int frameWidth) {
	int circ_px = (int)(((float)imgDims.width / (float)frameWidth) * this->CAP_SIZE);
	std::cout << "Pixels in a Circle in SqLayouter: " << circ_px << std::endl;
	std::vector<cv::Point> positions;
	for (int x = circ_px/2; x < imgDims.width; x = x + circ_px)
	{
		for (int y = circ_px/2; y < imgDims.height; y = y + circ_px)
		{
			positions.push_back(cv::Point(x, y));
		}
	}
	return positions;
};