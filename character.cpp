#pragma once
#include "headers.h"

class Stat
{
protected:
    int maxPoint = 100;
    int currentPoint = maxPoint;

public:
    // getters:
    int getMaxPoint() const { return maxPoint; }
    int getCurrentPoint() const { return currentPoint; }

    // setters:
    void setMaxPoint(int newValue) { maxPoint = newValue; }
    void setCurrentPoint(int newValue)
    {
        if (newValue > maxPoint)
            currentPoint = maxPoint;
        else
            currentPoint = newValue;
    }

    int level()
    {
        return (((maxPoint - 100) / 30) + 1);
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
    LimitedStorage getBackpack() const { return backpack; }
    Stat getHp() const { return hp; }
    Stat getStamina() const { return stamina; }
    vector<Character *> getWave() const { return currentWave; }
    int getFirearmLevel() const { return firearmLevel; }
    int getMeleeLevel() const { return meleeLevel; }
    int getCoins() const { return coins; }

    // setters
    void setName(const string &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGender(const string &newGender) { gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) { backpack = newBackpack; }
    void setHp(Stat newHp) { hp = newHp; }
    void setStamina(Stat newStamina) { stamina = newStamina; }
    void setWave(vector<Character *> newWave) { currentWave = newWave; }
    void setFirearmLevel(int newLevel) { firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) { meleeLevel = newLevel; }
    void setCoins(int newCoins) { coins = newCoins; }

    // others
    int level() { return firearmLevel + meleeLevel + hp.level() + stamina.level(); }
    virtual void turn() = 0;
    virtual void die() = 0;
};

class Player : public Character
{
protected:
    Storage inventory;

public:
    // getters
    Storage getInventory() const { return inventory; }
    // others
    void turn() override {}
    void die() override {}
};

class Enemy : public Character
{
public:
    void turn() override {}
    void die() override {}
};
class HumanEnemy : public Enemy
{
};
class ZombieEnemy : public Enemy
{
};
class SpecialZombie : public ZombieEnemy
{
public:
    void turn() override {}
};
