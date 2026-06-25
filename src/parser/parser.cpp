#include "parser.h"

#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

Command Parser::parse(const string& input)
{
    Command result;

    result.valid = false;
    result.error = "";
    result.command = "";
    result.key = "";
    result.value = "";

    stringstream ss(input);
    vector<string> tokens;

    string word;

    while (ss >> word)
    {
        tokens.push_back(word);
    }
    if (tokens.empty())
    {
        result.error = "Empty command";
        return result;
    }
    string command = tokens[0];
    for (char& c : command)
    {
        c = toupper(static_cast<unsigned char>(c));
    }
    // SET

    if (command == "SET")
    {
        if (tokens.size() != 3)
        {
            result.error = "SET requires key and value";
            return result;
        }

        result.valid = true;
        result.command = "SET";
        result.key = tokens[1];
        result.value = tokens[2];

        return result;
    }
    // GET

    if (command == "GET")
    {
        if (tokens.size() != 2)
        {
            result.error = "GET requires a key";
            return result;
        }

        result.valid = true;
        result.command = "GET";
        result.key = tokens[1];

        return result;
    }

    // DEL
    if (command == "DEL")
    {
        if (tokens.size() != 2)
        {
            result.error = "DEL requires a key";
            return result;
        }

        result.valid = true;
        result.command = "DEL";
        result.key = tokens[1];

        return result;
    }

    // EXISTS
    if (command == "EXISTS")
    {
        if (tokens.size() != 2)
        {
            result.error = "EXISTS requires a key";
            return result;
        }

        result.valid = true;
        result.command = "EXISTS";
        result.key = tokens[1];

        return result;
    }

    // Unknown command
    result.error = "Unknown command";
    return result;
}