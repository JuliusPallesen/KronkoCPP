#include "CapMap.h"


CapMap::CapMap(ColorPicker * cp, int max): color_picker(cp), max_amount(max)
{
	this->max_amount = max;
	this->color_picker = cp;
}

CapMapping CapMap::createCapMappingSimple(cv::Mat& img, std::vector<cv::Point> & positions, std::vector<Cap>& caps, int circ_px) {
	ColorDistanceMap data = getAllDistances(getColorValues(img, positions, circ_px), caps);
	std::vector<std::vector<cv::Point>> mapping(caps.size());
	for (int i = 0; i < data.size(); ++i) {
		mapping[std::get<0>(data[i][0])].push_back(positions[i]);
	}
	return mapping;
}

CapMapping CapMap::createCapMappingHist(cv::Mat & img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px) {
	//TODO: fix
	ColorDistanceMap data = getAllDistances(getColorValues(img, positions, circ_px), caps);
	CapMapping mapping(caps.size());
	bool* positions_used = new bool[data.size() + 1];
	std::fill_n(positions_used, data.size() + 1, false);
	int positions_used_num = 0;
	int next_best_i = 0;
	int next_best_j = 0;
	int j = 0;
	double smallest_unused_distance = 9999.99;
	while (positions_used_num <= positions.size()) {
		for (int i = 0; i < data.size(); ++i) // Positions
		{
			if (!positions_used[i])
			{
				while (mapping[std::get<0>(data[i][j])].size() > this->max_amount) ++j; // Caps
				double dist = std::get<1>(data[i][j]);
				if (smallest_unused_distance > dist)
				{
					next_best_i = i;
					next_best_j = j;
					smallest_unused_distance = dist;
				}
			}
			mapping[std::get<0>(data[next_best_i][next_best_j])].push_back(positions[next_best_i]);
			positions_used[next_best_i] = true;
			positions_used_num++;
			smallest_unused_distance = 9999.99;
			j = 0;
		}
	}
	delete[] positions_used;
	return mapping;
}


ColorDistanceMap CapMap::getAllDistances(std::vector<cv::Vec3i> cols, std::vector<Cap>& caps) {
	ColorDistanceMap data;
	for (cv::Vec3i & color: cols) {
		data.push_back(this->getColorVDistances(color, caps));
	}
	return data;
}

std::vector<std::tuple<int,double>> CapMap::getColorVDistances(cv::Vec3i col, std::vector<Cap>& caps) {
	std::vector<std::tuple<int, double>> distance_map;
	double euclidian_distance;
	for (int i = 0; i < caps.size(); ++i) {
		euclidian_distance = cv::norm(col-caps[i].color);
		distance_map.push_back(std::tuple(i, euclidian_distance));
	}
	std::sort(distance_map.begin(), distance_map.end(), [](const auto& t1, const auto& t2) {
		return std::get<1>(t1) < std::get<1>(t2);
		});
	return distance_map;
}
std::vector<cv::Vec3i> CapMap::getColorValues(cv::Mat& img, std::vector<cv::Point> positions, int circ_px) {
	std::vector<cv::Vec3i> colors;
	for (cv::Point & p: positions) {
		colors.push_back(this->color_picker->getColorV(img, p, circ_px));
	}
	return colors;
}


