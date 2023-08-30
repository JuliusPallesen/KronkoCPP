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
	CapMap();
	CapMap(ColorPicker * cp, int maxPercent = 100, int mapMode = CAP_MAP_SIMPLE);
	CapMapping createCapMapping(cv::Mat& img, std::vector<cv::Point> positions, std::vector<Cap> caps, int circlePixels);
	void setMaxAmount(int maxAmount);
	void setColorPicker(ColorPicker * cp);
	void setMapMode(int mapMode);

protected:
	ColorPicker * colorPicker;
	int maxAmount;
	int mapMode;
private:
	ColorDistanceMap getAllDistances(std::vector<cv::Vec3i> cols, std::vector<Cap>& caps);
	std::vector<std::tuple<int, double>> getColorVDistances(cv::Vec3i col, std::vector<Cap>& caps);
	CapMapping createCapMappingSimple(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circlePixels);
	CapMapping createCapMappingHist(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circlePixels);
	std::vector<cv::Vec3i> getColorValues(cv::Mat& img, std::vector<cv::Point> positions, int circlePixels);
};

