#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
private:
    int clientSocket;

public:
    Client();

    bool createSocket();
    bool connectToServer();

    bool sendMessage(const std::string& message);

    std::string receiveMessage();

    void disconnect();
};

#endif