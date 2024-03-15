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
        if (items.find(name) == items.end())
            items.insert({name, 1});
        else
            items[name]++;
    }
    void printStorage()
    {
        int i = 1;
        for (auto item : items)
        {
            cout<<i<<"-"<<dictionary[item.first].getName()<<" "<<dictionary[item.first];
        }
    }
    void removeItem(string name)
    {
        while(true){
            if (items[name] < 1){
                cout<<"item does not exist.\n";
            }
            else if(items[name] == 1){
                items.erase(name);
                break;
            }

            else
                items[name]--;
        }
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