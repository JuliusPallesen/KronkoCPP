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
	std::cout << "1-3:\t\t Chose Layouter (Square, Triangle, Packing)\n";
	std::cout << "g:\t\t Gaussian Colopicker";
	std::cout << "m:\t\t Mean Colopicker";
	std::cout << "p:\t\t Point Colopicker";
	std::cout << "s:\t\t Simple/Normal mapping";
	std::cout << "h:\t\t Hist/Better mapping";
	std::cout << "i:\t\t Import Caps from DB\n";
	std::cout << "c:\t\t clear DB\n";
	std::cout << "s:\t\t Save image\n";
	std::cout << "b:\t\t Load backup image / reset image\n";
	std::cout << "Esc/x:\t\t Quit.\n";
}

int kronkoGUI(KronkoConfig & cfg) {
	using namespace cv;
	const int MAX_WIDTH = 5000;
	bool cancel = false;
	bool imgOpened = false;
	cv::Mat backup;
	std::vector<cv::Point> capPositions;
	
	//Trackbars get callback functions with a pointer to the Config as context
	namedWindow("Kronko", WINDOW_NORMAL);
	createTrackbar("Width (mm)", "Kronko", nullptr, MAX_WIDTH, [](int value, void* ptr) {((KronkoConfig*)ptr)->widthMm = value; }, &cfg);
	setTrackbarMin("Width (mm)", "Kronko", CAP_SIZE + 1);
	setTrackbarPos("Width (mm)", "Kronko", CAP_SIZE + 1);
	createTrackbar("Resolution", "Kronko", nullptr, MAX_WIDTH,[](int value, void* ptr) { ((KronkoConfig*)ptr)->widthRes = value; }, & cfg);
	setTrackbarMin("Resolution", "Kronko", 0);
	Rect windowRect = getWindowImageRect("Kronko");
	Rect windowRectPrev = windowRect;

	while (!cancel) {
		//check if img initialized
		if (!imgOpened) {
			try
			{
				cfg.img = openImageWithFileDialog();
				cfg.widthRes = cfg.img.size().width;
				setTrackbarPos("Resolution", "Kronko", cfg.widthRes);
				backup = cfg.img.clone();
				imgOpened = true;
			}
			catch (const std::exception& ex)
			{
				imgOpened = false;
				std::cerr << ex.what() << std::endl;
			}
		}
		imshow("Kronko", cfg.img);
		int k = waitKey(0); // Wait for a keystroke in the window
		switch (k) {
		case 's': // SAVE
			imwrite(cfg.outputFilename, cfg.img);
			break;
		case 'b': // LOAD BACKUP
			std::cout << "Loading backup" << std::endl;
			cfg.img = backup.clone();
			break;
		case '1': // SQUARE LAYOUTER
			std::cout << "Calculating square layout..." << std::endl;
			capPositions = cfg.getLayout(new SquareLayouter());
			break;
		case '2':
			std::cout << "Calculating triangle layout..." << std::endl;
			capPositions = cfg.getLayout(new TriangleLayouter());
			break;
		case 'a': // ASSEMBLE
			std::cout << "Assembeling bottlecaps...\n";
			cfg.execConfig();
			break;
		case 'i': // IMPORT
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
		case 'c': // CLEAR DB
			std::cout << "Clearing DB\n";
			cfg.database->clearDB(); // move to cap import?
			break;
		case 'g': // GAUSS PICKER
			std::cout << "Gaussian color selection\n";
			cfg.setColorPicker(new ColorGauss());
			break;
		case 'm': // MEAN
			std::cout << "Mean color selection\n";
			cfg.setColorPicker(new ColorAvg());
			break;
		case 'p':
			std::cout << "Point color selection\n";
			cfg.setColorPicker(new ColorPoint());
			break;
		case 'n': //HIST MAPPING
			std::cout << "Simple/normal mapping\n";
			cfg.capMapper.setMapMode(CAP_MAP_SIMPLE);
			break;
		case 'h': //SIMPLE MAPPING
			std::cout << "Best/hist mapping\n";
			cfg.capMapper.setMapMode(CAP_MAP_HIST);
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
	return 0;
}
