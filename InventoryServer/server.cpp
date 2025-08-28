#include "server.h"
#include "client.h"
#include "consts.h"

#include <iostream>

namespace server
{

std::vector<std::thread> threads;

WSADATA wsaData;
SOCKET serverSocket;
sockaddr_in addr;

void startup() {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
    listen(serverSocket, SOMAXCONN);
}

void mainLoop() {
    std::cout << "listening to PORT " << PORT << "...\n";

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;

        std::cout << "connection received\n";
        threads.emplace_back(InventoryClient::handleClient, clientSocket);
    }
}

void cleanup() {
    for(auto& c : clients) {
        c.close();
    }
    
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    threads.clear();
    clients.clear();

    closesocket(serverSocket);
    WSACleanup();
}

}