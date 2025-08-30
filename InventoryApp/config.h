#pragma once

#include "consts.h"
#include <string>

bool loadConfigFile(const char* filename = CONFIG_FILE);
std::string getConfig(const std::string& key);
void setConfig(const std::string& key, const std::string& value);
void eraseConfig(const std::string& key);
bool updateConfigFile(const char* filename = CONFIG_FILE);
void clearConfig();
