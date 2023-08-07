#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <tuple>
#include "Cap.h"
#include "ColorPicker.h"

using Positions = std::vector<cv::Point>;
using Caps = std::vector<Cap>;
using Colors = std::vector<cv::Vec3i>;
using ColorDistanceMap = std::vector<std::vector<std::tuple<int, double>>>;

class CapMap
{
public:
	CapMap(ColorPicker cp, int max, int r);
	std::vector<std::vector<cv::Point>> createCapMappingSimple(cv::Mat& img, Positions& positions, Caps& caps);
	std::vector<std::vector<cv::Point>> createCapMappingHist(cv::Mat& img, Positions& positions, Caps& caps);

protected:
	ColorPicker color_picker;
	int max_amount;
	int radius;
private:
	ColorDistanceMap getAllDistances(Colors cols, Caps& caps);
	std::vector<std::tuple<int, double>> getColorVDistances(cv::Vec3i col, Caps& caps);
	Colors getColorValues(cv::Mat& img, Positions positions);
};

