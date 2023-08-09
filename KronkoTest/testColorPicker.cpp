#include "pch.h"
#include <opencv2/opencv.hpp>
#include "ColorPoint.h"
#include "ColorAvg.h"
#include "ColorGauss.h"
#include "ColorCustom.h"
//#include "ColorPicker.h"

#define TEST_IMG_FOLDER "./../Kronko/Bottlecaps/Test/"
#define TEST_IMG_RED_PATH "./../Kronko/Bottlecaps/Test/test_red.png"

TEST(TestConstructors, TestColorPicker) {
	ColorPicker* cp = new ColorPoint();
	ColorPicker* ca = new ColorAvg();
	ColorPicker* cg= new ColorGauss();
	ColorPicker* cc = new ColorCustom(cv::Vec3i(0,0,0));
	cv::Mat img = imread(TEST_IMG_RED_PATH,IMREAD_UNCHANGED);
	EXPECT_NO_THROW(cp->getColorV(img, cv::Point(1, 1)),10);
	EXPECT_NO_THROW(ca->getColorV(img, cv::Point(1, 1)),10);
	EXPECT_NO_THROW(cg->getColorV(img, cv::Point(1, 1)),10);
	EXPECT_NO_THROW(cc->getColorV(img, cv::Point(1, 1)),10);
}