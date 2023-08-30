#pragma once
#include "CapLayoutManager.h"

class SquareLayouter :
    public CapLayoutManager
{
public:
    SquareLayouter();
    ~SquareLayouter();
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
};