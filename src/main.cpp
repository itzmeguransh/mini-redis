#include "server/server.h"
#include "parser/parser.h"
#include "database/database.h"
#include "executor/executor.h"

#include <iostream>
#include <thread>
#include <functional>
#include <unistd.h>

void handleClient(Server &server,
                  Parser &parser,
                  Executor &executor,
                  int clientSocket)
{
    while (true)
    {
        std::string message = server.receiveMessage(clientSocket);

        if (message.empty())
            break;

        Command cmd = parser.parse(message);

        std::string response = executor.execute(cmd);

        server.sendMessage(clientSocket, response);
    }

    close(clientSocket);

    std::cout << "Client disconnected.\n";
}

int main()
{
    Server server;
    Parser parser;
    Database database;
    Executor executor(database);

    if (!server.createSocket())
        return 1;

    if (!server.bindSocket())
        return 1;

    if (!server.listenForConnections())
        return 1;

    while (true)
    {
        int clientSocket = server.acceptClient();

        if (clientSocket == -1)
            continue;

        std::thread(
            handleClient,
            std::ref(server),
            std::ref(parser),
            std::ref(executor),
            clientSocket)
            .detach();
    }

    return 0;
}