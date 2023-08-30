#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
#include <filesystem>
#include "CapImport.h"
#include "Cap.h"
#include "PackingLayouter.h"
#include "SquareLayouter.h"
#include "TriangleLayouter.h"
#include "ColorPicker.h"
#include "ColorPoint.h"
#include "ColorAvg.h"
#include "ColorCustom.h"
#include "ColorGauss.h"
#include "CapMap.h"
#include "CapAssembley.h"
#include "Types.h"
#include "KronkoHelpers.h"

class KronkoConfig
{
public:
	KronkoConfig();
	~KronkoConfig();

	int widthMm;
	int widthRes, heightRes;
	cv::Mat img;
	std::vector<std::string> capImportPaths;
	std::string outputFilename;
	CapLayoutManager * layouter = new SquareLayouter();
	ColorPicker * colorPicker = new ColorGauss();
	CapDB * database = new JsonDB("./JSON/db.json");
	CapImport capImport = CapImport();
	CapMap capMapper;

	void setColorPicker(ColorPicker * cp);
	std::vector<cv::Point> getLayout(CapLayoutManager* lay, bool preview = true);
	void execConfig();
};


