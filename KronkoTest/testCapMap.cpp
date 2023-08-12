#include "pch.h"

class TestCapMap : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		// Initialize common resources here
		cv::Mat zeroImg = Mat::zeros(Size(100, 100), CV_8UC1);
		img = &zeroImg;
		lay = new SquareLayouter();
		cp = new ColorPoint();
		db = new JsonDB("./db.json");
		ci = new CapImport(db, cp);
	}

	static void TearDownTestCase() {
		// Clean up common resources here
	}
public:
	static cv::Mat* img; // Static variable to hold the shared resource
	static CapLayoutManager * lay;
	static ColorPicker* cp;
	static CapDB* db;
	static CapImport* ci;

};

cv::Mat* TestCapMap::img			= nullptr;
CapLayoutManager* TestCapMap::lay	= nullptr;
ColorPicker* TestCapMap::cp			= nullptr;
CapDB* TestCapMap::db				= nullptr;
CapImport* TestCapMap::ci			= nullptr;


TEST(TestCapMap, TestNoFatalFail) {
	std::vector<cv::Point> points = TestCapMap::lay->createLayout(TestCapMap::img->size(), 10);
	TestCapMap::ci->addFolder(TEST_IMG_FOLDER);
	std::vector<Cap> caps = TestCapMap::ci->getCaps();
	CapMap cm = CapMap(TestCapMap::cp,10);
	EXPECT_NO_FATAL_FAILURE(CapMapping map = cm.createCapMappingSimple(*TestCapMap::img, points, caps, 10));	
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}