#include "client.h"
#include "consts.h"

#include <iostream>
#include <thread>
#include <mutex>

namespace server
{

std::mutex coutMutex;
std::vector<InventoryClient> clients;

InventoryClient::InventoryClient(SOCKET sock)
    : sock(sock)
{
}

InventoryClient::~InventoryClient() {

}

void InventoryClient::mainLoop() {
    std::cout << "InventoryClient::mainLoop connection initialized\n";

    char buffer[BUFFER_LEN];

    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Received: " << buffer << std::endl;
        }

        send(sock, buffer, bytesReceived, 0); // sending back
    }

    close();
}

void InventoryClient::close()
{
    std::cout << "InventoryClient::close connection closed\n";
    closesocket(sock);
}

void InventoryClient::handleClient(const SOCKET& s) {
    std::cout << "InventoryClient::handleClient\n";

    InventoryClient& client = clients.emplace_back(s);
    client.mainLoop();
}

    
}