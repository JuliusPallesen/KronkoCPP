#include "pch.h"
#include <vector>

TEST(TestCapMap, Constructor) {
	EXPECT_NO_FATAL_FAILURE(CapMap cm);
	EXPECT_NO_FATAL_FAILURE(CapMap cm(new ColorPoint, 50));
}
TEST(TestCapMap, TestNoFatalFail) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, cv::IMREAD_UNCHANGED);
	if (img.empty()) std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	SquareLayouter * lay = new SquareLayouter;
	ColorPoint * cp = new ColorPoint();;
	CapImport ci(new JsonDB("./db.json"), cp);
	std::vector<cv::Point> points = lay->createLayout(img.size(), 100);
	ci.addFolder(TEST_IMG_FOLDER);
	std::vector<Cap> caps = ci.getCaps();
	CapMap cm = CapMap(cp,100);

	cm.setMapMode(CAP_MAP_SIMPLE);
	EXPECT_NO_FATAL_FAILURE(cm.createCapMapping(img, points, caps, 10));	
	EXPECT_NO_THROW(cm.createCapMapping(img, points, caps, 10));

	cm.setMapMode(CAP_MAP_HIST);
	EXPECT_NO_FATAL_FAILURE(cm.createCapMapping(img, points, caps, 10));
	EXPECT_NO_THROW(cm.createCapMapping(img, points, caps, 10));
}

TEST(TestCapMap, TestMappingHist) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, cv::IMREAD_UNCHANGED);
	if (img.empty()) std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	SquareLayouter lay;
	ColorPoint * cp = new ColorPoint();
	JsonDB db("./db.json");
	db.clearDB();
	CapImport ci(&db, cp);
	ci.addFolder(TEST_IMG_FOLDER);
	std::vector<Cap> caps = ci.getCaps();
	std::vector<cv::Point> points = lay.createLayout(img.size(), 100);
	int max_amount = 10;
	CapMap cm = CapMap(cp, 25, CAP_MAP_HIST);
	int positions_num = 0;
	CapMapping map = cm.createCapMapping(img,points, caps, 1);
	for (int i = 0; i < map.size(); i++)
	{
		if (!map[i].empty()) {
			EXPECT_LE(map[i].size(), max_amount);
			EXPECT_LE(map[i].size(), caps[i].max_amount);
			positions_num += static_cast<int>(map[i].size());
		}
	}
	EXPECT_EQ(points.size(), positions_num);
}
