#include "CapLayoutManager.h"

std::vector<cv::Point> CapLayoutManager::createLayout(cv::Size imgDims, int frameWidth)
{
	throw std::runtime_error("Called a virtual Function");
	return std::vector<cv::Point>();
}

std::vector<cv::Point> CapLayoutManager::createLayoutmm(cv::Mat& img, int frameWidth)
{
	throw std::runtime_error("Called a virtual Function");
	return std::vector<cv::Point>();
}
