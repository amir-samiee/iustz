#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Character;

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
    int health;
    int energy;
    int level = 0;
    vector<Item> backpack;

public:
    // getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    int getHealth() const { return health; }
    int getEnergy() const { return energy; }
    int getLevel() const { return level; }
    vector<Item> getBackpack() const { return backpack; }

    // setters
    void setName(const string &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGender(const string &newGender) { gender = newGender; }
    void setHealth(int newHealth) { health = newHealth; }
    void setEnergy(int newEnergy) { energy = newEnergy; }
    void setLevel(int newLevel) { level = newLevel; }
    void setBackpack(const vector<Item> &newBackpack) { backpack = newBackpack; }
};

class Mission
{
};