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

using json = nlohmann::json;
namespace fs = std::filesystem;

class CapImport
{
public:
	CapImport(CapDB * db, ColorPicker * cp);
	CapImport();
	void addCap(Cap & cap);
	void addCap(fs::path path);
	void addFolder(std::string path);
	void setColorPicker(ColorPicker * cp);
	void setDB(CapDB * db);
	void clearDB();
	std::vector<Cap> getCaps();
protected:
	CapDB * dataBase;
	ColorPicker * colorPicker;
	std::vector<Cap> caps;
	int ids;

	cv::Vec3b getColVec(cv::Mat & img, cv::Vec3b * c = nullptr);
	cv::Vec2b getDirVector(cv::Mat & img);
	Cap makeCap(fs::path path, int prio = 0, int max_amount = INT_MAX);
};

