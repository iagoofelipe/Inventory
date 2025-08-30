#include "config.h"

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>

namespace server
{
    std::unordered_map<std::string, std::string> configData;
    bool configSet = false;

bool loadConfigFile(const char* filename) {
    if (configSet)
        return true;

    std::ifstream file(filename);
    if (!file.is_open()) {
		// File does not exist, trying to create it
        if (!configFromTerminal(filename))
            return false;
    }

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
    return true;
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

bool updateConfigFile(const char* filename) {
	std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& pair : configData) {
        file << pair.first << "=" << pair.second << "\n";
	}

	file.close();
    return true;
}

void clearConfig()
{
    configSet = false;
    configData.clear();
}

bool configFromTerminal(const char* filename)
{
    std::string buffer;
    std::cout << "[Database] setting up configuration...\n";

    std::cout << "Database (" << CONFIG_DEF_DB << "): ";
    std::getline(std::cin, buffer);
    setConfig("database", buffer.empty() ? CONFIG_DEF_DB : buffer);

    std::cout << "Host (" << CONFIG_DEF_HOST << "): ";
    std::getline(std::cin, buffer);
    setConfig("host", buffer.empty() ? CONFIG_DEF_HOST : buffer);

    std::cout << "Port (" << CONFIG_DEF_PORT << "): ";
    std::getline(std::cin, buffer);
    setConfig("port", buffer.empty() ? CONFIG_DEF_PORT : buffer);

    std::cout << "User (" << CONFIG_DEF_USER << "): ";
    std::getline(std::cin, buffer);
    setConfig("user", buffer.empty() ? CONFIG_DEF_USER : buffer);

    std::cout << "Password (" << CONFIG_DEF_PASSWORD << "): ";
    std::getline(std::cin, buffer);
    setConfig("password", buffer.empty() ? CONFIG_DEF_PASSWORD : buffer);

    return updateConfigFile(filename);
}

}
