#include "pch.h"


TEST(TestColorPicker,TestConstructors) {
	ColorPicker* cp = new ColorPoint();
	ColorPicker* ca = new ColorAvg();
	ColorPicker* cg= new ColorGauss();
	ColorPicker* cc = new ColorCustom(cv::Vec3i(0,0,0));
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH,IMREAD_UNCHANGED);
	if (img.empty()) std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	EXPECT_NO_THROW(cp->getColorV(img, cv::Point(1, 1),1));
	EXPECT_NO_THROW(ca->getColorV(img, cv::Point(1, 1),1));
	EXPECT_NO_THROW(cg->getColorV(img, cv::Point(1, 1),1));
	EXPECT_NO_THROW(cc->getColorV(img, cv::Point(1, 1),1));
}

TEST(TestColorPicker, TestDefaults) {
	ColorPicker* cp = new ColorPoint();
	ColorPicker* ca = new ColorAvg();
	ColorPicker* cg = new ColorGauss();
	ColorPicker* cc = new ColorCustom(cv::Vec3i(0, 0, 0));
	for (auto& p : {TEST_IMG_RED_PATH,TEST_IMG_BUDWEISER,TEST_IMG_BLACK_PATH,TEST_IMG_CARLSBERG}) {
		cv::Mat img = cv::imread(p, IMREAD_UNCHANGED);
		std::cout << p << std::endl;
		if (img.empty()) {
			std::cerr << "Couldn't load Image: " << p << std::endl;
		}
		else {
			EXPECT_NO_THROW(cp->getColorV(img));
			EXPECT_NO_THROW(ca->getColorV(img));
			EXPECT_NO_THROW(cg->getColorV(img));
			EXPECT_NO_THROW(cc->getColorV(img));
		}
	}
}

TEST(TestColorPicker, TestGaussBudweiser) {
	ColorPicker* cg = new ColorGauss();
	cv::Mat img = cv::imread(TEST_IMG_BUDWEISER, IMREAD_UNCHANGED);
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_BUDWEISER << std::endl;
	}
	else {
		EXPECT_NO_THROW(cg->getColorV(img));
	}
}


TEST(TestColorPicker, TestColorPointRed) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, IMREAD_UNCHANGED);
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	}
	else {
		ColorPicker* cp = new ColorPoint();
		cv::Size sz = img.size();
		cv::Point center = cv::Point(sz.width / 2, sz.height / 2);
		Vec4b color = img.at<Vec4b>(center);
		Vec3i col_red = Vec3i(color[0], color[1], color[2]);
		Vec3i return_value = cp->getColorV(img, center,1);
		EXPECT_EQ(col_red, return_value);
	}
}

TEST(TestColorPicker,TestColorAvgRed) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, IMREAD_UNCHANGED);
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	}
	else {
		ColorPicker* cp = new ColorAvg();
		cv::Size sz = img.size();
		cv::Point center = cv::Point(sz.width / 2, sz.height / 2);
		Vec4b color = img.at<Vec4b>(center);
		Vec3i col_red = Vec3i(color[0], color[1], color[2]);
		Vec3i return_value = cp->getColorV(img, center,1);
		EXPECT_EQ(col_red, return_value);
	}
}

TEST(TestColorPicker, TestColorGaussRed) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, IMREAD_UNCHANGED);
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	}
	else {
		ColorPicker* cp = new ColorGauss();
		cv::Size sz = img.size();
		cv::Point center = cv::Point(sz.width / 2, sz.height / 2);
		Vec4b color = img.at<Vec4b>(center);
		Vec3i col_red = Vec3i(color[0], color[1], color[2]);
		Vec3i col_blk = Vec3i(0, 0, 0);
		Vec3i return_value = cp->getColorV(img, center, 5);
		EXPECT_EQ(col_red, return_value);
	}
}

TEST(TestColorPicker, TestColorCorrect) {
	ColorPicker* cp = new ColorPoint();
	ColorPicker* ca = new ColorAvg();
	ColorPicker* cg = new ColorGauss();
	ColorPicker* cc = new ColorCustom(cv::Vec3i(0, 0, 0));
	ColorPicker* cps[3] = { cp,ca,cg };
	for (auto& p : { TEST_IMG_RED_PATH,TEST_IMG_BLACK_PATH,TEST_IMG_BLUE_PATH,TEST_IMG_GREEN_PATH,TEST_IMG_YELLOW_PATH,TEST_IMG_MAGENTA_PATH }) {
		cv::Mat img = cv::imread(p, IMREAD_UNCHANGED);
		if (img.empty()) std::cerr << "Couldn't load Image: " << p << std::endl;
		cv::Vec4b color = img.at<Vec4b>(img.cols / 2, img.rows /2);
		std::cout << p << " --> " << color << std::endl;
		for (auto&c:cps)
		{
			std::cout << typeid(*c).name() << std::endl;
			cv::Vec3i res_color = c->getColorV(img);
			//EXPECT_EQ(color,res_color);
			EXPECT_NEAR(color[0], res_color[0],1);
			EXPECT_NEAR(color[1], res_color[1], 1);
			EXPECT_NEAR(color[2], res_color[2], 1);
		}
	}
}