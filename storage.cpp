#pragma once
#include "headers.h"

Storage::Storage(Character *newOwner)
{
    owner = newOwner;
}
void Storage::addItem(string name)
{
    if (items.find(name) == items.end())
        items.insert({name, 1});

    else if (dynamic_cast<Permanent *>(dictionary[name]) != nullptr)
        cout << "you can only add a permanent item once!\n";

    else
        items[name]++;
}

void Storage::printStorage()
{
    int i = 1;
    int maxNameLength = 0;
    // Find the maximum length of names
    for (auto &item : items)
    {
        int length = dictionary[item.first]->getName().length();
        if (length > maxNameLength)
            maxNameLength = length;
    }

    cout << "No." << setw(maxNameLength + 5) << "Name" << setw(15) << "Effectivity" << setw(10) << "Stamina" << setw(10) << "Count\n";
    for (auto &item : items)
    {
        cout << i << "- " << setw(maxNameLength + 5) << dictionary[item.first]->getName()
             << setw(15) << dictionary[item.first]->getSpecial()
             << setw(10) << dictionary[item.first]->getStamina()
             << setw(10) << item.second << endl;
        i++;
    }
}

void Storage::removeItem(string name)
{
    while (true)
    {
        if (items[name] < 1)
            cout << "item does not exist.\n";

        else if (items[name] == 1)
        {
            items.erase(name);
            break;
        }

        else
        {
            items[name]--;
            break;
        }
    }
}

LimitedStorage::LimitedStorage(Character *newOwner, int newSize) : Storage(newOwner)
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

        else if (dynamic_cast<Permanent *>(dictionary[name]) != nullptr)
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