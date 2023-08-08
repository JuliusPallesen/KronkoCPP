#include "ColorAvg.h"

Vec3i ColorAvg::getColorV(Mat& img, Point p, double radius)
{
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (radius == -1) radius = std::min(sz.width, sz.height) / 2;
    cv::Rect regionOfInterest(p.x - radius, p.y - radius, 2 * radius + 1, 2 * radius + 1);
    cv::Scalar meanColor = cv::mean(img(regionOfInterest));

    return cv::Vec3i(static_cast<int>(meanColor[0]), static_cast<int>(meanColor[1]), static_cast<int>(meanColor[2]));
}
