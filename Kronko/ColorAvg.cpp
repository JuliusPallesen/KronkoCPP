#include "ColorAvg.h"

ColorAvg::ColorAvg()
{
}

Vec3i ColorAvg::getColorV(Mat& img, Point p, int diameter)
{
    using namespace cv;
    Size sz = img.size();
    int radius = diameter / 2 + (diameter % 2) ;
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (diameter == -1) diameter = std::min(sz.width-1, sz.height-1);
    Rect roi = Rect(p.x-radius, p.y-radius, diameter + 1, diameter + 1);
    if (roi.x >= 0 && roi.y >= 0 &&
        roi.x + roi.width <= img.cols &&
        roi.y + roi.height <= img.rows) 
    {
        //Combine Circle Mask with images Alphachannel
        Mat mask = Mat::zeros(img.size(), CV_8U);
        circle(mask, p, radius, Scalar(255), -1);
        Mat alphaChannel;
        extractChannel(img, alphaChannel, 3);
        bitwise_and(mask, alphaChannel, mask);
        Scalar meanColor = mean(img,mask);
        return cv::Vec3i(
            static_cast<int>(meanColor[2]), 
            static_cast<int>(meanColor[1]), 
            static_cast<int>(meanColor[0])
        );
    }
    else {
        throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x)+ 
                                  " Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) + 
                                  " Diameter: " + std::to_string(diameter));
    }
}
