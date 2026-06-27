#include "server.h"
#include <iostream>
#include "server.h"
#include "../common/constants.h"
// POSIX socket API
#include <sys/socket.h>
#include <string>
// IPv4 structures
#include <netinet/in.h>

// close()
#include <unistd.h>
using namespace std;
Server::Server()
    : serverSocket(-1)
{
}
bool Server::createSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        cerr << "Failed to create socket.\n";
        return false;
    }

    cout << "Socket created successfully.\n";
    cout << "File Descriptor: " << serverSocket << '\n';

    return true;
}

bool Server::bindSocket()
{
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6379);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;

    if (setsockopt(serverSocket,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   &opt,
                   sizeof(opt)) == -1)
    {
        cerr << "Failed to set socket options.\n";
        return false;
    }

    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == -1)
    {
        cerr << "Failed to bind socket.\n";
        return false;
    }

    cout << "Socket bound successfully to port 6379.\n";

    return true;
}

bool Server::listenForConnections()
{
    if (listen(serverSocket, BACKLOG) == -1)
    {
        cerr << "Failed to listen for connections.\n";
        return false;
    }

    cout << "Server is listening on port 6379.\n";

    return true;
}

int Server::acceptClient()
{
    cout << "Waiting for a client to connect...\n";

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket == -1)
    {
        cerr << "Failed to accept client.\n";
        return -1;
    }

    cout << "Client connected successfully!\n";
    cout << "Client Socket FD: " << clientSocket << '\n';

    return clientSocket;
}

std::string Server::receiveMessage(int clientSocket)
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

bool Server::sendMessage(
    int clientSocket,
    const std::string& message)
{
    ssize_t bytesSent =
        send(clientSocket,
             message.c_str(),
             message.size(),
             0);

    return bytesSent != -1;
}