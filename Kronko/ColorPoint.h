#pragma once
#include "ColorPicker.h"
class ColorPoint :
    public ColorPicker
{
public:
    ColorPoint();
    cv::Vec3i getColorV(cv::Mat& img, cv::Point p = cv::Point(-1, -1), int diameter = -1) override;
};

