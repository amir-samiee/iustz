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
    Storage(Character *newOwner)
    {
        owner = newOwner;
    }
    // getters
    Character *getOwner()
    {
        return owner;
    }

    // setters
    void setOwner(Character *newOwner)
    {
        owner = newOwner;
    }

    // others
    virtual void addItem(string name)
    {
        if (items.find(name) == items.end())
            items.insert({name, 1});

        else if (dynamic_cast<Permanent *>(dictionary[name]) != nullptr)
            cout << "you can only add a permanent item once!\n";

        else
            items[name]++;
    }

    void printStorage()
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

    void removeItem(string name)
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
};

class LimitedStorage : public Storage
{
protected:
    const int capacity = 12;
    int size = 0;

public:
    //constructor
    LimitedStorage(Character* newOwner , int newSize) : Storage(newOwner){
        size = newSize;
    }
    // getters
    int getSize()
    {
        return size;
    }
    // setters
    void setSize(int newSize)
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
    // others
    void addItem(string name) override
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
};