#pragma once

#include <opencv2/opencv.hpp>

void changeContrastRGBA(cv::Mat& image, double alpha);

void changeVibrancyRGBA(cv::Mat& image, double beta);

cv::Mat performColorQuantizationRGBA(cv::Mat& image, int numColors);