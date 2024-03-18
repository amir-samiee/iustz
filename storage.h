#pragma once
#include "headers.h"

class Character;
class Storage
{
protected:
    map<string, int> items;
    Character *owner;

public:
    // constructor
    Storage(Character *newOwner);
    
    // getters
    map<string, int> getItems() { return items; }
    Character *getOwner() { return owner; }

    // setters
    void setItems(map<string, int> newItems) { items = newItems; }
    void setOwner(Character *newOwner) { owner = newOwner; }

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
    LimitedStorage() ;
    LimitedStorage(Character *newOwner, int newSize);
    // getters
    int getSize() { return size; }
    // setters
    void setSize(int newSize);
    // others
    void addItem(string name) override;
};