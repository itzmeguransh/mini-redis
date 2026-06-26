int main()
{
    Server server;

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

        close(clientSocket);
    }
}