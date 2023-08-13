#include "CapDB.h"

CapDB::CapDB(std::string path): path(path)
{
}

void CapDB::storeCap(Cap& cap)
{
	throw std::runtime_error("[CapDB::storeCap] Called a virtual Function");
}

void CapDB::storeCaps(std::vector<Cap> caps)
{
	throw std::runtime_error("[CapDB::storeCaps] Called a virtual Function");
}

std::vector<Cap> CapDB::getCaps()
{
	throw std::runtime_error("[CapDB::getCaps] Called a virtual Function");
	return std::vector<Cap>();
}

void CapDB::clearDB()
{
	throw std::runtime_error("[CapDB::ClearDB] Called a virtual Function");
}
