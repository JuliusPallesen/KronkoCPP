#pragma once
#include "CapDB.h"
#include <fstream>
#include <thread>

class JsonDB :
    public CapDB
{
public:
    JsonDB();
    JsonDB(std::string path);
    void storeCap(Cap & cap) override;
    void storeCaps(std::vector<Cap> caps) override;
    std::vector<Cap> getCaps() override;
    void clearDB() override;
};

