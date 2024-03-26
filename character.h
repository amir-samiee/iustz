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
    bool isAlive = 1;
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
    Character(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina,
              int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
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
    bool getAlive() const { return isAlive; }

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
    void setALive(bool newIsAlive) { isAlive = newIsAlive; }

    // others
    int level();
    virtual void turn() = 0;
    virtual void die() = 0;
    void takeDamage(int newPoint);
};

class Player : public Character
{
protected:
    Storage inventory;
    int humanLevels = 0;
    int zombieLevels = 0;

public:
    Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave,
           int coins, Storage inventory, int humanLevels, int zombieLevels);

    // getters
    Storage *getInventory() { return &inventory; }

    // setters
    void setInventory(Storage newInventory) { inventory = newInventory; }

    // others
    void turn() override;
    void die() override;
};

Player *player1 = new Player("default name", 18, "default gender", LimitedStorage(12), Stat(), Stat(), 1, 1, 1, vector<Character *>(), 0, Storage(), 0, 0);

class Enemy : public Character
{
public:
    Enemy(string name, int age, string gender, LimitedStorage backpack,
          Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
    void turn() override;
    void die() override;
};

class HumanEnemy : public Enemy
{
public:
    HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
               Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
};

class ZombieEnemy : public Enemy
{
public:
    ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
};

class SpecialZombie : public ZombieEnemy
{
public:
    SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                  Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);

    void turn() override;
};
