#pragma once
#include "headers.h"

class Character;
class Storage
{
protected:
    map<string, int> items = {};
    vector<string> names;

public:
    // constructor
    Storage() = default;

    // getters
    map<string, int> getItems() { return items; }
    vector<string> getNames() { return names; }

    // setters
    virtual void setItems(map<string, int> newItems) { items = newItems; }

    // others
    virtual void addItem(string name);
    string getStorageData();
    void printStorage();

    virtual void removeItem(string name);
};

class LimitedStorage : public Storage
{
protected:
    int capacity = 12;
    int size = 0;

public:
    // getters
    int getCapacity() { return capacity; }
    int getSize() { return size; }
    // setters
    void setCapacity(int newCapacity) { capacity = newCapacity; }
    void setItems(map<string, int> newItems) override;
    // others
    void addItem(string name) override;
    void removeItem(string name) override;
};