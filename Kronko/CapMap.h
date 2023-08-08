#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <tuple>
#include "Cap.h"
#include "ColorPicker.h"
#include "Types.h"

class CapMap
{
public:
	CapMap(ColorPicker * cp, int max);
	CapMapping createCapMappingSimple(cv::Mat& img, Positions& positions, Caps& caps);
	CapMapping createCapMappingHist(cv::Mat& img, Positions& positions, Caps& caps);

protected:
	ColorPicker * color_picker;
	int max_amount;
private:
	ColorDistanceMap getAllDistances(Colors cols, Caps& caps);
	std::vector<std::tuple<int, double>> getColorVDistances(cv::Vec3i col, Caps& caps);
	Colors getColorValues(cv::Mat& img, Positions positions);
};

