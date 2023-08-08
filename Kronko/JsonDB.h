#pragma once
#include "CapDB.h"
#include <fstream>

class JsonDB :
    public CapDB
{
public:
    using CapDB::CapDB;
    void storeCap(Cap & cap) override;
    void storeCaps(Caps caps) override;
    Caps getCaps() override;
};

