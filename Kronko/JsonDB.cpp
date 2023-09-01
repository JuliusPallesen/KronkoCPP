#include "JsonDB.h"

JsonDB::JsonDB()
{
	this->path = "./db.json";
}

JsonDB::JsonDB(std::string path)
{
	this->path = path;
}

void JsonDB::storeCap(Cap& cap)
{
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

void JsonDB::storeCaps(std::vector<Cap> caps)
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

std::vector<Cap> JsonDB::getCaps()
{
	std::vector<Cap> caps;
	std::ifstream jsonFile(this->path);
	if (jsonFile.is_open()) {
		while (!jsonFile.eof()) {
			try {
				json jsonData;
				jsonFile >> jsonData;
				if (!jsonData.empty()) {  // Check if JSON data is empty before parsing
					std::cout << "JSON data: " << jsonData.dump() << std::endl; // Print JSON data
					caps.push_back(Cap::Cap(jsonData));
				}
			}
			catch (const json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}
		jsonFile.close();
	}
	return caps;
}

void JsonDB::clearDB() {
	fs::remove(fs::path(this->path));
};