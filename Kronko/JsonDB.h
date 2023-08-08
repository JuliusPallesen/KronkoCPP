#pragma once
#include "CapDB.h"
#include <fstream>

class JsonDB :
    public CapDB
{
public:
    using CapDB::CapDB;
    void storeCap(Cap & cap) override;
    void storeCaps(std::vector<Cap> caps) override;
    std::vector<Cap> getCaps() override;
};

