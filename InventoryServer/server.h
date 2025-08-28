#ifndef SERVER_H

#define SERVER_H

#include <winsock2.h>
#include <vector>
#include <thread>

namespace server
{

void startup();
void mainLoop();
void cleanup();

}

#endif