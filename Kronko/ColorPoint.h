#pragma once
#include "ColorPicker.h"
class ColorPoint :
    public ColorPicker
{
public:
    ColorPoint();
    Vec3i getColorV(Mat& img, Point p = Point(-1, -1), int diameter = -1) override;
};

