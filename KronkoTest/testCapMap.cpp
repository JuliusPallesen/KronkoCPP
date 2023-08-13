#include "pch.h"
#include <vector>

TEST(TestCapMap, TestNoFatalFail) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);
	CapLayoutManager * lay = new SquareLayouter();
	ColorPicker * cp = new ColorPoint();
	CapDB * db = new JsonDB("./db.json");
	CapImport * ci = new CapImport(db, cp);
	std::vector<cv::Point> points = lay->createLayout(img.size(), 100);
	ci->addFolder(TEST_IMG_FOLDER);
	std::vector<Cap> caps = ci->getCaps();
	CapMap cm = CapMap(cp,10);
	EXPECT_NO_FATAL_FAILURE(CapMapping map = cm.createCapMapping(img, points, caps, 10));	
	cm.setMapMode(CAP_MAP_HIST);
	EXPECT_NO_FATAL_FAILURE(CapMapping map = cm.createCapMapping(img, points, caps, 10));
	EXPECT_NO_THROW(CapMapping map = cm.createCapMapping(img, points, caps, 10));
	cm.setMapMode(CAP_MAP_SIMPLE);
	EXPECT_NO_THROW(CapMapping map = cm.createCapMapping(img, points, caps, 10));
}

TEST(TestCapMap, TestMappingHist) {
	cv::Mat img = Mat::zeros(Size(1000, 1000), CV_8UC1);
	CapLayoutManager* lay = new SquareLayouter;
	ColorPicker* cp = new ColorPoint();
	CapDB* db = new JsonDB("./db.json");
	CapImport ci = CapImport(db, cp);
	ci.addFolder(TEST_IMG_FOLDER);
	std::vector<Cap> caps = ci.getCaps();
	std::vector<Point> points = lay->createLayout(img.size(), 1000);
	int max_amount = 10;
	CapMap cm = CapMap(cp, max_amount, CAP_MAP_HIST);
	int positions_num = 0;
	CapMapping map = cm.createCapMapping(img,points, caps, 10);
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
