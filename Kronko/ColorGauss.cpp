#include "ColorGauss.h"

ColorGauss::ColorGauss()
{
}

Vec3i ColorGauss::getColorV(Mat& img, Point p, int diameter)
{
    Vec3i color = Vec3i(0,0,0);
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point((sz.width / 2), (sz.height / 2));
    if (diameter == -1) diameter = std::min(sz.width - 1, sz.height -1) -1;
    int kernelSize = static_cast<int>(diameter);
    kernelSize -= ((kernelSize % 2) == 0) ? 1 : 0; // Ensure kernel size is odd
    if (ColorPicker::isInBounds(sz, p, kernelSize)) {
        cv::Mat1d gaussKernel = cv::getGaussianKernel(kernelSize, 1.0, CV_64F);
        try
        {
            color = calcGaussAtPx(img, gaussKernel, p);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x) +
                " Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) +
                " Diameter: " + std::to_string(diameter) + "Thrown at: " + e.what());
        }
    }
    else {
        throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x) +
            " Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) +
            " Diameter: " + std::to_string(diameter));
    }
    return color;
}

Vec3i ColorGauss::calcGaussAtPx(Mat & img, Mat1d & kernel, Point p) {
    Vec3d gaussValue(0.0,0.0,0.0);
    Vec4b cVal;
    Size imgsize = img.size();
    double x_factor = 0.0;
    double y_factor = 0.0;
    int r = kernel.rows / 2;
    for (int x = 0 ; x < kernel.rows; x++)
    {
        x_factor = kernel(x);
        for (int y = 0; y < kernel.rows; y++)
        {
            y_factor = kernel(y);
            int x_pos = p.x + x - r;
            int y_pos = p.y + y - r;
            cVal = img.at<Vec4b>(y_pos, x_pos);
            //                              Gauss Kernel dims     |     alpha       | RGB
            gaussValue[0] = gaussValue[0] + (x_factor * y_factor) * (cVal[3] / 255) * cVal[0];
            gaussValue[1] = gaussValue[1] + (x_factor * y_factor) * (cVal[3] / 255) * cVal[1];
            gaussValue[2] = gaussValue[2] + (x_factor * y_factor) * (cVal[3] / 255) * cVal[2];
        }
            
    }
    return Vec3i(static_cast<int>(gaussValue[0]), static_cast<int>(gaussValue[1]), static_cast<int>(gaussValue[2]));
}
