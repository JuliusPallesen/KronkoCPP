#include "pch.h"
#include <opencv2/opencv.hpp>
#include "ColorPoint.h"
#include "ColorAvg.h"
#include "ColorGauss.h"
#include "ColorCustom.h"

#define TEST_IMG_FOLDER "./Test/"
#define TEST_IMG_RED_PATH "C:/Users/juliu/source/repos/Kronko/KronkoTest/Test/test_red.png"
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

TEST(TestColorPicker, TestColorPointRed) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, IMREAD_UNCHANGED);
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	}
	else {
		ColorPicker* cp = new ColorPoint();
		cv::Size sz = img.size();
		cv::Point center = cv::Point(sz.width / 2, sz.height / 2);
		Vec3i col_red = Vec3i(img.at<Vec3b>(center));
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
		Vec3i col_red = Vec3i(img.at<Vec3b>(center));
		Vec3i return_value = cp->getColorV(img, center,1);
		EXPECT_EQ(col_red, return_value);
	}
}

TEST(TestColorPicker, TestColorGaussRed) {
	cv::Mat img = cv::imread(TEST_IMG_RED_PATH, IMREAD_UNCHANGED);
	std::cout << "HEREHRHERHEHREHRHEHEHEHEAAAAHHAHAHAHAHRGHHH woooweeewooooweeee" << std::endl;
	if (img.empty()) {
		std::cerr << "Couldn't load Image: " << TEST_IMG_RED_PATH << std::endl;
	}
	else {
		ColorPicker* cp = new ColorGauss();
		cv::Size sz = img.size();
		cv::Point center = cv::Point(sz.width / 2, sz.height / 2);
		Vec3i col_red = Vec3i(img.at<Vec3b>(center));
		Vec3i col_blk = Vec3i(0, 0, 0);
		Vec3i return_value = cp->getColorV(img, center, 5);
		EXPECT_EQ(col_red, return_value);
	}
}