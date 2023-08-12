#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <tuple>
#include "Cap.h"
#include "ColorPicker.h"
#include "ColorPoint.h"
#include "Types.h"

class CapMap
{
public:
	CapMap(ColorPicker * cp = new ColorPicker(), int max = INT_MAX);
	CapMapping createCapMappingSimple(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px);
	CapMapping createCapMappingHist(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px);
	void setMaxAmount(int max_amount);
	void setColorPicker(ColorPicker* cp);

protected:
	ColorPicker * color_picker;
	int max_amount;
private:
	ColorDistanceMap getAllDistances(std::vector<cv::Vec3i> cols, std::vector<Cap>& caps);
	std::vector<std::tuple<int, double>> getColorVDistances(cv::Vec3i col, std::vector<Cap>& caps);
	std::vector<cv::Vec3i> getColorValues(cv::Mat& img, std::vector<cv::Point> positions, int circ_px);
};

