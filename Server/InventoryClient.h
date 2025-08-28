#pragma once

#include "consts.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <functional>
#include <map>
#include <vector>
#include <string>

class InventoryClient
{
public:

	enum EVT
	{
		EVT_CLOSE
	};

	InventoryClient(SOCKET sock);
	~InventoryClient();

	void mainLoop();
	void addEventDispatcher(EVT e, std::function<void(void*)> func);

private:
	SOCKET sock;
	std::map<EVT, std::vector<std::function<void(void*)>>> evts;
	char buffer[BUFFER_SIZE];
	std::string sbuffer;

	void dispatch(EVT e, void* data = (void*)nullptr);
	void _mainLoop();
};

