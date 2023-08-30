#pragma once
#include "ColorPicker.h"
class ColorGauss :
    public ColorPicker
{
public:
    ColorGauss();
    cv::Vec3i getColorV(cv::Mat& img, cv::Point p = cv::Point(-1, -1), int diameter = -1) override;
private:
    cv::Vec3i calcGaussAtPx(cv::Mat& img, cv::Mat1d& kernel, cv::Point p);
};

