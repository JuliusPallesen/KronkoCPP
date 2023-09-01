#include "KronkoConfig.h"

KronkoConfig::KronkoConfig()
{
	this->imgOpened = false;
	this->widthMm = 1000;
	this->widthRes = 0;
	this->heightRes = 0;
	this->outputFilename = "./output.jpg";
	this->capImportPaths = std::vector<std::string>();
	this->layouter = new SquareLayouter();
	this->colorPicker = new ColorGauss();
	this->database = new JsonDB();
	this->capImport = CapImport(this->database,this->colorPicker);
	this->capMapper = CapMap(this->colorPicker);
}

KronkoConfig::~KronkoConfig()
{
	delete(colorPicker);
	delete(layouter);
	delete(database);
	this->colorPicker = nullptr;
	this->layouter = nullptr;
	this->database = nullptr;
}

void KronkoConfig::setColorPicker(ColorPicker* cp) {
	this->colorPicker = cp;
	this->capImport.setColorPicker(cp);
	this->capMapper.setColorPicker(cp);
}

std::vector<cv::Point> KronkoConfig::getLayout(CapLayoutManager* lay, bool preview) {
	this->layouter = lay;
	conditionalResize(this->img, this->widthRes);
	std::vector<cv::Point> capPositions = this->layouter->createLayout(this->img.size(), this->widthMm);
	if (preview)
	{
		int circlePixels = getCircleSizePx(this->img, this->widthMm);
		for (auto& p : capPositions) {
			circle(this->img, p, circlePixels / 2, { 255,255,255 }, (this->img.cols / 1000) + 1);
		}
	}
	return capPositions;
};

void KronkoConfig::execConfig() {
	//Import all added folders
	if (!this->capImportPaths.empty()) for (auto& importPath : this->capImportPaths) this->capImport.addFolder(importPath);
	if (!this->imgOpened) return;
	conditionalResize(this->img, this->widthRes);
	std::vector<Cap> caps = this->capImport.getCaps();
	if (caps.empty()) {
		std::cerr << "Couldn't load any Bottlecaps, please specify an import folder or json file.";
	}
	else {
		std::vector<cv::Point> positions = this->layouter->createLayout(this->img.size(), this->widthMm);
		std::cout << "Overall caps needed: " << positions.size() << std::endl;
		int circlePixels = getCircleSizePx(this->img, this->widthMm);
		CapMapping map = this->capMapper.createCapMapping(this->img, positions, caps, circlePixels);
		for (int i = 0; i < map.size(); i++) std::cout << caps[i].brand << ": " << map[i].size() << std::endl;
		assembleMapping(this->img, map, caps, circlePixels);
		cv::imwrite(this->outputFilename, this->img);
	}
}