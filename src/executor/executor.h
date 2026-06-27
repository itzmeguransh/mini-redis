#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../database/database.h"
#include "../parser/parser.h"
#include <string>

class Executor
{
private:
    Database &database;

public:
    Executor(Database &db);

    std::string execute(const Command &cmd);
};

#endif