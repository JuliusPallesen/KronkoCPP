#include "ColorPicker.h"

ColorPicker::ColorPicker(){}

cv::Vec3i ColorPicker::getColorV(cv::Mat & img, cv::Point p, int diameter)
{
    throw std::runtime_error("[ColorPicker::getColorV] Called Virtual Function");
    return cv::Vec3i(0,0,0);
}

bool ColorPicker::isInBounds(cv::Size sz, cv::Point p, int diameter)
{
    int radius = (diameter / 2);
    return ((p.x + radius < sz.width)   && 
            (p.x - radius >= 0)         &&
            (p.y + radius < sz.height)  && 
            (p.y - radius >= 0));
}
