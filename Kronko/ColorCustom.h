#pragma once
#include "ColorPicker.h"
class ColorCustom :
    public ColorPicker
{
public:
    cv::Vec3i col;
    ColorCustom(cv::Vec3i c);
    virtual cv::Vec3i getColorV(cv::Mat& img, cv::Point p = cv::Point(-1, -1), int diameter = -1);
};

