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
    Storage(map<string, int> items) : items(items) {}

    // getters
    map<string, int> getItems() { return items; }
    vector<string> getNames() { return names; }

    // setters
    virtual void setItems(map<string, int> newItems);

    // others
    void clearStorage();
    virtual void loadStorage(json data);
    virtual json dumpStorage();
    virtual void addItem(string name, bool isViewed = false);
    virtual void addItem(map<string, int> addingItems, bool isViewed = false);
    string getStorageData(string beforeNumber = "", string afterNumber = "- ", int leftMargin = -1);
    void printStorage(string beforeNumber = "", string afterNumber = "- ", int leftMargin = -1);
    virtual void removeItem(string name, bool isViewd = 1);
    void removeItem(map<string, int> items, bool isViewd = 1);
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
    static void sortItems(vector<string> items);

public:
    // getters
    int getCapacity() { return capacity; }
    int getSize() { return size; }
    vector<string> getWeapons() const { return myWeapons; }
    vector<string> getHpPotions() const { return myHpPotions; }
    vector<string> getStaminaPotions() const { return myStaminaPotions; }
    vector<string> getPowerPotions() const { return myPowerPotions; }

    // setters
    void setCapacity(int newCapacity) { capacity = newCapacity; }
    void setItems(map<string, int> newItems) override;

    // others
    void loadStorage(json data) override;
    json dumpStorage();
    void addItem(string name, bool isViewed = false) override;
    void addItem(map<string, int> addingItems, bool isViewed = false) override;
    void removeItem(string name, bool isViewd = 1) override;
    inline int remainedSpace() { return capacity - size; }
    inline bool isFull() { return remainedSpace() == 0; }
};

vector<Storage *> storageLeakHandle;