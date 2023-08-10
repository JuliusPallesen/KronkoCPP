#include "Kronko.h"

using namespace cv;

void print_help() {
	std::cout << std::endl << "Help:" << std::endl;
	std::cout << "1-3:\t\t Chose Layouter (Square, Triangle, Packing)" << std::endl;
	std::cout << "i:\t\t Import Caps from DB" << std::endl;
	std::cout << "c:\t\t clear DB" << std::endl;
	std::cout << "s:\t\t Save image" << std::endl;
	std::cout << "b:\t\t Load backup image / reset image" << std::endl;
	std::cout << "Esc/x:\t\t Quit." << std::endl;
}

void resizeImage(cv::Mat& image, int& windowWidth, int& windowHeight) {
	//TODO: Fix / responding to feedback
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
		// Create an alpha channel filled with fully opaque values
		cv::Mat alphaChannel(jpegImage.size(), CV_8UC1, cv::Scalar(255));

		// Split the JPEG image into its RGB channels
		std::vector<cv::Mat> rgbChannels(3);
		cv::split(jpegImage, rgbChannels);

		// Merge the RGB channels with the alpha channel to create BGRA image
		std::vector<cv::Mat> bgraChannels(4);
		bgraChannels[0] = rgbChannels[0]; // Blue channel
		bgraChannels[1] = rgbChannels[1]; // Green channel
		bgraChannels[2] = rgbChannels[2]; // Red channel
		bgraChannels[3] = alphaChannel;   // Alpha channel

		cv::merge(bgraChannels, bgraImage);
	}
	return bgraImage;
}

int main(int argc, char* argv[])
{
	// TODO: 
	//			- Parse commandline args
	//			- Move GUI stuff to KronkoGUI  
	const std::string DB_PATH = "./JSON/db.json";
	const std::string LENA_PATH = "./Images/lena.jpg";
	const std::string CAP_IMG_FOLDER = "./Bottlecaps/";

	bool cancel = false;
	int wdth_mm = CAP_SIZE;
	int circ_px = 100;
	std::string path = LENA_PATH;

	CapLayoutManager* lom = new SquareLayouter;
	std::vector<cv::Point> cap_positions;

	ColorPicker * cp = new ColorPoint();

	JsonDB db(DB_PATH);
	CapImport cap_importer(&db,cp);

	// TODO: Open File Dialogue instead
	Mat img = readJpgAsBGRA(path);
	Mat backup = img.clone();

	std::vector<Cap> caps; // look into using shared pointers for this
	CapMapping map;
	CapMap cm = CapMap(cp, 20);

	//TODO: Throw Exception instead
	if (img.empty())
	{
		std::cout << "Could not read the image: " << path << std::endl;
		return 1;
	}

	namedWindow("Kronko", WINDOW_NORMAL);
	createTrackbar("Width", "Kronko", &wdth_mm, 1000);
	setTrackbarMin("Width", "Kronko", CAP_SIZE);

	//TODO: Try to give a live preview
	while (!cancel) {
		try {
			Rect windowRect = getWindowImageRect("Kronko");
			int windowWidth = windowRect.width;
			int windowHeight = windowRect.height;
			resizeImage(img, windowWidth, windowHeight);
			resizeWindow("Kronko", windowWidth, windowHeight);
		}
		catch (...) {
			return 1; //Window has been closed
		}
		imshow("Kronko", img);
		int k = waitKey(0); // Wait for a keystroke in the window
		switch (k) {
			//TODO: Add : Load img, Import, Show Loaded Caps, 
		case 's': // SAVE
			imwrite(path, img);
			break;
		case 'b':
			// LOAD BACKUP
			img = backup.clone();
			break;
		case '1':
			// SQUARE LAYOUTER
			cap_positions = lom->createLayoutmm(img, wdth_mm);
			circ_px = (int)(((float)img.size().width / (float)wdth_mm) * CAP_SIZE);
			for (auto& p : cap_positions) {
				circle(img, p, circ_px / 2, { 255,255,255 }, 1);
			}
			break;
		case 'a':
			// ASSEMBLE
			if (!cap_positions.empty()) {
				caps = cap_importer.getCaps();
				if (caps.empty()) {
					std::cerr << "No Caps Loaded." << std::endl;
					break;
				}
				circ_px = (int)(((float)img.size().width / (float)wdth_mm) * CAP_SIZE);
				map = cm.createCapMappingHist(img, cap_positions, caps, circ_px);
				assembleMapping(img, map, caps, circ_px);
			}
			break;
		case 'i':
			//	IMPORT
			cap_importer.addFolder(CAP_IMG_FOLDER);
			break;
		case 'c':
			// CLEAR DB
			db.clearDB();
			break;
		case 'x': // QUIT
		case 27:
			cancel = true;
			break;
		default:
			// HELP
			print_help();
			break;
		}

	}
	return 0;
}
