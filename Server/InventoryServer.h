#pragma once

#include "InventoryClient.h"

#include <windows.h>
#include <unordered_set>

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);

class InventoryServer
{
public:
	InventoryServer();
	~InventoryServer();

	void mainLoop();

private:
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in addr;
	bool keepLoop;
	std::unordered_set<InventoryClient*> clients;

	void OnClientClose(InventoryClient* client);
};

extern InventoryServer* pServer;