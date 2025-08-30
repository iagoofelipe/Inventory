#include "tools.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

namespace inventory
{
	void dispatchEvent(const wxEventTypeTag<wxCommandEvent>& tag, wxWindow* sender, void* data, int* value)
	{
		wxCommandEvent evt(tag, sender->GetId());
		evt.SetEventObject(sender);
		if (data) evt.SetClientData(data);
		if (value) evt.SetInt(*value);
		sender->ProcessWindowEvent(evt);
	}

	std::string Config::operator[](const std::string& key) { return Get(key); }

	Config& Config::GetInstance()
	{
		static Config instance;
		return instance;
	}

	bool Config::Initialize()
	{
		if (initialized) return true;

		std::ifstream file(filename);
		if (!file.is_open()) {
			return false;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key, value;
			if (std::getline(iss, key, '=') && std::getline(iss, value)) {
				data[key] = value;
			}
		}
		
		file.close();
		initialized = true;
		return true;
	}

	std::string Config::Get(const std::string& key)
	{
		return data.count(key) ? data[key] : "";
	}

	void Config::Set(const std::string& key, const std::string& value)
	{
		data[key] = value;
	}

	void Config::Erase(const std::string& key)
	{
		if (data.find(key) != data.end())
			data.erase(key);
	}

	bool Config::UpdateFile()
	{
		std::ofstream file(filename);
		if (!file.is_open()) return false;

		for (const auto& pair : data) {
			file << pair.first << "=" << pair.second << "\n";
		}

		file.close();
		return true;
	}

	Config::Config()
		: initialized(false)
		, filename("config.ini")
	{
	}
}