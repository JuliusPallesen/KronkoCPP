#include "pch.h"
#include "CppUnitTest.h"
#include "../Kronko/ColorCustom.h"
#include "../Kronko/ColorAvg.h"
#include "../Kronko/ColorGauss.h"
#include "../Kronko/ColorPicker.h"
#include "../Kronko/ColorPoint.h"
#include <opencv2/opencv.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KronkoTest
{
	TEST_CLASS(KronkoTest)
	{
	public:
		
		TEST_METHOD(TestCustomColor)
		{
			cv::Vec3i colorVec(1, 2, 3);
			ColorCustom cc = ColorCustom::ColorCustom(colorVec);
			cv::Mat * img = new cv::Mat();
			cv::Vec3i resVec = cc.getColorV(*img);
			Assert::AreEqual(resVec[0],colorVec[0]);
			Assert::AreEqual(resVec[1], colorVec[1]);
			Assert::AreEqual(resVec[2], colorVec[2]);
			delete[] img;
		}
	};
}
