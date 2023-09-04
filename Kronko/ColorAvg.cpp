#include "ColorAvg.h"

ColorAvg::ColorAvg()
{
}

//still pretty slow
cv::Vec3i ColorAvg::getColorV(cv::Mat& img, cv::Point p, int diameter)
{
    cv::Size sz = img.size();
    if (p == cv::Point(-1, -1)) p = cv::Point(sz.width / 2, sz.height / 2);
    if (diameter == -1) diameter = std::min(sz.width-1, sz.height-1) -1;
    if (ColorPicker::isInBounds(img.size(), p, diameter)) 
    {
        //Combine Circle Mask with images Alphachannel
        cv::Mat mask = cv::Mat::zeros(img.size(), CV_8U);
        cv::circle(mask, p, diameter/2, cv::Scalar(255), -1);
        cv::Mat alphaChannel;
        cv::extractChannel(img, alphaChannel, 3);
        cv::bitwise_and(mask, alphaChannel, mask);
        cv::Scalar meanColor = mean(img,mask);
        return cv::Vec3i(
            static_cast<int>(meanColor[0]), 
            static_cast<int>(meanColor[1]), 
            static_cast<int>(meanColor[2])
        );
    }
    else {
        throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x)+ 
                                  " Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) + 
                                  " Diameter: " + std::to_string(diameter));
    }
}
