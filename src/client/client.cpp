#include "client.h"

#include "../common/constants.h"

#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Client::Client()
    : clientSocket(-1)
{
}

bool Client::createSocket()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1)
    {
        std::cerr << "[ERROR] Failed to create socket.\n";
        return false;
    }

    std::cout << "[INFO] Client socket created.\n";
    return true;
}

bool Client::connectToServer()
{
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if (inet_pton(AF_INET,
                  "127.0.0.1",
                  &serverAddress.sin_addr) <= 0)
    {
        std::cerr << "[ERROR] Invalid server address.\n";
        return false;
    }

    if (connect(clientSocket,
                reinterpret_cast<sockaddr*>(&serverAddress),
                sizeof(serverAddress)) == -1)
    {
        std::cerr << "[ERROR] Failed to connect to server.\n";
        return false;
    }

    std::cout << "[INFO] Connected to server.\n";
    return true;
}

void Client::disconnect()
{
    if (clientSocket != -1)
    {
        close(clientSocket);
        clientSocket = -1;
    }

    std::cout << "[INFO] Disconnected.\n";
}

bool Client::sendMessage(const std::string& message)
{
    ssize_t bytesSent = send(
        clientSocket,
        message.c_str(),
        message.size(),
        0);

    return bytesSent != -1;
}

std::string Client::receiveMessage()
{
    char buffer[1024]{};

    ssize_t bytesReceived =
        recv(clientSocket,
             buffer,
             sizeof(buffer),
             0);

    if (bytesReceived <= 0)
        return "";

    return std::string(buffer, bytesReceived);
}