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
	CapMap(ColorPicker * cp = new ColorPicker(), int max = INT_MAX, int map_mode = CAP_MAP_SIMPLE);
	CapMapping createCapMapping(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px);
	void setMaxAmount(int max_amount);
	void setColorPicker(ColorPicker* cp);
	void setMapMode(int map_mode);

protected:
	ColorPicker * color_picker;
	int max_amount;
	int map_mode;
private:
	ColorDistanceMap getAllDistances(std::vector<cv::Vec3i> cols, std::vector<Cap>& caps);
	std::vector<std::tuple<int, double>> getColorVDistances(cv::Vec3i col, std::vector<Cap>& caps);
	CapMapping createCapMappingSimple(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px);
	CapMapping createCapMappingHist(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px);
	std::vector<cv::Vec3i> getColorValues(cv::Mat& img, std::vector<cv::Point> positions, int circ_px);
};

