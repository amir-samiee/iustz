#pragma once
#include "headers.h"

class Factory
{
protected:
    int level;
    int casualEnemy;
    bool specialEnemy;
    Storage *inventory;
    int **waveInfo;

public:
    // constructor:
    Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory);
    Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo);

    // getters:
    int getLevel() const { return level; }
    int getCasualEnemy() const { return casualEnemy; }
    bool getSpecialEnemy() const { return specialEnemy; }
    Storage *getInventory() const { return inventory; }

    // seters:
    void setLevel(int newLevel) { level = newLevel; }
    void setCasualEnemy(int newCasualEnemy) { casualEnemy = newCasualEnemy; }
    void setSpecialEnemy(bool newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setInventory(Storage *newInventory) { inventory = newInventory; }

    // methodes:
    vector<int> getWave();
    virtual vector<vector<Character *>> createEnemy() = 0;
};

class ZombieFactory : public Factory
{
public:
    ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory);
    ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo);
    vector<vector<Character *>> createEnemy() override;
};

class HumanFactory : public Factory
{
public:
    HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory);
    HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo);
    vector<vector<Character *>> createEnemy() override;
};

/// @brief ///////////////////////////////////////////////

class Mission
{

protected:
    string name;
    int missionNum;
    int casualEnemyNum;
    bool specialEnemy;
    Storage *inventory;
    vector<vector<Character *>> enemies;

public:
    // constructors:
    Mission(string newName, int newMissionNum, bool specialEnemy);
    Mission(string newName, int newMissionNum, int newCasualEnemyNum, bool specialEnemy, Storage *newInventory);

    // getters:
    string getName() const { return name; }
    int getMissionNum() const { return missionNum; }
    int getCasualEnemyNum() const { return casualEnemyNum; }
    bool getSpecialEnemy() const { return specialEnemy; }
    Storage *getInventory() const { return inventory; }

    // setters :
    void setName(const string &newName) { name = newName; }
    void setMissionNum(const int &newMissionNum) { missionNum = newMissionNum; }
    void setCasualEnemyNum(int newCasualEnemyNum) { casualEnemyNum = newCasualEnemyNum; }
    void setSpecialEnemyNum(bool newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setInventory(Storage *newInventory) { inventory = newInventory; }

    // methods:
    // virtual void initInventory();
    void addPotion(vector<Item*> addingItem);
    void story();
    void playerTurn();
    void enemyTurn();
    void endWave();
    void removeDead();
    void playerDeath();
    void end();
    void start();
};

class ZombieMission : public Mission
{
public:
    // constructors:
    ZombieMission(string newName, int newMissionNum, bool newSpecialEnemy);
    ZombieMission(string newName, int newMissionNum, int newCasualEnemyNum,
                  bool newSpecialEnemy, Storage *newInventory, int **waveInfo);

    // methodes:
    void initInventory();
};

class HumanMission : public Mission
{
public:
    // constructor:
    HumanMission(string newName, int newMissionNum, bool newSpecialEnemy);
    HumanMission(string newName, int newMissionNum, int newCasualEnemyNum,
                 bool newSpecialEnemy, Storage *newInventory, int **waveInfo);

    // methodes:
    void initInventory();
};

// a map for connecting missioins to their id:
map<string, Mission *> missionMap;

// vectors for saving missions:
vector<ZombieMission *> zombieMissions;
vector<HumanMission *> humanMissions;