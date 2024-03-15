#pragma once
#include "headers.h"

class Character;
class Storage
{
protected:
    map<string, int> items;
    Character *owner;

public:
    virtual void addItem(string name)
    {
    }
    void printStorage()
    {
    }
    void removeItem(string itemName)
    {
    }
};
class LimitedStorage : public Storage
{
protected:
    int number;

public:
    void addItem()
    {
    }
};