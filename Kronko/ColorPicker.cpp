#include "ColorPicker.h"
#include <iostream>

ColorPicker::ColorPicker(){}

cv::Vec3i ColorPicker::getColorV(Mat & img, Point p, double radius)
{
    std::cerr << "[ColorPicker::getColorV] Should'nt be called." << std::endl;
    return cv::Vec3i(0,0,0);
}