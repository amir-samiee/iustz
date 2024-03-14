#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Character;
class Storage
{
protected:
    map<string, int> items;
    Character *owner;

public:
    virtual void addItem(string name)
    {
    }
    void printStorage()
    {
    }
    void removeItem(string)
    {
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

class Stat
{
protected:
    int maxPoint = 100;
    int currentPoint = maxPoint;

public:
    // getters:
    int getMaxPoint() const
    {
        return maxPoint;
    }
    int getCurrentPoint() const
    {
        return currentPoint;
    }
    int level()
    {
        return (((maxPoint - 100) / 30) + 1);
    }

    // setters:
    void setMaxPoint(int newValue)
    {
        maxPoint = newValue;
    }
    void setCurrentPoint(int newValue)
    {
        currentPoint = newValue;
    }
};

class Item // passive, consumable and throwable items + skills
{
protected:
    Character *owner = nullptr;

public:
    virtual void useItem();
};

class Character
{
protected:
    string name;
    int age;
    string gender; // -male -female -other
    LimitedStorage backpack;
    Stat hp;
    Stat stamina;
    int fireArmLevel;
    int meleeLevel;
    vector<Character *> currentWave;
    int coins;

public:
    // getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    int level() { return fireArmLevel + meleeLevel + hp.level() + stamina.level(); }
    LimitedStorage getBackpack() const { return backpack; }
    vector<Character*> getWave() { return currentWave; }
    // setters
    void setName(const string &newName)
    {
        name = newName;
    }
    void setAge(int newAge)
    {
        age = newAge;
    }
    void setGender(const string &newGender)
    {
        gender = newGender;
    }
};

class Mission
{
};