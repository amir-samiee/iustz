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
    virtual void setFirearmLevel(int newLevel) = 0;
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
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getGender() const override { return gender; }
    LimitedStorage *getBackpack() override { return &backpack; }
    Stat *getHp() override { return &hp; }
    Stat *getStamina() override { return &stamina; }
    vector<Character *> getWave() const override { return currentWave; }
    int getFirearmLevel() const override { return firearmLevel; }
    int getMeleeLevel() const override { return meleeLevel; }
    int getPowerBoost() const override { return powerBoost; }
    int getCoins() const override { return coins; }
    Storage *getInventory() { return &inventory; }

    // setters
    void setName(const string newName) override { name = newName; }
    void setAge(int newAge) override { age = newAge; }
    void setGender(const string newGender) override { gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) override { backpack = newBackpack; }
    void setHp(Stat newHp) override { hp = newHp; }
    void setStamina(Stat newStamina) override { stamina = newStamina; }
    void setWave(vector<Character *> newWave) override { currentWave = newWave; }
    void setFirearmLevel(int newLevel) override { firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) override { meleeLevel = newLevel; }
    void setPowerBoost(int newPowerBoost) override { powerBoost = newPowerBoost; }
    void setCoins(int newCoins) override { coins = newCoins; }
    void setInventory(Storage newInventory) { inventory = newInventory; }

    // others
    int level() override;
    void turn() override;
    void die() override;
    void takeDamage(int newPoint) override;
};

Player *player1 = new Player("default name", 18, "default gender", LimitedStorage(12), Stat(), Stat(), 1, 1, 1, vector<Character *>(), 0, Storage(), 0, 0);

// Enemies

namespace MVC
{
    class EnemyModel
    {
    public:
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

        EnemyModel(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                   int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);
    };

    class EnemyView
    {
    };

    class EnemyController
    {
    private:
        EnemyModel &model;
        EnemyView &view;

    public:
        EnemyController(EnemyModel &model, EnemyView &view) : model(model), view(view) {}
        void takeDamage(int damage);
        void die();
    };

}

class Enemy : public Character
{

private:
    MVC::EnemyModel model;
    MVC::EnemyView view;
    MVC::EnemyController controller;

public:
    Enemy(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
          int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins);

    // getters
    string getName() const override { return model.name; };
    int getAge() const override { return model.age; };
    string getGender() const override { return model.gender; };
    LimitedStorage *getBackpack() override { return &model.backpack; };
    Stat *getHp() override { return &model.hp; };
    Stat *getStamina() override { return &model.stamina; };
    int getFirearmLevel() const override { return model.firearmLevel; };
    int getMeleeLevel() const override { return model.meleeLevel; };
    int getPowerBoost() const override { return model.powerBoost; };
    int getCoins() const override { return model.coins; };
    vector<Character *> getWave() const override { return model.currentWave; };

    // setters
    void setName(const string newName) override { model.name = newName; }
    void setAge(int newAge) override { model.age = newAge; }
    void setGender(const string newGender) override { model.gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) override { model.backpack = newBackpack; }
    void setHp(Stat newHp) override { model.hp = newHp; }
    void setStamina(Stat newStamina) override { model.stamina = newStamina; }
    void setWave(vector<Character *> newWave) override { model.currentWave = newWave; }
    void setFirearmLevel(int newLevel) override { model.firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) override { model.meleeLevel = newLevel; }
    void setPowerBoost(int newPowerBoost) override { model.powerBoost = newPowerBoost; }
    void setCoins(int newCoins) override { model.coins = newCoins; }

    // others
    int level() override;
    void takeDamage(int damage) override;
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
