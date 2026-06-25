#include "database.h"
using namespace std;
bool Database::set(const string &key, const string &value)
{
    if (key.empty())
        return false;
    store[key] = value;
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
    auto it = store.find(key);
    if (it == store.end())
        return false;
    store.erase(key);
    return true;
}

bool Database::exists(const string &key)
{
    return store.find(key) != store.end();
}