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
    std::vector<json> jsonDataVector;
    std::ifstream jsonFile(this->path);
    std::vector<Cap> caps;
    std::vector<std::thread> threads;
    std::mutex capsMutex;

    if (!jsonFile.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + this->path);
    }
    while (!jsonFile.eof()) {
        json jsonData;
        try {
            jsonFile >> jsonData;
            if (!jsonData.empty()) { 
                jsonDataVector.push_back(jsonData);
            }
        }
        catch (const json::parse_error& e) {
        }
    }

    jsonFile.close();

    for (const auto& jsonData : jsonDataVector) {
        threads.emplace_back([this, &caps, &jsonData, &capsMutex]() {
            try
            {
                Cap cap = Cap(jsonData);
                std::lock_guard<std::mutex> lock(capsMutex);
                caps.push_back(cap);
            }
            catch (const std::exception&){
            }
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return caps;
}


void JsonDB::clearDB() {
	fs::remove(fs::path(this->path));
};