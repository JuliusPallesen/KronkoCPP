#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include "Types.h"
using json = nlohmann::json;

class Cap
{
public:
	int id;
	std::string brand;
	std::string path;
	cv::Vec3i color;
	cv::Vec2b dir;
	cv::Mat img;
	int prio;
	int max_amount;

	Cap(json data);
	Cap(int id, std::string brand, std::string path, cv::Vec3i color, cv::Vec2b dir, cv::Mat img, int prio = 1, int max_amount = -1);
	json serializeJSON();
	std::string toString();
};

