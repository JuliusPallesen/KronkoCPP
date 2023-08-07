#include <opencv2/opencv.hpp>

void overlayImage(cv::Mat& img1, cv::Mat& img2, cv::Point position, int size) {
	cv::resize(img2, img2, cv::Size(size, size)); // Resize image2 to the desired size

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
	cv::addWeighted(img1_roi, 1.0, img2, 1.0, 0.0, img1_roi);
}
