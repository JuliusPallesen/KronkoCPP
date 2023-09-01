#include "KronkoHelpers.h"

void conditionalResize(cv::Mat& img, int wdth_res) {
	if ((wdth_res != img.cols) && (wdth_res != 0)) {
		int height = static_cast<int>((static_cast<double>(wdth_res) / static_cast<double>(img.cols)) * static_cast<double>(img.rows));
		cv::resize(img, img, cv::Size(wdth_res, height));
	}
}

int getCircleSizePx(cv::Mat img, int width_mm) {
	return (int)(((float)img.cols / (float)width_mm) * CAP_SIZE);
}

cv::Mat readimGBRA(std::string path) {
	cv::Mat jpegImage = cv::imread(path, cv::IMREAD_UNCHANGED);
	cv::Mat bgraImage;
	if (!jpegImage.empty()) {
		if (jpegImage.channels() == 4) return jpegImage;
		cv::Mat alphaChannel(jpegImage.size(), CV_8UC1, cv::Scalar(255));
		std::vector<cv::Mat> rgbChannels(3);
		cv::split(jpegImage, rgbChannels);
		std::vector<cv::Mat> bgraChannels(4);
		bgraChannels[0] = rgbChannels[0]; // Blue channel
		bgraChannels[1] = rgbChannels[1]; // Green channel
		bgraChannels[2] = rgbChannels[2]; // Red channel
		bgraChannels[3] = alphaChannel;   // Alpha channel
		cv::merge(bgraChannels, bgraImage);
	}
	else {
		throw std::runtime_error("Couldn't load image (.png,.jpg): " + path);
	}
	return bgraImage;
}