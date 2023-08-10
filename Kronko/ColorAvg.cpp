#include "ColorAvg.h"

ColorAvg::ColorAvg()
{
}

Vec3i ColorAvg::getColorV(Mat& img, Point p, int diameter)
{
    Size sz = img.size();
    int radius = diameter / 2;
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (diameter == -1) diameter = std::min(sz.width, sz.height);
    cv::Rect roi = cv::Rect(p.x-radius, p.y-radius, diameter + 1, diameter + 1);
    cv::Mat mask = cv::Mat::zeros(img.size(), CV_8U);
    cv::circle(mask, p, radius, cv::Scalar(255), -1);
    if (roi.x >= 0 && roi.y >= 0 &&
        roi.x + roi.width <= img.cols &&
        roi.y + roi.height <= img.rows) 
    {
        cv::Scalar meanColor = cv::mean(img,mask);
        std::cout << "Avg Scalar: " << meanColor << std::endl;
        return cv::Vec3i(
            static_cast<int>(meanColor[2]), 
            static_cast<int>(meanColor[1]), 
            static_cast<int>(meanColor[0])
        );
    }
    else {
        throw std::runtime_error("Index out of bounds");
        return cv::Vec3i(0, 0, 0);  // Return default color if ROI is near image border
    }
}
