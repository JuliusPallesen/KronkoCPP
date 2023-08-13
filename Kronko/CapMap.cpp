#include "CapMap.h"

CapMap::CapMap(ColorPicker * cp , int max, int map_mode): color_picker(cp), max_amount(max), map_mode(map_mode)
{
}

CapMapping CapMap::createCapMapping(cv::Mat& img, std::vector<cv::Point>& positions, std::vector<Cap>& caps, int circ_px) {
	switch (this->map_mode) {
	case CAP_MAP_HIST:
		return this->createCapMappingHist(img, positions, caps, circ_px);
		break;
	case CAP_MAP_SIMPLE:
		return this->createCapMappingHist(img, positions, caps, circ_px);
		break;
	}
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
	ColorDistanceMap data = getAllDistances(getColorValues(img, positions, circ_px), caps);
	CapMapping mapping(caps.size());
	bool* positions_used = new bool[data.size() + 1];
	std::fill_n(positions_used, data.size() + 1, false);
	int positions_used_num = 0;
	int next_best_i = -1;
	int next_best_j = -1;
	int j = 0;
	double smallest_unused_distance = 9999.99;
	while (positions_used_num <= positions.size()) {
		for (int i = 0; i < data.size(); ++i) // Positions
		{
			if (!positions_used[i])
			{
				//Iterate through the sorted Caps untill we find a cap that doesnt exceed its set max_amount or the max_amount heuristic
				//mapping[std::get<0>(data[i][j])].size() is the amount the cap has already been used.
				while (mapping[std::get<0>(data[i][j])].size() > min(this->max_amount, caps[std::get<0>(data[i][j])].max_amount)) ++j;
				double dist = std::get<1>(data[i][j]);
				if (smallest_unused_distance > dist)
				{
					next_best_i = i;
					next_best_j = j;
					smallest_unused_distance = dist;
				}
			}
			j = 0;
		}
		if (next_best_i == -1 || next_best_j == -1) {
			return mapping;
			//throw std::runtime_error("Not enough caps!");
		}
		else {
			//std::cout << "Distance: " << std::get<1>(data[next_best_i][next_best_j]) << " Cap: " << caps[std::get<0>(data[next_best_i][next_best_j])].brand<< "\n";
			mapping[std::get<0>(data[next_best_i][next_best_j])].push_back(positions[next_best_i]);
			positions_used[next_best_i] = true;
			positions_used_num++;
			next_best_i = -1;
			next_best_j = -1;
			smallest_unused_distance = 9999.99;
		}
	}
	delete[] positions_used;
	return mapping;
}

void CapMap::setMaxAmount(int max_amount)
{
	this->max_amount = max_amount;
}

void CapMap::setColorPicker(ColorPicker* cp)
{
	this->color_picker = cp;
}

void CapMap::setMapMode(int map_mode)
{
	this->map_mode = map_mode;
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
	cv::Vec3i col;
	for (cv::Point & p: positions) {
		try
		{
			colors.push_back(this->color_picker->getColorV(img, p, circ_px));
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << " Trying ColorPoint Picker" << std::endl;
			col = cv::Vec3i(0,0,0);
			try
			{
				col = ColorPoint().getColorV(img, p , circ_px);
			}
			catch (const std::exception& ex)
			{
				std::cerr << ex.what() << " ColorPoint Also Failed, pushing {0,0,0}" << std::endl;
			}
			colors.push_back(Vec3i(0,0,0));
		}
	}
	return colors;
}


