#include "ColorCustom.h"

ColorCustom::ColorCustom(Vec3i c): col(c)
{
    this->col = c;
}

Vec3i ColorCustom::getColorV(Mat& img, Point p, int diameter)
{
    return this->col;
}
