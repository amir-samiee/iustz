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
    virtual void setItems(map<string, int> newItems);

    // others
    virtual void addItem(string name);
    string getStorageData(string beforeNumber = "", string afterNumber = "- ", int leftMargin = -1);
    void printStorage(string beforeNumber = "", string afterNumber = "- ", int leftMargin = -1);
    virtual void removeItem(string name);
};

class LimitedStorage : public Storage
{
protected:
    vector<string> myWeapons;
    vector<string> myHpPotions;
    vector<string> myStaminaPotions;
    vector<string> myPowerPotions;
    int capacity = 12;
    int size = 0;

public:
    // getters
    int getCapacity() { return capacity; }
    int getSize() { return size; }
    vector<string> getPermanents() const { return myWeapons; }
    vector<string> getHpPotions() const { return myHpPotions; }
    vector<string> getStaminaPotions() const { return myStaminaPotions; }
    vector<string> getPowerPotions() const { return myPowerPotions; }

    // setters
    void setCapacity(int newCapacity) { capacity = newCapacity; }
    void setItems(map<string, int> newItems) override;
    
    // others
    static void sortItems(vector<string> items);
    void addItem(string name) override;
    void removeItem(string name) override;
    bool isFull() { return size == capacity; }
};