#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
using namespace std;

class Database
{
private:
    unordered_map<string, string> store;

public:
    bool set(const string &key, const string &value);
    string get(const string &key);
    bool del(const string &key);
    bool exists(const string &key);
};

#endif