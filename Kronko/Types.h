#pragma once

#define CAP_BRAND	"Brand"
#define CAP_PATH	"Path"
#define CAP_PRIO	"Priority"
#define CAP_COLOR	"Color"
#define CAP_DIR		"Direction"
#define CAP_ID		"ID"
#define CAP_MAX		"Amount"

// Bottlecaps have a 26mm diameter
const int CAP_SIZE = 26;

using Positions = std::vector<cv::Point>;
using Caps = std::vector<Cap>;
using Colors = std::vector<cv::Vec3i>;
using ColorDistanceMap = std::vector<std::vector<std::tuple<int, double>>>;
using CapMapping = std::vector<std::vector<cv::Point>>;
