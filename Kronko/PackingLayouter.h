#pragma once
#include "CapLayoutManager.h"

class PackingLayouter :
    public CapLayoutManager
{
public:
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
};