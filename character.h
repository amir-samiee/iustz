#pragma once
#include "headers.h"

class Stat
{
protected:
    int basePoint = 100;
    int maxPoint = basePoint;
    int currentPoint = maxPoint;
    int lastSavedPoint = 0;

public:
    // constructors:
    Stat() = default;
    Stat(int basePoint) : basePoint(basePoint) {}
    Stat(int basePoint , int lvl);

    // getters:
    int getMaxPoint() const { return maxPoint; }
    int getCurrentPoint() const { return currentPoint; }

    // setters:
    void setMaxPoint(int newValue) { maxPoint = newValue; }
    void setCurrentPoint(int newValue);

    // other
    void loadStat(json data);
    json dumpStat();
    void savePoint();
    void loadPoint();
    void fill();
    int level();
};

class Character
{
public:
    // getters
    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getGender() const = 0;
    virtual LimitedStorage *getBackpack() = 0;
    virtual Stat *getHp() = 0;
    virtual Stat *getStamina() = 0;
    virtual vector<Character *> getWave() const = 0;
    virtual Character *currentEnemy(bool isViewd = 0) = 0;
    virtual int getFirearmLevel() const = 0;
    virtual int getMeleeLevel() const = 0;
    virtual double getPowerBoost() const = 0;
    virtual int getCoins() const = 0;

    // setters
    virtual void setName(const string newName) = 0;
    virtual void setAge(int newAge) = 0;
    virtual void setGender(const string newGender) = 0;
    virtual void setBackpack(LimitedStorage newBackpack) = 0;
    virtual void setHp(Stat newHp) = 0;
    virtual void setStamina(Stat newStamina) = 0;
    virtual void setWave(vector<Character *> newWave) = 0;
    virtual void setFirearmLevel(int newLevel) = 0;
    virtual void setMeleeLevel(int newLevel) = 0;
    virtual void setPowerBoost(double newPowerBoost) = 0;
    virtual void setCoins(int newCoins) = 0;

    // others
    virtual bool isAlive() = 0;
    virtual int level() = 0;
    virtual bool move() = 0;
    virtual void die() = 0;
    virtual void takeDamage(int takenDamage) = 0;
    virtual void display(bool isFighting = 0) = 0;
};

class Player : public Character
{
protected:
    string username;
    string name;
    int age;
    string gender; // -male -female -other
    LimitedStorage backpack;
    Stat hp;
    Stat stamina;
    int firearmLevel = 1;
    int meleeLevel = 1;
    double powerBoost = 1;
    int coins;
    vector<Character *> currentWave;
    Storage rewardItems;
    int rewardCoins = 0;
    Storage inventory;
    int humanLevels = 0;
    int zombieLevels = 0;

public:
    Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave,
           int coins, Storage inventory, int humanLevels, int zombieLevels);
    Player(const Player &other);

    // getters
    string getUsername() { return username; }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getGender() const override { return gender; }
    LimitedStorage *getBackpack() override { return &backpack; }
    Stat *getHp() override { return &hp; }
    Stat *getStamina() override { return &stamina; }
    int getFirearmLevel() const override { return firearmLevel; }
    int getMeleeLevel() const override { return meleeLevel; }
    double getPowerBoost() const override { return powerBoost; }
    int getCoins() const override { return coins; }
    vector<Character *> getWave() const override { return currentWave; }
    Character *currentEnemy(bool isViewd = 0) override;
    Storage *getInventory() { return &inventory; }
    int getHumanLevels() { return humanLevels; }
    int getZombieLevels() { return zombieLevels; }
    Storage *getRewardItems() { return &rewardItems; }
    int getRewardCoins() { return rewardCoins; }

    // setters
    void setUsername(string newUsername) { username = newUsername; }
    void setName(string newName) override { name = newName; }
    void setAge(int newAge) override { age = newAge; }
    void setGender(string newGender) override { gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) override { backpack = newBackpack; }
    void setHp(Stat newHp) override { hp = newHp; }
    void setStamina(Stat newStamina) override { stamina = newStamina; }
    void setFirearmLevel(int newLevel) override { firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) override { meleeLevel = newLevel; }
    void setPowerBoost(double newPowerBoost) override { powerBoost = newPowerBoost; }
    void setCoins(int newCoins) override { coins = newCoins; }
    void setWave(vector<Character *> newWave) override { currentWave = newWave; }
    void setInventory(Storage newInventory) { inventory = newInventory; }
    void setHumanLevels(int newLevel) { humanLevels = newLevel; }
    void setZombieLevels(int newLevel) { zombieLevels = newLevel; }
    void setRewardItems(Storage newReward) { rewardItems = newReward; }
    void setRewardCoins(int newReward) { rewardCoins = newReward; }

    // others
    bool isAlive() override;
    int level() override;
    bool move() override;
    void die() override;
    void takeDamage(int takenDamage) override;
    void display(bool isFighing = 0) override;
    void addRewardCoins(int addedCoins);
    void loadPlayer(json data);
    json dumpPlayer();
};

Player defaultPlayer("default name", 18, "default gender",
                     LimitedStorage({{"Grenade", 1}, {"Knife", 1}, {"FirstAid Kits", 1}, {"Vigor Rush", 1}, {"Savage Serum", 1}}),
                     Stat(300), Stat(300), 1, 1, 1, vector<Character *>(), 50, Storage(), 0, 0);
Player *player1 = new Player(defaultPlayer);

// Enemies
class Enemy;
class FSM;
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
        double powerBoost = 1;
        int coins;
        string currentMission;
        vector<Character *> currentWave;

        EnemyModel(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                   int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins);
        bool isAlive();
    };

    class EnemyView
    {
    public:
        void display(const EnemyModel &model, bool isFighring = 0);
    };

    class EnemyController
    {
    protected:
        EnemyModel *model;
        EnemyView *view;
        Enemy *self;

    public:
        EnemyController(EnemyModel *model, EnemyView *view, Enemy *self);
        virtual void takeDamage(int takenDamage);
        void die();
        bool move();
    };

    class SpecialEnemyController : public EnemyController
    {
    public:
        // constructor:
        SpecialEnemyController(EnemyModel *model, EnemyView *view, Enemy *self)
            : EnemyController(model, view, self) {}

        // methodes:
        void takeDamage(int takenDamage) override;
    };
}

class Enemy : public Character
{
protected:
    MVC::EnemyModel *model;
    MVC::EnemyView *view;
    MVC::EnemyController *controller;

public:
    Enemy(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
          int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins);
    ~Enemy();

    // getters
    string getName() const override { return model->name; };
    int getAge() const override { return model->age; };
    string getGender() const override { return model->gender; };
    LimitedStorage *getBackpack() override { return &model->backpack; };
    Stat *getHp() override { return &model->hp; };
    Stat *getStamina() override { return &model->stamina; };
    int getFirearmLevel() const override { return model->firearmLevel; };
    int getMeleeLevel() const override { return model->meleeLevel; };
    virtual double getPowerBoost() const override { return model->powerBoost; };
    int getCoins() const override { return model->coins; };
    vector<Character *> getWave() const override { return model->currentWave; };
    Character *currentEnemy(bool isViewd = 0) override;

    // setters
    void setName(const string newName) override { model->name = newName; }
    void setAge(int newAge) override { model->age = newAge; }
    void setGender(const string newGender) override { model->gender = newGender; }
    void setBackpack(LimitedStorage newBackpack) override { model->backpack = newBackpack; }
    void setHp(Stat newHp) override { model->hp = newHp; }
    void setStamina(Stat newStamina) override { model->stamina = newStamina; }
    void setWave(vector<Character *> newWave) override { model->currentWave = newWave; }
    void setFirearmLevel(int newLevel) override { model->firearmLevel = newLevel; }
    void setMeleeLevel(int newLevel) override { model->meleeLevel = newLevel; }
    void setPowerBoost(double newPowerBoost) override { model->powerBoost = newPowerBoost; }
    void setCoins(int newCoins) override { model->coins = newCoins; }

    // others
    bool isAlive() override;
    int level() override;
    virtual void takeDamage(int takenDamage) override;
    bool move() override;
    void die() override;
    void display(bool isFighting = 0) override;
};

class HumanEnemy : public Enemy
{
public:
    HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
               Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins);
};

class ZombieEnemy : public Enemy
{
public:
    ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins);
    virtual void takeDamage(int takenDamage);
    virtual double getPowerBoost() const override { return model->powerBoost; };
};

class SpecialZombie : public ZombieEnemy
{
public:
    SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                  Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins);
    double getPowerBoost() const override;
    void takeDamage(int takenDamage) override;
};

vector<Character *> characterLeakHandle;