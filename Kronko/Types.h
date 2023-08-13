#pragma once

#define CAP_COLOR_GAUSS	1
#define CAP_COLOR_POINT	2
#define CAP_COLOR_AVG	3
#define CAP_COLOR_CUSTOM 4

#define CAP_MAP_SIMPLE 0
#define CAP_MAP_HIST 1

// Bottlecaps have a 26mm diameter
const int CAP_SIZE = 26;

using ColorDistanceMap = std::vector<std::vector<std::tuple<int, double>>>;
using CapMapping = std::vector<std::vector<cv::Point>>;
