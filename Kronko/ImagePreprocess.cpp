// TODO: Preprocess image
//	- Color quantization
//	- Antialiasing ?
//	- Maybe not necessery...

#include <opencv2/opencv.hpp>

#include <opencv2/opencv.hpp>

void changeContrastRGBA(cv::Mat& image, double alpha) {
    cv::Mat channels[4];
    cv::split(image, channels);
    for (int i = 0; i < 3; ++i) {
        channels[i] *= alpha; 
    }
    cv::merge(channels, 4, image); 
}


void changeVibrancyRGBA(cv::Mat& image, double beta) {
    cv::cvtColor(image, image, cv::COLOR_RGBA2BGR);
    cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
    cv::Mat channels[3];
    cv::split(image, channels); // Split HSV image into channels
    channels[1] *= beta; // Apply saturation adjustment to the S channel
    cv::merge(channels, 3, image); // Merge the channels back into an HSV image
    cv::cvtColor(image, image, cv::COLOR_HSV2BGR);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);
}

cv::Mat performColorQuantizationRGBA(cv::Mat & image, int numColors) {
    cv::Mat samples = image.reshape(1, image.rows * image.cols);
    samples.convertTo(samples, CV_32F);

    cv::Mat labels, centers;
    cv::kmeans(samples, numColors, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);

    cv::Mat newImage(image.size(), image.type());
    for (int i = 0; i < image.rows * image.cols; ++i) {
        int clusterIdx = labels.at<int>(i);
        cv::Vec4b& pixel = newImage.at<cv::Vec4b>(i / image.cols, i % image.cols);
        cv::Vec3f color = centers.at<cv::Vec3f>(clusterIdx);
        pixel[0] = cv::saturate_cast<uchar>(color[0]);
        pixel[1] = cv::saturate_cast<uchar>(color[1]);
        pixel[2] = cv::saturate_cast<uchar>(color[2]);
        pixel[3] = 255; // Set alpha to 255 (fully opaque)
    }
    return newImage;
}