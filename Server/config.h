#pragma once

#ifndef CONFIG_FILE

#define CONFIG_FILE "config.ini"

#endif // !CONFIG_FILE

#include <string>

namespace server
{
    void loadConfigFile(const char* filename = CONFIG_FILE);
	std::string getConfig(const std::string& key);
	void setConfig(const std::string& key, const std::string& value);
	void eraseConfig(const std::string& key);
	void updateConfigFile(const char* filename = CONFIG_FILE);
	void clearConfig();
}