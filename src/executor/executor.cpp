#include "executor.h"

Executor::Executor(Database &db)
    : database(db)
{
}

std::string Executor::execute(const Command &cmd)
{
    if (!cmd.valid)
    {
        return cmd.error;
    }

    if (cmd.command == "SET")
    {
        database.set(cmd.key, cmd.value);
        return "OK";
    }

    if (cmd.command == "GET")
    {
        return database.get(cmd.key);
    }

    if (cmd.command == "DEL")
    {
        return database.del(cmd.key) ? "1" : "0";
    }

    if (cmd.command == "EXISTS")
    {
        return database.exists(cmd.key) ? "1" : "0";
    }

    return "Unknown Command";
}