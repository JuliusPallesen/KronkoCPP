#pragma once

// Bottlecaps have a 26mm diameter
const int CAP_SIZE = 26;

using Positions = std::vector<cv::Point>;
using Caps = std::vector<Cap>;
using Colors = std::vector<cv::Vec3i>;
using ColorDistanceMap = std::vector<std::vector<std::tuple<int, double>>>;
using CapMapping = std::vector<std::vector<cv::Point>>;
