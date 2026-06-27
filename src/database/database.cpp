#include "database.h"
#include <fstream>
#include <sstream>
#include<iostream>
using namespace std;

Database::Database()
{
    loadFromDisk();
}
void Database::loadFromDisk()
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return;
    }

    std::string key, value;

    while (file >> key >> value)
    {
        store[key] = value;
    }

    file.close();
}
void Database::saveToDisk()
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open database file for writing.\n";
        return;
    }

    for (const auto &entry : store)
    {
        file << entry.first << " " << entry.second << "\n";
    }

    file.close();
}
bool Database::set(const string &key,
                   const string &value)
{
    std::lock_guard<std::mutex> lock(dbMutex);

    store[key] = value;

    saveToDisk();

    return true;
}

string Database::get(const string &key)
{
    auto it = store.find(key);
    if (it == store.end())
        return "NULL";
    return it->second;
}

bool Database::del(const string &key)
{
    std::lock_guard<std::mutex> lock(dbMutex);

    auto it = store.find(key);

    if (it == store.end())
        return false;

    store.erase(it);

    saveToDisk();

    return true;
}

bool Database::exists(const string &key)
{
    return store.find(key) != store.end();
}