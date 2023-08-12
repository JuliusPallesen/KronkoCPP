#include "pch.h"

TEST(TestLayout, TestNoFatalFail) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);;
	CapLayoutManager * lay;
	EXPECT_NO_FATAL_FAILURE(lay = new SquareLayouter());
	EXPECT_NO_FATAL_FAILURE(lay->createLayout(img.size(),100));
	EXPECT_NO_FATAL_FAILURE(lay->createLayoutmm(img, 100));
}

TEST(TestLayout, TestNoThrow) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);;
	CapLayoutManager* lay;
	EXPECT_NO_THROW(lay = new SquareLayouter());
	EXPECT_NO_THROW(lay->createLayout(img.size(), 100));
	EXPECT_NO_THROW(lay->createLayoutmm(img, 100));
}

TEST(TestLayout, TestReturn) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);;
	CapLayoutManager* lay = new SquareLayouter();
	std::vector<cv::Point> points;
	points = lay->createLayout(img.size(), 100);
	EXPECT_GT(points.size(),0);
}

TEST(TestLayout, TestReturnExactlyOne) {
	cv::Mat img = Mat::zeros(Size(CAP_SIZE+1, CAP_SIZE + 1), CV_8UC1);;
	CapLayoutManager* lay = new SquareLayouter();
	std::vector<cv::Point> points;
	points = lay->createLayout(img.size(), CAP_SIZE);
	EXPECT_EQ(points.size(), 1);
}

TEST(TestLayout, TestTooSmall) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);;
	CapLayoutManager* lay = new SquareLayouter();
	std::vector<cv::Point> points = lay->createLayout(img.size(),CAP_SIZE - 1);
	EXPECT_EQ(points.size(), 0);
}

TEST(TestLayout, TestOOB) {
	cv::Mat img = Mat::zeros(Size(1, 1), CV_8UC1);;
	CapLayoutManager* lay = new SquareLayouter();
	std::vector<cv::Point> points;
	EXPECT_THROW(points = lay->createLayout(img.size(), 1000), std::runtime_error);
}
