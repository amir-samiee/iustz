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

    // setters
    void setItems(map<string, int> newItems) { items = newItems; }

    // others
    virtual void addItem(string name);

    void printStorage();

    void removeItem(string name);
};

class LimitedStorage : public Storage
{
protected:
    int capacity = 12;
    int size = 0;

public:
    // constructor
    LimitedStorage() = default;
    LimitedStorage(int newSize);
    // getters
    int getSize() { return size; }
    // setters
    void setSize(int newSize);
    // others
    void addItem(string name) override;
};