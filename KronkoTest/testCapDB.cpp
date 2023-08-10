#include "pch.h"

TEST(TestCapDBNoFail, TestTest) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB * db;
	Cap cap = Cap::Cap(0, "", "", cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	EXPECT_NO_FATAL_FAILURE(db = new JsonDB("./"));
	EXPECT_NO_FATAL_FAILURE(db->storeCap(cap));
	EXPECT_NO_FATAL_FAILURE(db->storeCaps(std::vector<Cap>({cap,cap})));
}

TEST(TestCapDBStore, TestTest) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB* db = new JsonDB("./");
	Cap cap = Cap::Cap(0, "", "", cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	db->clearDB();
	db->storeCap(cap);
	EXPECT_EQ(db->getCaps().size(),1);
}