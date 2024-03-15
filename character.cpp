#pragma once
#include "headers.h"
using namespace std;

class LimitedStorage;

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

class Character
{
protected:
    string name;
    int age;
    string gender; // -male -female -other
    LimitedStorage backpack;
    Stat hp;
    Stat stamina;
    int firearmLevel;
    int meleeLevel;
    vector<Character *> currentWave;
    int coins;

public:
    // getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    int level() { return firearmLevel + meleeLevel + hp.level() + stamina.level(); }
    LimitedStorage getBackpack() const { return backpack; }
    vector<Character *> getWave() { return currentWave; }
    int getFirearmLevel() { return firearmLevel; }
    int getMeleeLevel() { return meleeLevel; }
    int getCoins() { return coins; }

    // setters
    void setName(const string &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGender(const string &newGender) { gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) { backpack = newBackpack; }
    void setWave(vector<Character *> newWave) { currentWave = newWave; }
    void setFirearmLevel(int newLevel) { firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) { meleeLevel = newLevel; }
    void setCoins(int newCoins) { coins = newCoins; }

    // others
    virtual void turn() {}
    virtual void death() {}
};

class Player : public Character
{
protected:
    Storage *inventory;

public:
    // getters
    Storage *getInventory() { return inventory; }
    // others
    virtual void turn() {}
    virtual void death() {}
};

class Enemy : public Character
{
public:
    virtual void turn() {}
    virtual void death() {}
};
class HumanEnemy : public Enemy
{
};
class ZombieEnemy : public Enemy
{
};
class SpecialZombie : public ZombieEnemy
{
};
