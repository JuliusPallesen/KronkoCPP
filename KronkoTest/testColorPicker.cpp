#include "pch.h"
#include <opencv2/opencv.hpp>
#include "ColorPoint.h"
#include "ColorAvg.h"
#include "ColorGauss.h"
#include "ColorCustom.h"

#define TEST_IMG_FOLDER "./../Kronko/Bottlecaps/Test/"

TEST(TestConstructors, TestColorPicker) {
	ColorPoint colorpoint();
	ColorPoint colorpoint();
	ColorPoint colorpoint();
	ColorPoint colorpoint();
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}