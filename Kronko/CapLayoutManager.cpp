#include "CapLayoutManager.h"

CapLayoutManager::~CapLayoutManager()
{
}

std::vector<cv::Point> CapLayoutManager::createLayout(cv::Size imgDims, int frameWidth)
{
	throw std::runtime_error("[CapLayoutManager] Called a virtual Function");
	return std::vector<cv::Point>();
}

