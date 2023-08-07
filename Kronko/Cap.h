#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

#define CAP_BRAND	"Brand"
#define CAP_PATH	"Path"
#define CAP_PRIO	"Priority"
#define CAP_COLOR	"Color"
#define CAP_DIR		"Direction"

using json = nlohmann::json;

class Cap
{
public:
	std::string brand;
	std::string path;
	cv::Vec3i color;
	cv::Vec2b dir;
	cv::Mat img;
	int prio;

	Cap(json data);
	Cap(std::string brand, std::string path, cv::Vec3i color, cv::Vec2b dir, cv::Mat img, int prio = 1);
	json serializeJSON();
	std::string toString();
};

