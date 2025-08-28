#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024];

    // Inicializa Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Cria socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Define endereço do servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    inet_pton(AF_INET, "192.168.1.10", &serverAddr.sin_addr); // localhost

    // Conecta ao servidor
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erro ao conectar.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Conectado ao servidor!\n";

    // Envia mensagem
    const char* msg = "Hello, server!";
    send(clientSocket, msg, strlen(msg), 0);

    // Recebe resposta
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Resposta: " << buffer << "\n";
    }

    // Encerra conexão
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}