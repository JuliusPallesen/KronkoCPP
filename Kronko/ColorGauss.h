#pragma once
#include "ColorPicker.h"
class ColorGauss :
    public ColorPicker
{
public:
    ColorGauss();
    Vec3i getColorV(Mat& img, Point p = Point(-1, -1), int diameter = -1) override;
private:
    Vec3i calcGaussAtPx(Mat& img, Mat1d& kernel, Point p);
};

