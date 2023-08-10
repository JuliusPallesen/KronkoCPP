#include "ColorGauss.h"

ColorGauss::ColorGauss()
{
}

Vec3i ColorGauss::getColorV(Mat& img, Point p, int diameter)
{
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (diameter == -1) diameter = std::min(sz.width, sz.height) / 2;
    cv::Mat blurred;
    int kernelSize = static_cast<int>(2 * diameter) + 1;  // Ensure kernel size is odd
    std::cout << kernelSize << std::endl;
    cv::Mat1d gaussKernel = cv::getGaussianKernel(kernelSize, 1.0, CV_64F);
    return calcGaussAtPx(img,gaussKernel,p);
}

Vec3i ColorGauss::calcGaussAtPx(Mat & img, Mat1d & kernel, Point p) {
    Vec3d gaussValue(0.0,0.0,0.0);
    Vec4b cVal;
    Size imgsize = img.size();
    int kernelsize = kernel.rows;
    if (
        p.x + (kernelsize / 2) <= imgsize.width   &&
        p.x - (kernelsize / 2) >= 0               &&
        p.y + (kernelsize / 2) <= imgsize.height  &&
        p.x - (kernelsize / 2) >= 0
        ) {
        for (int x = 0 ; x < kernelsize; x++)
        {
            int y = x / static_cast<int>(sqrt(kernelsize));
            double factor = kernel(x);
            cVal = img.at<Vec4b>(p.x + x - (kernelsize / 2), p.y + y - (kernelsize / 2));
            gaussValue[0] = gaussValue[0] + factor * (cVal[3] / 255) * cVal[2];
            gaussValue[1] = gaussValue[1] + factor * (cVal[3]/255) * cVal[1];
            gaussValue[2] = gaussValue[2] + factor * (cVal[3]/255) * cVal[0];
        }
    }
    else {
        throw std::runtime_error("Index out of bounds");
    }
    return Vec3i(static_cast<int>(gaussValue[0]), static_cast<int>(gaussValue[1]), static_cast<int>(gaussValue[2]));
}
