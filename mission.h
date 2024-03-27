#pragma once
#include "headers.h"

class Factory
{
protected:
    int level;
    int casualEnemy;
    int specialEnemy;
    vector<string> missionPermanents;
    vector<string> missionThrowables;
    vector<string> missionHpPotions;
    vector<string> missionStaminaPotions;
    vector<string> missionPowerPotions;
    map<string, vector<string>> missionItemTypes = {
        {"per", missionPermanents},
        {"thr", missionThrowables},
        {"hp", missionHpPotions},
        {"sta", missionStaminaPotions},
        {"pow", missionPowerPotions}};

    vector<int> waveInfo;

public:
    // constructors:
    Factory(int lvl, int casualEn, int specialEn,
            const vector<string> &permanents,
            const vector<string> &throwables,
            const vector<string> &hpPotions,
            const vector<string> &staminaPotions,
            const vector<string> &powerPotions)
        : level(lvl), casualEnemy(casualEn), specialEnemy(specialEn),
          missionPermanents(permanents), missionThrowables(throwables),
          missionHpPotions(hpPotions), missionStaminaPotions(staminaPotions),
          missionPowerPotions(powerPotions) {}
    Factory(int lvl, int casualEn, int specialEn,
            const vector<string> &permanents,
            const vector<string> &throwables,
            const vector<string> &hpPotions,
            const vector<string> &staminaPotions,
            const vector<string> &powerPotions, vector<int> wavesInfo)
        : level(lvl), casualEnemy(casualEn), specialEnemy(specialEn),
          missionPermanents(permanents), missionThrowables(throwables),
          missionHpPotions(hpPotions), missionStaminaPotions(staminaPotions),
          missionPowerPotions(powerPotions), waveInfo(wavesInfo) {}

    // getters:
    int getLevel() const { return level; }
    int getCasualEnemy() const { return casualEnemy; }
    int getSpecialEnemy() const { return specialEnemy; }
    const vector<string> &getMissionPermanents() const { return missionPermanents; }
    const vector<string> &getMissionThrowables() const { return missionThrowables; }
    const vector<string> &getMissionHpPotions() const { return missionHpPotions; }
    const vector<string> &getMissionStaminaPotions() const { return missionStaminaPotions; }
    const vector<string> &getMissionPowerPotions() const { return missionPowerPotions; }

    // seters:
    void setLevel(int newLevel) { level = newLevel; }
    void setCasualEnemy(int newCasualEnemy) { casualEnemy = newCasualEnemy; }
    void setSpecialEnemy(int newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setMissionPermanents(const vector<string> &newPermanents) { missionPermanents = newPermanents; }
    void setMissionThrowables(const vector<string> &newThrowables) { missionThrowables = newThrowables; }
    void setMissionHpPotions(const vector<string> &newHpPotions) { missionHpPotions = newHpPotions; }
    void setMissionStaminaPotions(const vector<string> &newStaminaPotions) { missionStaminaPotions = newStaminaPotions; }
    void setMissionPowerPotions(const vector<string> &newPowerPotions) { missionPowerPotions = newPowerPotions; }

    // methodes:
    vector<int> getWave();
    void addConsumable(vector<Character *> unorderedEn , vector<string> addingItem);
    virtual vector<vector<Character *>> createEnemy(vector<int> waves) = 0;
};

class ZombieFactory : public Factory
{
public:
    ZombieFactory(int lvl, int casualEn, int specialEn,
                  const vector<string> &permanents,
                  const vector<string> &throwables,
                  const vector<string> &hpPotions,
                  const vector<string> &staminaPotions,
                  const vector<string> &powerPotions)
        : Factory(lvl, casualEn, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions) {}

    ZombieFactory(int lvl, int casualEn, int specialEn,
                  const vector<string> &permanents,
                  const vector<string> &throwables,
                  const vector<string> &hpPotions,
                  const vector<string> &staminaPotions,
                  const vector<string> &powerPotions, vector<int> wavesInfo)
        : Factory(lvl, casualEn, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions, wavesInfo) {}

    vector<vector<Character *>> createEnemy(vector<int> waves) override;
};

class HumanFactory : public Factory
{
public:
    HumanFactory(int lvl, int casualEn, int specialEn,
                 const vector<string> &permanents,
                 const vector<string> &throwables,
                 const vector<string> &hpPotions,
                 const vector<string> &staminaPotions,
                 const vector<string> &powerPotions)
        : Factory(lvl, casualEn, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions) {}
    HumanFactory(int lvl, int casualEn, int specialEn,
                 const vector<string> &permanents,
                 const vector<string> &throwables,
                 const vector<string> &hpPotions,
                 const vector<string> &staminaPotions,
                 const vector<string> &powerPotions, vector<int> wavesInfo)
        : Factory(lvl, casualEn, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions, wavesInfo) {}

    vector<vector<Character *>> createEnemy(vector<int> waves) override;
};

/// @brief ///////////////////////////////////////////////

class Mission
{

protected:
    string name;
    int missionNum;
    int casualEnemyNum;
    int specialEnemy;
    vector<string> missionPermanents;
    vector<string> missionThrowables;
    vector<string> missionHpPotions;
    vector<string> missionStaminaPotions;
    vector<string> missionPowerPotions;
    map<string, vector<string>> missionItemTypes = {
        {"per", missionPermanents},
        {"thr", missionThrowables},
        {"hp", missionHpPotions},
        {"sta", missionStaminaPotions},
        {"pow", missionPowerPotions}};

    vector<vector<Character *>> enemies;

public:
    // constructors:
    Mission(string newName, int newMissionNum, int specialEnemy);
    Mission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
            const vector<string> &missionPermanents,
            const vector<string> &missionThrowables,
            const vector<string> &missionHpPotions,
            const vector<string> &missionStaminaPotions,
            const vector<string> &missionPowerPotions)
        : name(name), missionNum(missionNum), casualEnemyNum(casualEnemyNum), specialEnemy(specialEnemy),
          missionPermanents(missionPermanents), missionThrowables(missionThrowables),
          missionHpPotions(missionHpPotions), missionStaminaPotions(missionStaminaPotions),
          missionPowerPotions(missionPowerPotions) {}

    // getters:
    string getName() const { return name; }
    int getMissionNum() const { return missionNum; }
    int getCasualEnemyNum() const { return casualEnemyNum; }
    int getSpecialEnemy() const { return specialEnemy; }
    const vector<string> &getMissionPermanents() const { return missionPermanents; }
    const vector<string> &getMissionThrowables() const { return missionThrowables; }
    const vector<string> &getMissionHpPotions() const { return missionHpPotions; }
    const vector<string> &getMissionStaminaPotions() const { return missionStaminaPotions; }
    const vector<string> &getMissionPowerPotions() const { return missionPowerPotions; }

    // setters :
    void setName(const string &newName) { name = newName; }
    void setMissionNum(const int &newMissionNum) { missionNum = newMissionNum; }
    void setCasualEnemyNum(int newCasualEnemyNum) { casualEnemyNum = newCasualEnemyNum; }
    void setSpecialEnemyNum(int newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setMissionPermanents(const vector<string> &newPermanents) { missionPermanents = newPermanents; }
    void setMissionThrowables(const vector<string> &newThrowables) { missionThrowables = newThrowables; }
    void setMissionHpPotions(const vector<string> &newHpPotions) { missionHpPotions = newHpPotions; }
    void setMissionStaminaPotions(const vector<string> &newStaminaPotions) { missionStaminaPotions = newStaminaPotions; }
    void setMissionPowerPotions(const vector<string> &newPowerPotions) { missionPowerPotions = newPowerPotions; }

    // methods:
    // virtual void initInventory();
    void initCon(vector<Item *> addingItem, string type);
    void story();
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
    ZombieMission(string newName, int newMissionNum, int newSpecialEnemy);
    ZombieMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                  const vector<string> &missionPermanents,
                  const vector<string> &missionThrowables,
                  const vector<string> &missionHpPotions,
                  const vector<string> &missionStaminaPotions,
                  const vector<string> &missionPowerPotions,
                  const vector<int> wavesInfo);

    // methodes:
    void initInventory();
};

class HumanMission : public Mission
{
public:
    // constructor:
    HumanMission(string newName, int newMissionNum, int newSpecialEnemy);
    HumanMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                 const vector<string> &missionPermanents,
                 const vector<string> &missionThrowables,
                 const vector<string> &missionHpPotions,
                 const vector<string> &missionStaminaPotions,
                 const vector<string> &missionPowerPotions,
                 const vector<int> wavesInfo);

    // methodes:
    void initInventory();
};

// a map for connecting missioins to their id:
map<string, Mission *> missionMap;

// vectors for saving missions:
vector<ZombieMission *> zombieMissions;
vector<HumanMission *> humanMissions;