#include <iostream>
#include "../src/parser/parser.h"

int main()
{
    Parser parser;

    Command cmd = parser.parse("set name Guransh");

    std::cout << std::boolalpha;

    std::cout << "Valid: " << cmd.valid << '\n';
    std::cout << "Command: " << cmd.command << '\n';
    std::cout << "Key: " << cmd.key << '\n';
    std::cout << "Value: " << cmd.value << '\n';
    std::cout << "Error: " << cmd.error << '\n';

    return 0;
}