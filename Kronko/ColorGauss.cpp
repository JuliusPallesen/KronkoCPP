#include "ColorGauss.h"

Vec3i ColorGauss::getColorV(Mat& img, Point p, int radius)
{
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (radius == -1) radius = std::min(sz.width, sz.height) / 2;
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(2 * static_cast<int>(radius) + 1, 2 * static_cast<int>(radius) + 1), 0);

    if (p.x >= radius && p.x < img.cols - radius && p.y >= radius && p.y < img.rows - radius) {
        cv::Vec3b pixel = blurred.at<cv::Vec3b>(p.y, p.x);

        return cv::Vec3i(pixel[0], pixel[1], pixel[2]);
    }
    else {
        return cv::Vec3i(0, 0, 0);  // Return default color if point is near image border
    }
}
