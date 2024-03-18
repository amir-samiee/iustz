#pragma once
#include "headers.h"

class Factory
{
protected:
    int level;
    int casualEnemy;
    int specialEnemy;
    Storage *inventory;

public:
    // constructor:
    Factory(int level, int casualEnemy, int specialEnemy, Storage *inventory);

    // getters:
    int getLevel() const { return level; }
    int getCasualEnemy() const { return casualEnemy; }
    int getSpecialEnemy() const { return specialEnemy; }
    Storage *getInventory() const { return inventory; }

    // seters:
    void setLevel(int newLevel) { level = newLevel; }
    void setCasualEnemy(int newCasualEnemy) { casualEnemy = newCasualEnemy; }
    void setSpecialEnemy(int newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setInventory(Storage *newInventory) { inventory = newInventory; }
    void setFactory(int newLevel, int newCasualEnemy, int newSpecialEnemy, Storage *newInventory);

    // methodes:
    vector<int> getWave();
    virtual vector<vector<Character *>> createEnemy() = 0;
};

class ZombieFactory : public Factory
{
public:
    vector<vector<Character *>> createEnemy() override;
};

class HumanFactory : public Factory
{
public:
    vector<vector<Character *>> createEnemy() override;
};

/// @brief ///////////////////////////////////////////////
class Mission;

//a map for conecting missioins to their id:
map<string, Mission *> missionsID;

class Mission
{

protected:
    string name;
    int missionNum;
    int casualEnemyNum;
    int specialEnemyNum;
    Storage *inventory;
    vector<vector<Character *>> enemies;

public:
    // constructor:
    Mission(string newName, int newMissionNum, int newCasualEnemyNum, int newSpecialEnemyNum, Storage *newInventory);

    // getters:
    string getName() const { return name; }
    int getMissionNum() const { return missionNum; }
    int getCasualEnemyNum() const { return casualEnemyNum; }
    int getSpecialEnemyNum() const { return specialEnemyNum; }
    Storage *getInventory() const { return inventory; }

    // setters :
    void setName(const string &newName) { name = newName; }
    void setMissionNum(const int &newMissionNum) { missionNum = newMissionNum; }
    void setCasualEnemyNum(int newCasualEnemyNum) { casualEnemyNum = newCasualEnemyNum; }
    void setSpecialEnemyNum(int newSpecialEnemyNum) { specialEnemyNum = newSpecialEnemyNum; }
    void setInventory(Storage *newInventory) { inventory = newInventory; }

    // methods:
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
    // constructor:
    ZombieMission(string newName, int newMissionNum, int newCasualEnemyNum,
                int newSpecialEnemyNum, Storage *newInventory , vector<vector<Character *>> newEnemies);
};

class HumanMission : public Mission
{
public:
    // constructor:
    HumanMission(string newName, int newMissionNum, int newCasualEnemyNum,
                int newSpecialEnemyNum, Storage *newInventory , vector<vector<Character *>> newEnemies);
};
