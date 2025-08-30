#pragma once

#include "consts.h"

#include <string>
#include <wx/event.h>
#include <wx/window.h>

namespace inventory
{
	void dispatchEvent(const wxEventTypeTag<wxCommandEvent>& tag, wxWindow* sender, void* data = nullptr, int* value = nullptr);

	class Config
	{
	public:
		Config(const Config&) = delete;
		Config& operator=(const Config&) = delete;

		std::string operator[](const std::string& key);

		static Config& GetInstance();
		bool Initialize();
		std::string Get(const std::string& key);
		void Set(const std::string& key, const std::string& value);
		void Erase(const std::string& key);
		bool UpdateFile();

	private:
		Config();

		bool initialized;
		std::unordered_map<std::string, std::string> data;
		const std::string filename;
	};
}