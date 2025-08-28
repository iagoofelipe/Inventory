#include "server.h"

int main() {
	server::startup();
    server::mainLoop();
    server::cleanup();
}