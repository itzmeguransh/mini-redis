#ifndef DATABASE_H
#define DATABASE_H
#include <mutex>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

class Database
{
private:
    unordered_map<string, string> store;
    std::mutex dbMutex;

    const std::string filename = "database.txt";

    void loadFromDisk();
    void saveToDisk();

public:
    Database();

    bool set(const string &key, const string &value);
    string get(const string &key);
    bool del(const string &key);
    bool exists(const string &key);
};

#endif