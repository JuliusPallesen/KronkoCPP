#include "Cap.h"

Cap::Cap(json data)
{
    cv::Mat img = cv::imread(data[CAP_PATH], cv::IMREAD_UNCHANGED);
    if (img.empty())
    {
        throw std::runtime_error("[CAP] Couldn't read image:" + data[CAP_PATH]);
    }
    json col = data[CAP_COLOR];
    json dir = data[CAP_DIR];
    this->id = data[CAP_ID];
    this->brand = data[CAP_BRAND];
    this->path = data[CAP_PATH];
    this->prio = data[CAP_PRIO];
    this->max_amount = data[CAP_MAX];
    this->color = cv::Vec3i(col[0],col[1],col[2]);
    this->dir = cv::Vec2b(dir[0],dir[1]);
    this->img = img;
}

Cap::Cap(int id, std::string brand, std::string path, cv::Vec3i color, cv::Vec2b dir, cv::Mat img, int prio, int max_amount)
{
    this->id = id;
    this->brand = brand;
    this->path = path;
    this->color = color;
    this->dir = dir;
    this->img = img;
    this->prio = prio;
    this->max_amount = max_amount;
}

json Cap::serializeJSON()
{
    json data;
    cv::Vec3i col = this->color;
    cv::Vec2b dir = this->dir;
    data[CAP_ID] = this->id;
    data[CAP_BRAND] = this->brand;
    data[CAP_PATH] = this->path;
    data[CAP_COLOR] = { col[0],col[1],col[2] };
    data[CAP_DIR] = { dir[0], dir[1] };
    data[CAP_PRIO] = this->prio;
    data[CAP_MAX] = this->max_amount;
	return data;
}

std::string Cap::toString()
{
    return this->brand + " " + std::to_string(this->id);
}
