#pragma once

#ifndef SERVER_CONFIG

#define SERVER_CONFIG
#define CONFIG_FILE "config.ini"
#define CONFIG_DEF_HOST "localhost"
#define CONFIG_DEF_PORT "33060"
#define CONFIG_DEF_USER "root"
#define CONFIG_DEF_PASSWORD ""
#define CONFIG_DEF_DB "inventory_stock"

#endif

#include <string>

namespace server
{
    bool loadConfigFile(const char* filename = CONFIG_FILE);
	std::string getConfig(const std::string& key);
	void setConfig(const std::string& key, const std::string& value);
	void eraseConfig(const std::string& key);
	bool updateConfigFile(const char* filename = CONFIG_FILE);
	void clearConfig();
	bool configFromTerminal(const char* filename = CONFIG_FILE);
}