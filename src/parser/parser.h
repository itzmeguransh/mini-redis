#ifndef PARSER_H
#define PARSER_H
using namespace std;
#include <string>
struct Command
{
    bool valid;
    string error;
    string command;
    string key;
    string value;
};

class Parser
{
public:
    Command parse(const string& input);
};

#endif