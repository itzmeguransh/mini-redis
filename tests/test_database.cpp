#include <iostream>
#include "../src/database/database.h"

int main()
{
    Database db;

    db.set("name", "Guransh");

    std::cout << db.exists("name") << std::endl;

    db.del("name");

    std::cout << db.exists("name") << std::endl;
}