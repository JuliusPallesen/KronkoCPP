#include "pch.h"

bool allInBounds(std::vector<cv::Point> points, cv::Size sz, int radius) {
	for (auto & p: points)
	{
		if (p.x + radius >= sz.width	||
			p.x - radius < 0			||
			p.y + radius >= sz.height	||
			p.y - radius < 0 )
		{
			std::cout << "Out of bounds at: " << p << " with r: " << radius << " and img.size: " << sz << std::endl;
			return false;
		}
	}
	return true;
};

TEST(TestLayout, TestNoFatalFail) {
	cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC1);;
	SquareLayouter lay;
	EXPECT_NO_FATAL_FAILURE(lay = SquareLayouter());
	EXPECT_NO_FATAL_FAILURE(lay.createLayout(img.size(),100));
}

TEST(TestLayout, TestNoThrow) {
	cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC1);;
	SquareLayouter lay;
	EXPECT_NO_THROW(lay = SquareLayouter());
	EXPECT_NO_THROW(lay.createLayout(img.size(), 100));
}

TEST(TestLayout, TestReturn) {
	cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC1);;
	SquareLayouter lay;
	std::vector<cv::Point> points;
	points = lay.createLayout(img.size(), 100);
	EXPECT_GT(points.size(),0);
}

TEST(TestLayout, TestReturnExactlyOne) {
	cv::Mat img = cv::Mat::zeros(cv::Size(CAP_SIZE+1, CAP_SIZE + 1), CV_8UC1);;
	SquareLayouter lay;
	std::vector<cv::Point> points;
	points = lay.createLayout(img.size(), CAP_SIZE);
	EXPECT_EQ(points.size(), 1);
}

TEST(TestLayout, TestTooSmall) {
	cv::Mat img = cv::Mat::zeros(cv::Size(100, 100), CV_8UC1);;
	SquareLayouter lay;
	std::vector<cv::Point> points = lay.createLayout(img.size(),CAP_SIZE - 1);
	EXPECT_EQ(points.size(), 0);
}

TEST(TestLayout, TestOOB) {
	cv::Mat img = cv::Mat::zeros(cv::Size(1, 1), CV_8UC1);;
	SquareLayouter lay;
	std::vector<cv::Point> points;
	EXPECT_THROW(points = lay.createLayout(img.size(), 1000), std::runtime_error);
}

TEST(TestLayout, TestAllInBounds) {
	cv::Mat img = cv::Mat::zeros(cv::Size(1, 1), CV_8UC1);
	CapLayoutManager * layouter[2] = { new SquareLayouter() ,  new TriangleLayouter()};
	std::vector<cv::Point> points;
	for (auto& size : { 10,100,260,1337 }) {
		img = cv::Mat::zeros(cv::Size(size, size), CV_8UC1);
		for (auto & lay: layouter)
		{
			std::cout << typeid(*lay).name() << " size: "<< size << std::endl;
			EXPECT_TRUE(allInBounds(lay->createLayout(img.size(),26),img.size(),13));
		}
	}


}