#pragma once
#include "CapLayoutManager.h"

class PackingLayouter :
    public CapLayoutManager
{
public:
    PackingLayouter();
    ~PackingLayouter();
    std::vector<cv::Point> createLayout(cv::Size imgDims, int frameWidth) override;
};