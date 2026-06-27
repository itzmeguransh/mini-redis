#include "client.h"

#include <iostream>

int main()
{
    Client client;

    if (!client.createSocket())
        return 1;

    if (!client.connectToServer())
        return 1;

    std::string command;

    while (true)
    {
        std::cout << "mini-redis> ";

        std::getline(std::cin, command);

        if (command == "QUIT")
            break;

        if (command.empty())
            continue;

        if (!client.sendMessage(command))
        {
            std::cout << "Failed to send command.\n";
            break;
        }

        std::string response = client.receiveMessage();

        if (response.empty())
        {
            std::cout << "Server disconnected.\n";
            break;
        }

        std::cout << response << "\n";
    }

    client.disconnect();
}