#pragma once
#include "CapLayoutManager.h"

class TriangleLayouter :
    public CapLayoutManager
{
public:
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
};

