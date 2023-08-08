#include "CapAssembley.h"
// TODO:
//		- Fix alpha channel not being considered for PNG
//		- Add option for Directional insertion (?)
//		- Calculate Directional leaning of points (May not always make sense but could lead to cool results)
void overlayImage(cv::Mat& img1, cv::Mat & capimg, cv::Point position, int size) {
	std::cout << "Overlaying img at pos" << position << std::endl;
	cv::Mat img2;
	cv::resize(capimg, img2, cv::Size(size, size)); // Resize image2 to the desired size

	// Calculate the ROI using the specified position
	cv::Rect roi(position.x - size / 2, position.y - size / 2, img2.cols, img2.rows);

	// Ensure the ROI is within bounds
	if (roi.x < 0 || roi.y < 0 || roi.x + roi.width > img1.cols || roi.y + roi.height > img1.rows) {
		// Handle out-of-bounds error
		return;
	}

	// Create a region of interest (ROI) in img1 where img2 will be placed
	cv::Mat img1_roi = img1(roi);

	// Add the transformed image2 to the ROI of img1
	cv::addWeighted(img1_roi, 0, img2, 1.0, 0.0, img1_roi);
}

void assembleMapping(cv::Mat & img, CapMapping map, std::vector<Cap> caps,int circ_px) {
	for (int i = 0; i < map.size(); i++)
	{
		if (!map[i].empty())
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				overlayImage(img, caps[i].img, map[i][j], circ_px);
			}
		}
	}
}
