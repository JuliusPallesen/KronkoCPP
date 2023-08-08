#include "JsonDB.h"

void JsonDB::storeCap(Cap & cap)
{
	//TODO: Maybe check if Brand already exists
	std::ofstream jsonFile(this->path, std::ios::app);
	if (jsonFile.is_open())
	{
		std::cout << "JSON: Storing " << cap.brand << std::endl;
		jsonFile << cap.serializeJSON().dump(4) << std::endl;
		jsonFile.close();
	}
	else {
		throw std::runtime_error("Could not open JSON file: " + this->path);
	}
}

void JsonDB::storeCaps(Caps caps)
{
	std::ofstream jsonFile(this->path, std::ios::app);
	if (jsonFile.is_open())
	{
		for (Cap cap : caps) {
			std::cout << "JSON: Storing " << cap.brand << '\n';
			jsonFile << cap.serializeJSON().dump(4) << std::endl;
		}
		jsonFile.close();
	}
	else {
		throw std::runtime_error("Could not open JSON file: " + this->path);
	}
}

Caps JsonDB::getCaps()
{
	//Rewrite to return JSON objects, init images parallel
	Caps caps;
	std::ifstream jsonFile(this->path);
	if (jsonFile.is_open()) {
		json jsonData;
		while (!jsonFile.eof()) {
			try {
				jsonFile >> jsonData;
				std::cout << "JSON data: " << jsonData.dump() << std::endl; // Print JSON data
				caps.push_back(Cap::Cap(jsonData));
			}
			catch (const json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
				caps.pop_back();
			}
		}
		jsonFile.close();
	}
	return caps;
}
