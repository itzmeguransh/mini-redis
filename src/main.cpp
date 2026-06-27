#include "server/server.h"
#include "parser/parser.h"
#include "database/database.h"

#include <iostream>
#include <thread>
#include <functional>
#include <unistd.h>

void handleClient(Server &server,
                  Database &database,
                  Parser &parser,
                  int clientSocket)
{
    while (true)
    {
        std::string message = server.receiveMessage(clientSocket);

        if (message.empty())
            break;

        Command cmd = parser.parse(message);

        std::string response;

      if (!cmd.valid)
      {
          response = cmd.error;
      }
      else if (cmd.command == "SET")
      {
          database.set(cmd.key, cmd.value);
          response = "OK";
      }
      else if (cmd.command == "GET")
      {
          response = database.get(cmd.key);
      }
      else if (cmd.command == "DEL")
      {
          response = database.del(cmd.key) ? "1" : "0";
      }
      else if (cmd.command == "EXISTS")
      {
          response = database.exists(cmd.key) ? "1" : "0";
      }
      else
      {
          response = "Unknown Command";
      }

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
            std::ref(database),
            std::ref(parser),
            clientSocket
        ).detach();
    }

    return 0;
}