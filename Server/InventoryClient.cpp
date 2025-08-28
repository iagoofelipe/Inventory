#include "InventoryClient.h"
#include <iostream>
#include <thread>

InventoryClient::InventoryClient(SOCKET sock)
	: sock(sock)
	, buffer({ 0 })
{
	std::cout << "client connected\n";
}

InventoryClient::~InventoryClient()
{
	std::cout << "client disconnected\n";

	//delete addr;
	closesocket(sock);
}

void InventoryClient::mainLoop()
{
	std::thread t(&InventoryClient::_mainLoop, this);
}

void InventoryClient::addEventDispatcher(EVT e, std::function<void(void*)> func)
{
	if (!evts.count(e)) {
		evts[e] = std::vector<std::function<void(void*)>>();
	}

	evts[e].push_back(func);
}

void InventoryClient::dispatch(EVT e, void* data)
{
	if (!evts.count(e))
		return;

	for (const auto& f : evts[e]) {
		f(data);
	}
}

void InventoryClient::_mainLoop()
{
	while (true) {
		int received = recv(sock, buffer, BUFFER_SIZE, 0);

		if (!received)
			break;

		sbuffer += buffer;
		size_t pos = 0,
			len = sbuffer.size();

		std::cout << "Buffer Init '" << sbuffer << "'\n";

		while ((pos = sbuffer.find(BUFFER_SEP)) != std::string::npos) {
			std::cout << "Received: '" << sbuffer.substr(0, pos) << "'\n";
			int next = pos + BUFFER_SEP_LEN;
			sbuffer = len > next ? sbuffer.substr(pos + BUFFER_SEP_LEN) : "";
		}

		std::cout << "Buffer End '" << sbuffer << "'\n";
	}

	dispatch(EVT_CLOSE, this);
}
