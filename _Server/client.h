#ifndef CLIENT_H

#define CLIENT_H

#include <winsock2.h>
#include <vector>

namespace server
{

class InventoryClient
{
public:
    InventoryClient(SOCKET sock);
    ~InventoryClient();

    void mainLoop();
    void close();

    static void handleClient(const SOCKET& s);

private:
    SOCKET sock;
};

extern std::vector<InventoryClient> clients;

}

#endif