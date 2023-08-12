#include "ColorGauss.h"

ColorGauss::ColorGauss()
{
}

Vec3i ColorGauss::getColorV(Mat& img, Point p, int diameter)
{
    Vec3i color = Vec3i(0,0,0);
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (diameter == -1) diameter = std::min(sz.width, sz.height) / 2;
    if (isInBounds(sz, p, diameter)) {
        int kernelSize = static_cast<int>(2 * diameter) + 1;  // Ensure kernel size is odd
        cv::Mat1d gaussKernel = cv::getGaussianKernel(kernelSize, 1.0, CV_64F);
        try
        {
            color = calcGaussAtPx(img, gaussKernel, p);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Index out of bounds:" + std::to_string(p.x) + "," + std::to_string(p.x) +
                " Img size: " + std::to_string(sz.width) + "/" + std::to_string(sz.height) +
                " Diameter: " + std::to_string(diameter));
        }
    }
    return color;
}

Vec3i ColorGauss::calcGaussAtPx(Mat & img, Mat1d & kernel, Point p) {
    Vec3d gaussValue(0.0,0.0,0.0);
    Vec4b cVal;
    Size imgsize = img.size();
    int kernelsize = static_cast<int>(sqrt(kernel.rows));
    if ( isInBounds(imgsize,p,kernelsize) ) {
        for (int x = 0 ; x < kernel.rows; x++)
        {
            int y = x / kernelsize;
            double factor = kernel(x);
            cVal = img.at<Vec4b>(p.x + x - (kernelsize / 2), p.y + y - (kernelsize / 2));
            gaussValue[0] = gaussValue[0] + factor * (cVal[3]/255) * cVal[2];
            gaussValue[1] = gaussValue[1] + factor * (cVal[3]/255) * cVal[1];
            gaussValue[2] = gaussValue[2] + factor * (cVal[3]/255) * cVal[0];
        }
    }
    else {
        throw std::runtime_error("Index out of bounds");
    }
    return Vec3i(static_cast<int>(gaussValue[0]), static_cast<int>(gaussValue[1]), static_cast<int>(gaussValue[2]));
}
