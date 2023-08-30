#include "ColorCustom.h"

ColorCustom::ColorCustom(cv::Vec3i c): col(c)
{
    this->col = c;
}

cv::Vec3i ColorCustom::getColorV(cv::Mat& img, cv::Point p, int diameter)
{
    return this->col;
}
