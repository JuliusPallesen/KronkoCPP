#include "CapImport.h"

CapImport::CapImport(CapDB* db, ColorPicker* cp): dataBase(db), colorPicker(cp), ids(0)
{
    this->dataBase = db;
    this->colorPicker = cp;
}

CapImport::CapImport() : dataBase(new JsonDB("./db.json")), colorPicker(new ColorPoint), ids(0)
{
    this->dataBase = new JsonDB();
    this->colorPicker = new ColorPoint();
}

void CapImport::addCap(Cap & cap) {
    this->caps.push_back(cap);
    this->dataBase->storeCap(cap);
}

void CapImport::addCap(fs::path path) {
    Cap c = this->makeCap(path);
	this->addCap(c);
}

Cap CapImport::makeCap(fs::path path, int prio, int max_amount) {
    using namespace cv;
    Mat img = imread(path.string(), cv::IMREAD_UNCHANGED);
    Vec3i color = Vec3i(0,0,0);
    if (img.empty()) {
        throw std::runtime_error("Could not read the image: " + path.string());
    }
    try
    {
        color = this->getColVec(img);
    }
    catch (const std::runtime_error& ex)
    {
        std::cerr << ex.what() << " thrown for:" << path << "\n";
    }

    Cap cap = Cap(++this->ids,path.stem().string(), path.string(), color, this->getDirVector(img), img, prio, max_amount);
    return cap;
}

void CapImport::addFolder(const std::string path) {
    std::vector<Cap> caps;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string fileExtension = entry.path().extension().string();
                if (fileExtension == ".jpg" || fileExtension == ".png") {
                    std::cout << entry.path() << std::endl;
                    caps.push_back(this->makeCap(entry.path()));
                }
            }
        }
    }
    catch (const fs::filesystem_error& ex) {
        std::cerr << "Error accessing the folder: " << ex.what() << std::endl;
    }
    this->caps.insert(this->caps.end(), caps.begin(), caps.end());
    this->dataBase->storeCaps(caps);
}

void CapImport::setColorPicker(ColorPicker * cp)
{
    this->colorPicker = cp;
}

void CapImport::setDB(CapDB* db)
{
    this->dataBase = db;
}

void CapImport::clearDB() {
    this->dataBase->clearDB();
}

std::vector<Cap> CapImport::getCaps()
{ 
    if (this->caps.empty())
    {
        this->caps = this->dataBase->getCaps();
    }
    return this->caps;
}

cv::Vec3b CapImport::getColVec(cv::Mat& img, cv::Vec3b * c)
{
    if (c == nullptr) {
        return this->colorPicker->getColorV(img);
    }
    return *c;
}

cv::Vec2b CapImport::getDirVector(cv::Mat& img) {
    //TODO: implement
    return cv::Vec2b(0,1);
}
