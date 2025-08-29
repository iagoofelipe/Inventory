#include "config.h"

#include <fstream>
#include <sstream>
#include <unordered_map>

namespace server
{
    std::unordered_map<std::string, std::string> configData;
    bool configSet = false;

void loadConfigFile(const char* filename) {
    if (configSet)
        return;

    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            configData[key] = value;
        }
    }

    file.close();
    configSet = true;
    return;
}

std::string getConfig(const std::string& key) {
    auto it = configData.find(key);
    return (it != configData.end()) ? it->second : "";
}

void setConfig(const std::string& key, const std::string& value) {
	configData[key] = value;
}

void eraseConfig(const std::string& key) {
    if(configData.find(key) != configData.end())
		configData.erase(key);
}

void updateConfigFile(const char* filename) {
	std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& pair : configData) {
        file << pair.first << "=" << pair.second << "\n";
	}

	file.close();
}

void clearConfig()
{
    configSet = false;
    configData.clear();
}

}
