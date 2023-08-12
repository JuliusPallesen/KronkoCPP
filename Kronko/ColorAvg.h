#pragma once
#include "ColorPicker.h"
class ColorAvg :
    public ColorPicker
{
public:
    ColorAvg();
    Vec3i getColorV(Mat& img, Point p = Point(-1, -1), int diameter = -1) override;
};