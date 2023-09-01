#include "CapAssembley.h"
// TODO:
//		- Add option for Directional insertion (?)
//		- Calculate Directional leaning of points (May not always make sense but could lead to cool results)

void overlayImage(cv::Mat& img, cv::Mat& capimg, cv::Point position) {
	using namespace cv;
	Size capsize = capimg.size();
	Size imgsize = img.size();
	Vec4b color;
	if (position.x - (capsize.width / 2) >= 0			 &&
		position.x + (capsize.width / 2) < imgsize.width &&
		position.y - (capsize.height / 2) >= 0			 &&
		position.y + (capsize.height / 2) < imgsize.height
		) {
		for (int x = 0; x < capsize.width; x++)
		{
			int x_pos = x + position.x - (capsize.width / 2);
			for (int y = 0; y < capsize.height; y++)
			{
				int y_pos = y + position.y - (capsize.height / 2);
				try {
					Vec4b cap_pixel = capimg.at<Vec4b>(y, x);
					if (cap_pixel[3] > 0) img.at<Vec4b>(y_pos, x_pos) = cap_pixel;
				}
				catch (...) {
					std::cerr << "Failed to access pixel: " << x_pos << "," << y_pos << " in img size: " << imgsize << " Cap size: "  << capsize << std::endl;
				}
			}
		}
	}
	else {
		throw std::runtime_error("\n Tried to add image out of bounds");
	}
}

void combine(cv::Mat & img, cv::Mat & overlay) {
	assert(img.cols == overlay.cols);
	assert(img.rows == overlay.rows);
	for (int x = 0; x < overlay.cols; x++)
	{
		for (int y = 0; y < overlay.rows; y++)
		{
			cv::Vec4b cap_pixel = overlay.at<cv::Vec4b>(y, x);
			if (cap_pixel[3] > 0) img.at<cv::Vec4b>(y, x) = cap_pixel;
		}
	}
}

void assembleMapping(cv::Mat & img, CapMapping map, std::vector<Cap> caps,int circ_px) {
	assert(map.size() == caps.size());
	std::vector<std::thread> threads;
	std::mutex imgMutex;
	for (int i = 0; i < map.size(); i++)
	{
		const std::vector<cv::Point> insertPositions = map[i];
		if (!insertPositions.empty())
		{
			threads.emplace_back([&img, &caps, insertPositions, &imgMutex, i, &circ_px]() {
				try {
					cv::Mat capImg = caps[i].img;
					if (!img.empty()) {
						cv::resize(capImg, capImg, cv::Size(circ_px, circ_px));
						cv::Mat overlay = cv::Mat::zeros(img.size(), img.type());
						for (int j = 0; j < insertPositions.size(); j++)
						{
							overlayImage(overlay, capImg, insertPositions[j]);
						}
						std::lock_guard<std::mutex> lock(imgMutex);
						combine(img, overlay);
					}
				}
				catch (std::exception & e) {
					std::cerr << e.what() << std::endl;
				}
				});
		}
	}
	for (auto& thread : threads) {
		thread.join();
	}
}
/*

void assembleMapping(cv::Mat & img, CapMapping map, std::vector<Cap> caps,int circ_px) {
	for (int i = 0; i < map.size(); i++)
	{
		if (!map[i].empty())
		{
            cv::Mat capimg = caps[i].img;
            cv::resize(capimg, capimg, cv::Size(circ_px, circ_px)); // Resize cap to desired size
			for (int j = 0; j < map[i].size(); j++)
			{
				try {
					overlayImage(img, capimg, map[i][j]);
				}
				catch (std::runtime_error& e) {
					std::cerr << "Failed to overlay image\n" << e.what();
				}
			}
		}
	}
}*/