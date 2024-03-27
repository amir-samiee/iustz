#pragma once
#include "headers.h"

void Storage::addItem(string name)
{
    if (itemsMap.find(name) == itemsMap.end())
        throw invalid_argument("Invalid item name!");
    if (items.find(name) == items.end())
        items.insert({name, 1});

    else if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr)
        cout << "you can only add a permanent item once!\n";

    else
        items[name]++;
}

string Storage::getStorageData()
{
    stringstream result;
    int i = 1;
    int maxNameLength = 0;
    // Find the maximum length of names
    for (auto &item : items)
    {
        int length = itemsMap[item.first]->getName().length();
        if (length > maxNameLength)
            maxNameLength = length;
    }

    result << "No." << setw(maxNameLength + 5) << "Name" << setw(15) << "Effectivity" << setw(10) << "Stamina" << setw(10) << "Count\n";
    names.clear();
    for (auto &item : items)
    {
        names.push_back(item.first);
        result << i << "- " << setw(maxNameLength + 5) << item.first
               << setw(15) << itemsMap[item.first]->getSpecial()
               << setw(10) << itemsMap[item.first]->getStamina()
               << setw(10) << item.second << endl;
        i++;
    }
    return result.str();
}

void Storage::printStorage()
{
    cout << getStorageData();
}

void Storage::removeItem(string name)
{
    if (items[name] < 1)
        cout << "item does not exist.\n";

    else if (items[name] == 1)
        items.erase(name);

    else
        items[name]--;
}

LimitedStorage::LimitedStorage(int newSize)
{
    size = newSize;
}
// setters
void LimitedStorage::setSize(int newSize)
{
    if (newSize >= 0 && newSize <= capacity)
    {
        size = newSize;
    }
    else
    {
        cout << "Invalid size value. Size must be between 0 and " << capacity << endl;
    }
}
void LimitedStorage::addItem(string name)
{
    if (size < capacity)
    {
        if (items.find(name) == items.end())
        {
            items.insert({name, 1});
            size++;
        }

        else if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr)
            cout << "you can only add a permanent item once!\n";

        else
        {
            items[name]++;
            size++;
        }
    }
    else
        cout << "your backpack is already full\n";
}