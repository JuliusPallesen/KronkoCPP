#include "pch.h"

TEST(TestLayout, TestNoFatalFail) {
	cv::Mat img = Mat::zeros(Size(100, 100), CV_8UC1);;
	CapLayoutManager * lay = new SquareLayouter();
	
}