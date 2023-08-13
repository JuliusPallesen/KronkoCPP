#pragma once
#include "CapLayoutManager.h"

class TriangleLayouter :
    public CapLayoutManager
{
public:
    TriangleLayouter();
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
    std::vector<cv::Point> createLayoutmm(cv::Mat& img, int frameWidth) override;
};

