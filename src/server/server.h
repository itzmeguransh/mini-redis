#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server
{
private:
    int serverSocket;

public:
    Server();

    bool createSocket();
    bool bindSocket();
    bool listenForConnections();

    int acceptClient();

    // ADD THESE
    std::string receiveMessage(int clientSocket);
    bool sendMessage(int clientSocket, const std::string& message);
};

#endif