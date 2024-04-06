#pragma once
#include "headers.h"

void Storage::setItems(map<string, int> newItems)
{
    clearStorage();
    addItem(newItems);
}

void Storage::clearStorage()
{
    removeItem(items);
}

void Storage::loadStorage(json data)
{
    setItems(data["items"]);
}

json Storage::dumpStorage()
{
    json data;
    data["items"] = items;
    return data;
}

void Storage::addItem(string name, bool isViewed)
{
    if (itemsMap.find(name) == itemsMap.end())
        throw invalid_argument("Invalid item name!");
    if (items.find(name) == items.end())
        items.insert({name, 1});

    else if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr && isViewed)
        cout << yellow << "you can only add a permanent item once!\n"
             << reset;

    else
        items[name]++;
}

void Storage::addItem(map<string, int> addingItems, bool isViewed)
{
    for (auto item : addingItems)
        for (int i = 0; i < item.second; i++)
            addItem(item.first, isViewed);
}

string Storage::getStorageData(string beforeNumber, string afterNumber, int leftMargin)
{
    if (items.empty())
        return "Storage is Empty!\n";
    stringstream result;
    int i = 1;
    int maxNameLength = 4;
    int maxTypeLength = 4;
    // Find the maximum length of names and types
    for (auto &item : items)
    {
        int nameLength = itemsMap[item.first]->getName().length();
        if (nameLength > maxNameLength)
            maxNameLength = nameLength;

        int typeLength = itemsMap[item.first]->getType().length();
        if (typeLength > maxTypeLength)
            maxTypeLength = typeLength;
    }
    if (leftMargin == -1)
        leftMargin = (beforeNumber + afterNumber).size() + 3;
    result << left << setw(leftMargin) << "No." << setw(maxNameLength + 5) << "Name"
           << setw(maxTypeLength + 2) << "Type" << right
           << setw(12) << "Effectivity"
           << setw(10) << "Stamina"
           << setw(10) << "Count" << endl;
    names.clear();
    for (auto &item : items)
    {
        string itemName = item.first;
        Item *itemPtr = itemsMap[itemName];
        names.push_back(itemName);
        result << left << setw(leftMargin) << beforeNumber + to_string(i) + afterNumber << setw(maxNameLength + 5) << itemName
               << setw(maxTypeLength + 2) << itemPtr->getType() << right
               << setw(9) << itemPtr->getSpecial() << string(3, ' ')
               << setw(8) << itemPtr->getStamina() << string(2, ' ')
               << setw(8) << item.second << endl;
        i++;
    }
    return result.str();
}

void Storage::printStorage(string beforeNumber, string afterNumber, int leftMargin)
{
    cout << getStorageData(beforeNumber, afterNumber, leftMargin);
}

void Storage::removeItem(string name, bool isViewd)
{
    if (items[name] < 1)
    {
        if (isViewd)
            cout << yellow << "item does not exist to remove!\n"
                 << reset;
    }

    else if (items[name] == 1)
        items.erase(name);

    else
        items[name]--;
}

void Storage::removeItem(map<string, int> removingItems, bool isViewd)
{
    for (auto item : removingItems)
        for (int i = 0; i < item.second; i++)
            removeItem(item.first, isViewd);
}

void LimitedStorage::setItems(map<string, int> newItems)
{
    if (mapSize(newItems) > capacity)
    {
        cout << yellow << "insufficient space!\n"
             << reset;
        return;
    }
    Storage::setItems(newItems);
}

void LimitedStorage::loadStorage(json data)
{
    Storage::loadStorage(data);
    capacity = data["capacity"];
}

json LimitedStorage::dumpStorage()
{
    json data = Storage::dumpStorage();
    data["capacity"] = capacity;
    return data;
}

void LimitedStorage::sortItems(vector<string> myItems)
{
    bool check = 1;
    while (check)
    {
        check = 0;
        for (int i = 0; i < myItems.size() - 1; ++i)
            if (itemsMap[myItems[i]]->getSpecial() > itemsMap[myItems[i + 1]]->getSpecial())
            {
                swap(myItems[i], myItems[i + 1]);
                check = 1;
            }
    }
}

void LimitedStorage::addItem(string name, bool isViewed)
{
    if (size < capacity)
    {
        if (items.find(name) == items.end())
        {
            items.insert({name, 1});
            if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr || dynamic_cast<Throwable *>(itemsMap[name]) != nullptr)
            {
                myWeapons.push_back(name);
                sortItems(myWeapons);
            }
            else if (dynamic_cast<HpPotion *>(itemsMap[name]) != nullptr)
            {
                myHpPotions.push_back(name);
                sortItems(myHpPotions);
            }
            else if (dynamic_cast<StaminaPotion *>(itemsMap[name]) != nullptr)
            {
                myStaminaPotions.push_back(name);
                sortItems(myStaminaPotions);
            }
            else
            {
                myPowerPotions.push_back(name);
                sortItems(myPowerPotions);
            }
            size++;
        }

        else if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr && isViewed)
            cout << yellow << "you can only add a permanent item once!\n"
                 << reset;

        else
        {
            items[name]++;
            size++;
        }
    }
    else if (isViewed)
        cout << yellow << "your backpack is already full!\n"
             << reset;
}

void LimitedStorage::addItem(map<string, int> addingItems, bool isViewed)
{
    if (mapSize(addingItems) > remainedSpace())
    {
        if (isViewed)
            cout << yellow << "insufficient space!\n"
                 << reset;
        return;
    }
    Storage::addItem(addingItems, isViewed);
}

void LimitedStorage::removeItem(string name, bool isViewd)
{
    if (items[name] > 0)
        size--;
    if (items[name] == 1)
    {
        if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr || dynamic_cast<Throwable *>(itemsMap[name]) != nullptr)
            myWeapons.erase(remove(myWeapons.begin(), myWeapons.end(), name), myWeapons.end());
        else if (dynamic_cast<HpPotion *>(itemsMap[name]) != nullptr)
            myHpPotions.erase(remove(myHpPotions.begin(), myHpPotions.end(), name), myHpPotions.end());
        else if (dynamic_cast<StaminaPotion *>(itemsMap[name]) != nullptr)
            myStaminaPotions.erase(remove(myStaminaPotions.begin(), myStaminaPotions.end(), name), myStaminaPotions.end());
        else
            myPowerPotions.erase(remove(myPowerPotions.begin(), myPowerPotions.end(), name), myPowerPotions.end());
    }
    Storage::removeItem(name, isViewd);
}