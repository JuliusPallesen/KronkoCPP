#pragma once
#include "ColorPicker.h"
class ColorCustom :
    public ColorPicker
{
public:
    Vec3i col;
    ColorCustom(Vec3i c);
    virtual Vec3i getColorV(Mat& img, Point p = Point(-1, -1), double radius = -1.0);
};

