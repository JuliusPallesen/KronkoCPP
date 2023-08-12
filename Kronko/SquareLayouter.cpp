#include "SquareLayouter.h"

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
std::vector<cv::Point> SquareLayouter::createLayoutmm(cv::Mat& img, int frameWidth)
{
	cv::Size img_size = img.size();
	int new_width = (frameWidth / CAP_SIZE) * 100;
	double scale_factor = (double)new_width / double(img_size.width);
	img_size = cv::Size2d(new_width, (int)img_size.height * scale_factor);
	cv::resize(img, img, img_size, cv::INTER_AREA);
	return createLayout(img_size,frameWidth);
}
;