#include "KronkoGUI.h"

cv::Mat openImageWithFileDialog() {
	OPENFILENAME ofn;
	wchar_t szFile[260] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Image Files\0*.png;*.jpg\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE) {
		std::wstring wstrPath = szFile;
		char imagePath[MAX_PATH];
		WideCharToMultiByte(CP_UTF8, 0, wstrPath.c_str(), -1, imagePath, MAX_PATH, NULL, NULL);
		cv::Mat image = readimGBRA(imagePath);
		return image;
	}
	else {
		throw std::runtime_error("No file selected.");
		return cv::Mat();
	}
}

std::string openFolderWithFileDialog() {
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));

	bi.hwndOwner = NULL;
	bi.ulFlags = BIF_USENEWUI;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL) {
		wchar_t folderPath[MAX_PATH];
		if (SHGetPathFromIDList(pidl, folderPath)) {
			char folder[MAX_PATH];
			WideCharToMultiByte(CP_UTF8, 0, folderPath, -1, folder, MAX_PATH, NULL, NULL);

			std::string folderStr(folder);
			CoTaskMemFree(pidl);
			return folderStr;
		}
		CoTaskMemFree(pidl);
	}

	return std::string();
}


void print_help() {
	std::cout << "\nHelp:\n";
	std::cout << "1,2:\t Chose Layouter (Square, Triangle)\n";
	std::cout << "g:\t Gaussian Colopicker\n";
	std::cout << "m:\t Mean Colopicker\n";
	std::cout << "p:\t Point Colopicker\n";
	std::cout << "s:\t Normal mapping (use bottlecaps in order of position occurence)\n";
	std::cout << "h:\t Best mapping (use best fitting bottlecaps first)\n";
	std::cout << "i:\t Import Caps folder\n";
	std::cout << "c:\t Clear DB\n";
	std::cout << "s:\t Save image\n";
	std::cout << "b:\t Load backup image / reset image\n";
	std::cout << "r:\t Toggle sliders on/off to resize Window\n";
	std::cout << "Esc/x:\t\t Quit.\n";
}

void loadImg(KronkoConfig & cfg) {
	try
	{
		cfg.img = openImageWithFileDialog();
		cfg.widthRes = cfg.img.size().width;
		cfg.imgOpened = true;
	}
	catch (const std::exception& ex)
	{
		cfg.imgOpened = false;
		std::cerr << ex.what() << std::endl;
	}
}

void createKronkoWindow(KronkoConfig & cfg, int res = 0) {
	using namespace cv;
	const int MAX_WIDTH = 5000;
	//Trackbars get callback functions with a pointer to the Config as context
	namedWindow("Kronko", WINDOW_NORMAL);
	createTrackbar("Width (mm)", "Kronko", nullptr, MAX_WIDTH, [](int value, void* ptr) {((KronkoConfig*)ptr)->widthMm = value; }, &cfg);
	setTrackbarMin("Width (mm)", "Kronko", CAP_SIZE + 1);
	setTrackbarPos("Width (mm)", "Kronko", CAP_SIZE + 1);
	createTrackbar("Resolution", "Kronko", nullptr, MAX_WIDTH, [](int value, void* ptr) { ((KronkoConfig*)ptr)->widthRes = value; }, &cfg);
	setTrackbarMin("Resolution", "Kronko", cfg.widthRes);
}

int kronkoGUI(KronkoConfig & cfg) {
	using namespace cv;
	bool cancel = false;
	bool resizeToggle = false; // Used to temporarily delete sliders to resize window
	bool imgOpened = false;
	cv::Mat backup;
	std::vector<cv::Point> capPositions;
	
	createKronkoWindow(cfg);

	while (!cancel) {
		if (!cfg.imgOpened) {
			loadImg(cfg);
			cv::setTrackbarPos("Resolution", "Kronko", cfg.widthRes);
			backup = cfg.img.clone();
		}
		try
		{
			imshow("Kronko", cfg.img);
		}
		catch (const std::exception&)
		{
			return 1;
		}
		int k = waitKey(0);
		switch (k) {
		case 'l': 
			loadImg(cfg);
			cv::setTrackbarPos("Resolution", "Kronko", cfg.widthRes);
			backup = cfg.img.clone();
			break;
		case 's':
			imwrite(cfg.outputFilename, cfg.img);
			break;
		case 'b':
			std::cout << "Loading backup" << std::endl;
			cfg.img = backup.clone();
			break;
		case '1':
			std::cout << "Calculating square layout..." << std::endl;
			capPositions = cfg.getLayout(new SquareLayouter());
			break;
		case '2':
			std::cout << "Calculating triangle layout..." << std::endl;
			capPositions = cfg.getLayout(new TriangleLayouter());
			break;
		case 'a':
			std::cout << "Assembeling bottlecaps...\n";
			cfg.execConfig();
			break;
		case 'i':
			std::cout << "Importing folder\n";
			try
			{
				std::string folderPath = openFolderWithFileDialog();
				cfg.capImport.addFolder(folderPath);
			}
			catch (const std::exception& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
			break;
		case 'c':
			std::cout << "Clearing DB\n";
			cfg.capImport.clearDB(); // move to cap import?
			break;
		case 'g':
			std::cout << "Gaussian color selection\n";
			cfg.setColorPicker(new ColorGauss());
			break;
		case 'm':
			std::cout << "Mean color selection\n";
			cfg.setColorPicker(new ColorAvg());
			break;
		case 'p':
			std::cout << "Point color selection\n";
			cfg.setColorPicker(new ColorPoint());
			break;
		case 'n':
			std::cout << "Simple/normal mapping\n";
			cfg.capMapper.setMapMode(CAP_MAP_SIMPLE);
			break;
		case 'h':
			std::cout << "Best/hist mapping\n";
			cfg.capMapper.setMapMode(CAP_MAP_HIST);
			break;
		case 'r':
			std::cout << "Toggle Trackbars\n";
			resizeToggle = !resizeToggle;
			if (resizeToggle) {
				destroyWindow("Kronko");
				namedWindow("Kronko", WINDOW_NORMAL);
			} else {
				createKronkoWindow(cfg);
			}
			break;
		case 'x':
		case 27:
			cancel = true;
			break;
		default:
			print_help();
			break;
		}

	}
	return 0;
}
