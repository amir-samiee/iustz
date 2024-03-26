#pragma once
#include "headers.h"

class Stat
{
protected:
    int maxPoint = 100;
    int currentPoint = maxPoint;

public:
    Stat() = default;
    // getters:
    int getMaxPoint() const { return maxPoint; }
    int getCurrentPoint() const { return currentPoint; }

    // setters:
    void setMaxPoint(int newValue) { maxPoint = newValue; }
    void setCurrentPoint(int newValue);

    int level();
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
    int firearmLevel = 1;
    int meleeLevel = 1;
    int powerBoost = 1;
    int coins;
    string currentMission;
    vector<Character *> currentWave;

public:
    // getters
    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getGender() const = 0;
    virtual LimitedStorage *getBackpack() = 0;
    virtual Stat *getHp() = 0;
    virtual Stat *getStamina() = 0;
    virtual vector<Character *> getWave() const = 0;
    virtual int getFirearmLevel() const = 0;
    virtual int getMeleeLevel() const = 0;
    virtual int getPowerBoost() const = 0;
    virtual int getCoins() const = 0;

    // setters
    virtual void setName(const string newName) = 0;
    virtual void setAge(int newAge) { age = newAge; }
    virtual void setGender(const string newGender) = 0;
    virtual void setBackpack(LimitedStorage newBackpack) = 0;
    virtual void setHp(Stat newHp) { hp = newHp; }
    virtual void setStamina(Stat newStamina) = 0;
    virtual void setWave(vector<Character *> newWave) = 0;
    virtual void setMeleeLevel(int newLevel) = 0;
    virtual void setPowerBoost(int newPowerBoost) = 0;
    virtual void setCoins(int newCoins) = 0;

    // others
    virtual int level() = 0;
    virtual void turn() = 0;
    virtual void die() = 0;
    virtual void takeDamage(int newPoint) = 0;
};

class Player : public Character
{
protected:
    string name;
    int age;
    string gender; // -male -female -other
    LimitedStorage backpack;
    Stat hp;
    Stat stamina;
    int firearmLevel = 1;
    int meleeLevel = 1;
    int powerBoost = 1;
    int coins;
    string currentMission;
    vector<Character *> currentWave;

    Storage inventory;
    int humanLevels = 0;
    int zombieLevels = 0;

public:
    Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave,
           int coins, Storage inventory, int humanLevels, int zombieLevels);

    // getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    LimitedStorage *getBackpack() { return &backpack; }
    Stat *getHp() { return &hp; }
    Stat *getStamina() { return &stamina; }
    vector<Character *> getWave() const { return currentWave; }
    int getFirearmLevel() const { return firearmLevel; }
    int getMeleeLevel() const { return meleeLevel; }
    int getPowerBoost() const { return powerBoost; }
    int getCoins() const { return coins; }
    Storage *getInventory() { return &inventory; }

    // setters
    void setName(const string newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setGender(const string newGender) { gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) { backpack = newBackpack; }
    void setHp(Stat newHp) { hp = newHp; }
    void setStamina(Stat newStamina) { stamina = newStamina; }
    void setWave(vector<Character *> newWave) { currentWave = newWave; }
    void setFirearmLevel(int newLevel) { firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) { meleeLevel = newLevel; }
    void setPowerBoost(int newPowerBoost) { powerBoost = newPowerBoost; }
    void setCoins(int newCoins) { coins = newCoins; }
    void setInventory(Storage newInventory) { inventory = newInventory; }

    // others
    int level();
    void turn() override;
    void die() override;
    void takeDamage(int newPoint);
};

Player *player1 = new Player("default name", 18, "default gender", LimitedStorage(12), Stat(), Stat(), 1, 1, 1, vector<Character *>(), 0, Storage(), 0, 0);

class Enemy : public Character
{
public:
    // Enemy(string name, int age, string gender, LimitedStorage backpack,
    //       Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
    void turn() override;
    void die() override;
};

class HumanEnemy : public Enemy
{
public:
    // HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
    //            Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
};

class ZombieEnemy : public Enemy
{
public:
    // ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
    //             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
};

class SpecialZombie : public ZombieEnemy
{
public:
    // SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
    //               Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);

    void turn() override;
};
