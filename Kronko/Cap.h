#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

#define CAP_BRAND	"Brand"
#define CAP_PATH	"Path"
#define CAP_PRIO	"Priority"
#define CAP_COLOR	"Color"
#define CAP_DIR		"Direction"
#define CAP_ID		"ID"
#define CAP_MAX		"Amount"

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
	Cap(int id, std::string brand, std::string path, cv::Vec3i color, cv::Vec2b dir, cv::Mat img, int prio = 1, int max_amount = INT_MAX);
	json serializeJSON();
	std::string toString();
};

