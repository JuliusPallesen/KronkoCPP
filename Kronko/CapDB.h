#pragma once
#include "Cap.h"
#include <filesystem>
#include <string>
#include <vector>
#include "Types.h"

namespace fs = std::filesystem;
class CapDB
{
protected:
	std::string path;
public:
	CapDB();
	CapDB(std::string path);

	virtual void storeCap(Cap& cap);
	virtual void storeCaps(std::vector<Cap> caps);
	virtual std::vector<Cap> getCaps();
	virtual void clearDB();
};

