#include "InventoryServer.h"

#include "consts.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

extern InventoryServer* pServer = new InventoryServer;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
	if (fdwCtrlType == CTRL_C_EVENT) {
		std::cout << "\nbreaking loop...\n";
		delete pServer;
		ExitProcess(0);
		return TRUE;
	}
	return FALSE;
}

InventoryServer::InventoryServer()
	: keepLoop(true)
{
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// address
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
}

InventoryServer::~InventoryServer()
{
	keepLoop = false;

	std::cout << "destroying...\n";
	for (InventoryClient* client : clients) {
		delete client;
	}

	clients.clear();
	closesocket(sock);
	WSACleanup();
}

void InventoryServer::mainLoop()
{
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	listen(sock, SOMAXCONN);
	std::cout << "server listening to port " << PORT << "...\n";

	while (keepLoop)
	{
		SOCKET client_sock = accept(sock, nullptr, nullptr);
		if (client_sock == INVALID_SOCKET) continue;

		InventoryClient* c = new InventoryClient(client_sock);
		
		c->addEventDispatcher(InventoryClient::EVT_CLOSE, [&](void* d) { this->OnClientClose((InventoryClient*) d); });
		clients.insert(c);
	}
}

void InventoryServer::OnClientClose(InventoryClient* client)
{
	clients.erase(client);
	delete client;
}
