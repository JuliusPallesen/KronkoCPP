#include "pch.h"
TEST(TestDB,TestCapDBNoFatelFail) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB * db;
	Cap cap = Cap::Cap(0, "Black", TEST_IMG_BLACK_PATH, cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	EXPECT_NO_FATAL_FAILURE(db = new JsonDB("./db.json"));
	EXPECT_NO_FATAL_FAILURE(db->storeCap(cap));
	EXPECT_NO_FATAL_FAILURE(db->storeCaps(std::vector<Cap>({cap,cap})));
	EXPECT_NO_FATAL_FAILURE(std::vector<Cap> cps = db->getCaps());
}

TEST(TestDB,TestCapDBNoExep) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB* db;
	Cap cap = Cap::Cap(0, "Black", TEST_IMG_BLACK_PATH, cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	EXPECT_NO_THROW(db = new JsonDB("./db.json"));
	EXPECT_NO_THROW(db->storeCap(cap));
	EXPECT_NO_THROW(db->storeCaps(std::vector<Cap>({ cap,cap })));
	EXPECT_NO_THROW(std::vector<Cap> cps = db->getCaps());
}

TEST(TestDB,TestCapDBStoreSuccess) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB* db = new JsonDB("./db.json");
	Cap cap = Cap::Cap(0, "Black", TEST_IMG_BLACK_PATH, cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	db->clearDB();
	db->storeCap(cap);
	EXPECT_EQ(db->getCaps().size(),1);
}

TEST(TestDB,TestCapDBStoreElem) {
	cv::Mat img;
	ColorPoint::ColorPicker colorpoint;
	CapDB* db = new JsonDB("./db.json");
	Cap cap = Cap::Cap(0, "Black", TEST_IMG_BLACK_PATH, cv::Vec3i(0, 0, 0), Vec2b(0, 0), img, 0, 0);
	db->clearDB();
	db->storeCap(cap);
	EXPECT_EQ(db->getCaps()[0].path, TEST_IMG_BLACK_PATH);
}
