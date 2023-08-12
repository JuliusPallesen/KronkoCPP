#include "Kronko.h"

using namespace cv;

void print_help() {
	std::cout << "\nHelp:\n";
	std::cout << "1-3:\t\t Chose Layouter (Square, Triangle, Packing)\n";
	std::cout << "g:\t\t Gaussian Colopicker";
	std::cout << "m:\t\t Mean Colopicker";
	std::cout << "p:\t\t Point Colopicker";
	std::cout << "i:\t\t Import Caps from DB\n";
	std::cout << "c:\t\t clear DB\n";
	std::cout << "s:\t\t Save image\n";
	std::cout << "b:\t\t Load backup image / reset image\n";
	std::cout << "Esc/x:\t\t Quit.\n";
}

void resizeImage(cv::Mat& image, int& windowWidth, int& windowHeight) {
	double imageAspectRatio = static_cast<double>(image.cols) / image.rows;
	int desiredWidth = windowWidth;
	int desiredHeight = static_cast<int>(desiredWidth / imageAspectRatio);

	if (desiredHeight > windowHeight) {
		desiredHeight = windowHeight;
		desiredWidth = static_cast<int>(desiredHeight * imageAspectRatio);
	}

	windowWidth = desiredWidth;
	windowHeight = desiredHeight;
}

Mat readJpgAsBGRA(std::string path) {
	cv::Mat jpegImage = cv::imread(path);
	cv::Mat bgraImage;
	if (!jpegImage.empty()) {
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
	return bgraImage;
}

int getCircleSizePx(cv::Mat img, int width_mm) {
	return (int)(((float)img.cols / (float)width_mm) * CAP_SIZE);
}

int main(int argc, char* argv[])
{
	const std::string DB_PATH = "./JSON/db.json";
	const std::string LENA_PATH = "./Images/lena.jpg";
	const std::string CAP_IMG_FOLDER = "./Bottlecaps/";

	bool cancel = false;
	int wdth_mm = CAP_SIZE;
	int circ_px = 100;
	std::string path = LENA_PATH;

	CapLayoutManager* lom = new SquareLayouter;
	std::vector<cv::Point> cap_positions;

	ColorPicker * cp = new ColorAvg();

	JsonDB db(DB_PATH);
	CapImport cap_importer(&db,cp);

	Mat img = readJpgAsBGRA(path);
	Mat backup = img.clone();

	std::vector<Cap> caps;
	CapMapping map;
	CapMap cm = CapMap();

	if (img.empty())
	{
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	namedWindow("Kronko", WINDOW_NORMAL);
	createTrackbar("Width", "Kronko", &wdth_mm, 1000);
	setTrackbarMin("Width", "Kronko", CAP_SIZE);
	Rect windowRect = getWindowImageRect("Kronko");
	Rect windowRectPrev = windowRect;

	while (!cancel) {
		try {
			windowRect = getWindowImageRect("Kronko");
		}
		catch (...) {
			return 0; // window closed
		}
		if (windowRect != windowRectPrev) {
			windowRectPrev = windowRect;
			int windowWidth = windowRect.width;
			int windowHeight = windowRect.height;
			resizeImage(img, windowWidth, windowHeight);
			resizeWindow("Kronko", windowWidth, windowHeight);
		}
		else {
			imshow("Kronko", img);
			int k = waitKey(0); // Wait for a keystroke in the window
			switch (k) {
			case 's': // SAVE
				std::cout << "Saving image to " << path << std::endl;
				imwrite(path, img);
				break;
			case 'b': // LOAD BACKUP
				std::cout << "Loading backup" << std::endl;
				img = backup.clone();
				break;
			case '1': // SQUARE LAYOUTER
				std::cout << "Calculating Square Layout..." << std::endl;
				lom = new SquareLayouter();
				cap_positions = lom->createLayout(img.size(), wdth_mm);
				circ_px = getCircleSizePx(img, wdth_mm);
				for (auto& p : cap_positions) {
					circle(img, p, circ_px / 2, { 255,255,255 }, (img.cols / 1000) +1);
				}
				break;
			case '2':
				std::cout << "Calculating Triangle Layout..." << std::endl;
				lom = new TriangleLayouter();
				cap_positions = lom->createLayout(img.size(), wdth_mm);
				circ_px = getCircleSizePx(img, wdth_mm);
				for (auto& p : cap_positions) {
					circle(img, p, circ_px / 2, { 255,255,255 }, (img.cols / 1000) +1);
				}
				break;
			case 'a': // ASSEMBLE
				std::cout << "Assembeling Bottlecaps...\n";
				if (!cap_positions.empty()) {
					caps = cap_importer.getCaps();
					if (caps.empty()) {
						std::cerr << "No Caps Loaded." << std::endl;
						break;
					}
					circ_px = getCircleSizePx(img, wdth_mm);
					map = cm.createCapMappingHist(img, cap_positions, caps, circ_px);
					assembleMapping(img, map, caps, circ_px);
				}
				break;
			case 'i': // IMPORT
				std::cout <<"Importing Folder \n";
				cap_importer.addFolder(CAP_IMG_FOLDER);
				break;
			case 'c': // CLEAR DB
				std::cout << "clearing DB...\n";
				db.clearDB();
				break;
			case 'g': // GAUSS PICKER
				std::cout << "Gaussian Colorselection\n";
				cm.setColorPicker(new ColorGauss());
				break;
			case 'm': // MEAN
				std::cout << "Mean Colorselection\n";
				cm.setColorPicker(new ColorAvg());
				break;
			case 'p':
				std::cout << "Point Colorselection\n";
				cm.setColorPicker(new ColorPoint());
				break;
			case 'x': // QUIT
			case 27:
				cancel = true;
				break;
			default: // HELP
				print_help();
				break;
			}
		}

		
	}
	return 0;
}
