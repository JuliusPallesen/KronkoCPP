#pragma once
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <filesystem>
#include <fstream>
#include "Cap.h"
#include "CapDB.h"
#include "JsonDB.h"
#include "ColorPicker.h"
#include "ColorPoint.h"
#include "Types.h"

using namespace cv;
using json = nlohmann::json;
namespace fs = std::filesystem;

class CapImport
{
public:
	CapImport(CapDB * db, ColorPicker *  cp = new ColorPicker());
	void addCap(Cap& cap);
	void addCap(fs::path path);
	void addFolder(const std::string path);
	std::vector<Cap> getCaps();
protected:
	CapDB * db;
	std::vector<Cap> caps;
	ColorPicker * color_picker;
	int ids;

	cv::Vec3b getColVec(cv::Mat & img, cv::Vec3b * c = nullptr);
	cv::Vec2b getDirVector(cv::Mat & img);
	Cap makeCap(fs::path path, int prio = 0);
};

