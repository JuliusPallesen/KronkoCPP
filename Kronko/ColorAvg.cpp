#include "ColorAvg.h"

Vec3i ColorAvg::getColorV(Mat& img, Point p, int radius)
{
    Size sz = img.size();
    if (p == Point(-1, -1)) p = Point(sz.width / 2, sz.height / 2);
    if (radius == -1) radius = std::min(sz.width, sz.height) / 2;
    cv::Rect regionOfInterest(p.x - radius, p.y - radius, 2 * static_cast<int>(radius) + 1, 2 * static_cast<int>(radius) + 1);

    if (regionOfInterest.x >= 0 && regionOfInterest.y >= 0 &&
        regionOfInterest.x + regionOfInterest.width <= img.cols &&
        regionOfInterest.y + regionOfInterest.height <= img.rows) {

        cv::Scalar meanColor = cv::mean(img(regionOfInterest));

        return cv::Vec3i(static_cast<int>(meanColor[0]), static_cast<int>(meanColor[1]), static_cast<int>(meanColor[2]));
    }
    else {
        return cv::Vec3i(0, 0, 0);  // Return default color if ROI is near image border
    }
}
