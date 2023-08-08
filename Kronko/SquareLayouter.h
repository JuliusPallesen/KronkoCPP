#pragma once
#include "CapLayoutManager.h"

class SquareLayouter :
    public CapLayoutManager
{
public:
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
    std::vector<cv::Point> createLayoutmm(cv::Mat& img, int frameWidth) override;
};