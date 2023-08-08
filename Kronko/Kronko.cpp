#include "Kronko.h"

using namespace cv;

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

int main(int argc, char* argv[])
{
	// TODO: 
	//			- Parse commandline args
	//			- Move GUI stuff to KronkoGUI  

	bool cancel = false;
	int wdth_mm = CAP_SIZE;
	int circ_px;

	CapLayoutManager* lom = new SquareLayouter;
	std::vector<cv::Point> cap_positions;

	ColorPicker * cp = new ColorPoint();

	JsonDB db("./JSON/db.json");
	CapImport cap_importer(&db,cp);

	// TODO: Open File Dialogue instead
	std::string lena_path = "./Images/lena.jpg";
	Mat img = imread(lena_path, IMREAD_COLOR);
	Mat backup = img.clone();

	Caps caps;
	CapMapping map;
	CapMap cm = CapMap(cp, 20);

	//TODO: Throw Exception instead
	if (img.empty())
	{
		std::cout << "Could not read the image: " << lena_path << std::endl;
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
			//resizeImage(img, windowWidth, windowHeight);
			//resizeWindow("Kronko", windowWidth, windowHeight);
		}
		catch (...) {
			return 1; //Window has been closed
		}
		imshow("Kronko", img);
		int k = waitKey(0); // Wait for a keystroke in the window
		switch (k) {
			//TODO: Add : Load img, Import, Show Loaded Caps, 
		case 's': // SAVE
			imwrite(lena_path, img);
			break;
		case 'b': // LOAD BACKUP
			img = backup.clone();
			break;
		case '1': // SQUARE LAYOUTER
			circ_px = (int)(((float)img.size().width / (float)wdth_mm) * CAP_SIZE);
			//	rewrite Layouter to work in mm instead of px? 
			//	(26 )(26 )(26 ) caps (mm)
			//	(100)(100)(100) caps (px)
			//	<----------> wdth_mm (98mm)
			//  <----------> original px_width (221)
			//	<----------> new px_width -> 300
			//				
			cap_positions = lom->createLayout(img.size(), wdth_mm);
			caps = cap_importer.getCaps();
			if (caps.empty()) {
				std::cerr << "No Caps Loaded." << std::endl;
				return 1;
			}
			//map = cm.createCapMappingSimple(img,cap_positions,caps);
			map = cm.createCapMappingHist(img, cap_positions, caps);
			//std::cout << "final mapping:" << std::endl;
			for (int i = 0; i < map.size(); i++)
			{
				if (!map[i].empty())
				{
					for (int j = 0; j < map[i].size(); j++)
					{
						std::cout << caps[i].toString() << std::endl;
						overlayImage(img,caps[i].img,map[i][j],circ_px);
					}
				}
			}
			for (auto& p : cap_positions) {
				circle(img, p, circ_px / 2, { 255,255,255 }, 1);
			}
			break;
		case 'i':
			cap_importer.addFolder("./BottleCap/");
			break;
		case 'x': // QUIT
		case 27:
			cancel = true;
			break;
		}
	}
	return 0;
}
