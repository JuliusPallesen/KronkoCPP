#pragma once
#include "ColorPicker.h"
class ColorPoint :
    public ColorPicker
{
public:
    using ColorPicker::ColorPicker;
    Vec3i getColorV(Mat& img, Point p = Point(-1, -1), int radius = -1.0) override;
};

