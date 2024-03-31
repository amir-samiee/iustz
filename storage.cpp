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

void LimitedStorage::addItem(string name)
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
    Storage::removeItem(name);
}