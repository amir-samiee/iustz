#pragma once
#include "headers.h"

void Storage::addItem(string name)
{
    if (itemsMap.find(name) == itemsMap.end())
        throw invalid_argument("Invalid item name!");
    if (items.find(name) == items.end())
        items.insert({name, 1});

    else if (dynamic_cast<Permanent *>(itemsMap[name]) != nullptr)
        cout << yellow << "you can only add a permanent item once!\n"
             << reset;

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
        cout << yellow << "item does not exist to remove!\n"
             << reset;

    else if (items[name] == 1)
        items.erase(name);

    else
        items[name]--;
}

// setters
void LimitedStorage::setItems(map<string, int> newItems)
{
    int newSize = 0;
    for (auto i : newItems)
        newSize += i.second;
    if (newSize > capacity)
    {
        cout << yellow << "insufficient space!\n"
             << reset;
        return;
    }

    for (auto item : newItems)
        for (int i = 0; i < item.second; i++)
            addItem(item.first);
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
            cout << yellow << "you can only add a permanent item once!\n"
                 << reset;

        else
        {
            items[name]++;
            size++;
        }
    }
    else
        cout << yellow << "your backpack is already full!\n"
             << reset;
}

void LimitedStorage::removeItem(string name)
{
    if (items[name] > 0)
        size--;
    Storage::removeItem(name);
}