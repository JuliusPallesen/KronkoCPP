#pragma once
#include "CapLayoutManager.h"

class TriangleLayouter :
    public CapLayoutManager
{
public:
    TriangleLayouter();
    ~TriangleLayouter();
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
};

