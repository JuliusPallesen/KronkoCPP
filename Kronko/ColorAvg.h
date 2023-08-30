#pragma once
#include "ColorPicker.h"
class ColorAvg :
    public ColorPicker
{
public:
    ColorAvg();
    cv::Vec3i getColorV(cv::Mat& img, cv::Point p = cv::Point(-1, -1), int diameter = -1) override;
};