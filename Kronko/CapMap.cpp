#include "CapMap.h"

CapMap::CapMap(): colorPicker(new ColorPoint), maxAmount(50), mapMode(CAP_MAP_SIMPLE)
{
}

CapMap::CapMap(ColorPicker *  cp , int maxPercent, int mapMode): colorPicker(cp), maxAmount(maxPercent), mapMode(mapMode)
{
	if (maxPercent >= 100 || maxPercent <= 0) this->maxAmount = 100; //Should be a percentage
}

CapMapping CapMap::createCapMapping(cv::Mat& img, std::vector<cv::Point> positions, std::vector<Cap> caps, int circlePixels) {
	switch (this->mapMode) {
	case CAP_MAP_HIST:
		return this->createCapMappingHist(img, positions, caps, circlePixels);
		break;
	case CAP_MAP_SIMPLE:
		return this->createCapMappingSimple(img, positions, caps, circlePixels);
		break;
	default:
		return CapMapping();
	}
}

CapMapping CapMap::createCapMappingSimple(cv::Mat& img, std::vector<cv::Point> & positions, std::vector<Cap>& caps, int circlePixels) {
	ColorDistanceMap data = getAllDistances(getColorValues(img, positions, circlePixels), caps);
	CapMapping mapping(caps.size(),std::vector<cv::Point>());
	for (int i = 0; i < data.size(); ++i) {
		int j = 0;
		while (mapping[std::get<0>(data[i][j])].size() > caps[std::get<0>(data[i][j])].max_amount) {
			if (++j >= caps.size()) throw std::runtime_error("Not enough caps!");
		}
		mapping[std::get<0>(data[i][j])].push_back(positions[i]);
	}
	return mapping;
}

CapMapping CapMap::createCapMappingHist(cv::Mat & img, std::vector<cv::Point> & positions, std::vector<Cap> & caps, int circlePixels) {
	ColorDistanceMap data = getAllDistances(getColorValues(img, positions, circlePixels), caps);
	CapMapping mapping(caps.size(), std::vector<cv::Point>());
	bool * positions_used = new bool[data.size() + 1];
	std::fill_n(positions_used, data.size() + 1, false);
	int positions_used_num = 0;
	int next_best_i = -1;
	int next_best_j = -1;
	double smallest_unused_distance = 9999.99;
	int maximum_amount = static_cast<int>((positions.size() / 100.0) * this->maxAmount);
	std::cout << this->maxAmount << "% = " << maximum_amount << std::endl;
	while (positions_used_num < positions.size()) {
		for (int i = 0; i < data.size(); ++i) // Positions
		{
			int j = 0;
			if (!positions_used[i])
			{
				//Iterate through the sorted Caps untill we find a cap that doesnt exceed its set max_amount or the max_amount heuristic
				//mapping[std::get<0>(data[i][j])].size() is the amount the cap has already been used.
				int cap_index = std::get<0>(data[i][j]);
				int j_caps_used = mapping[cap_index].empty() ? 0 : static_cast<int>(mapping[cap_index].size());
				while (j_caps_used > std::min(maximum_amount, caps[cap_index].max_amount)) {
					if (++j >= caps.size()) throw std::runtime_error("Not enough caps!");
					cap_index = std::get<0>(data[i][j]);
					j_caps_used = mapping[cap_index].empty() ? 0 : static_cast<int>(mapping[cap_index].size());
				}
				double dist = std::get<1>(data[i][j]);
				if (smallest_unused_distance > dist)
				{
					next_best_i = i;
					next_best_j = j;
					smallest_unused_distance = dist;
				}
			}
		}
		mapping[std::get<0>(data[next_best_i][next_best_j])].push_back(positions[next_best_i]);
		positions_used[next_best_i] = true;
		positions_used_num++;
		next_best_i = -1;
		next_best_j = -1;
		smallest_unused_distance = 9999.99;
	}
	delete[] positions_used;
	return mapping;
}

void CapMap::setMaxAmount(int max_amount)
{
	this->maxAmount = max_amount;
	std::cout << "Max amount set: " << this->maxAmount << "\n";
}

void CapMap::setColorPicker(ColorPicker * cp)
{
	this->colorPicker = cp;
}

void CapMap::setMapMode(int map_mode)
{
	this->mapMode = map_mode;
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
std::vector<cv::Vec3i> CapMap::getColorValues(cv::Mat& img, std::vector<cv::Point> positions, int circlePixels) {
	std::vector<cv::Vec3i> colors;
	cv::Vec3i col;
	for (cv::Point & p: positions) {
		try
		{
			colors.push_back(this->colorPicker->getColorV(img, p, circlePixels));
		}
		catch (const std::exception&)
		{
			colors.push_back(ColorPoint().getColorV(img, p , circlePixels));
		}
	}
	return colors;
}


