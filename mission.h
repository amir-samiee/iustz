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

    // methode:
    void initRemovable(vector<Item *> adding, vector<string>); // initializing removable items for a mission
    void addRemovable(vector<Character *> unshuffeledEn, vector<string> addingItem);
    void addPermanent(vector<Character *> unshuffeledEn, vector<string> addingItem);
    vector<vector<Character *>> saveEnemies(vector<int> waves, vector<Character *> unshuffeledEn);

public:
    // constructors:
    Factory(int lvl, int casualEn, int specialEn)
        : level(lvl), casualEnemy(casualEn), specialEnemy(specialEn) {}

    Factory(int lvl, int specialEn,
            const vector<string> &permanents,
            const vector<string> &throwables,
            const vector<string> &hpPotions,
            const vector<string> &staminaPotions,
            const vector<string> &powerPotions,
            vector<int> wavesInfo);

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
    virtual void initInventory() = 0;
    vector<int> getWave(); // Calculating the number of waves and enemies in each
    virtual vector<vector<Character *>> createEnemy(vector<int> waves) = 0;
};

class ZombieFactory : public Factory
{
public:
    // Constructors:
    ZombieFactory(int lvl, int casualEn, int specialEn);

    ZombieFactory(int lvl, int specialEn,
                  const vector<string> &permanents,
                  const vector<string> &throwables,
                  const vector<string> &hpPotions,
                  const vector<string> &staminaPotions,
                  const vector<string> &powerPotions,
                  vector<int> wavesInfo)
        : Factory(lvl, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions, wavesInfo) {}

    // Methodes:
    void initInventory() override;
    vector<vector<Character *>> createEnemy(vector<int> waves) override;
};

class HumanFactory : public Factory
{
public:
    HumanFactory(int lvl, int casualEn, int specialEn);
    HumanFactory(int lvl, int specialEn,
                 const vector<string> &permanents,
                 const vector<string> &throwables,
                 const vector<string> &hpPotions,
                 const vector<string> &staminaPotions,
                 const vector<string> &powerPotions,
                 vector<int> wavesInfo)
        : Factory(lvl, specialEn, permanents, throwables,
                  hpPotions, staminaPotions, powerPotions, wavesInfo) {}

    // Methodes:
    void initInventory() override;
    vector<vector<Character *>> createEnemy(vector<int> waves) override;
};

//////////////////////////////////////////////////////////

class Mission
{
protected:
    string name;
    int humanLevels;  // to be required to pass
    int zombieLevels; // to be required to pass
    int missionNum;
    int casualEnemyNum;
    int specialEnemy;
    vector<vector<Character *>> waves;

public:
    static vector<string> eventsLog;
    // constructors:
    Mission(int newMissionNum, int specialEnemy);
    Mission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy)
        : name(name), missionNum(missionNum), casualEnemyNum(casualEnemyNum), specialEnemy(specialEnemy) {}

    // getters:
    string getName() const { return name; }
    int getMissionNum() const { return missionNum; }
    int getCasualEnemyNum() const { return casualEnemyNum; }
    int getSpecialEnemy() const { return specialEnemy; }
    int getHumanLevels() const { return humanLevels; }
    int getZombieLevels() const { return zombieLevels; }

    // setters :
    void setName(const string &newName) { name = newName; }
    void setWaves(vector<vector<Character *>> waves) { this->waves = waves; }
    void setMissionNum(const int &newMissionNum) { missionNum = newMissionNum; }
    void setCasualEnemyNum(int newCasualEnemyNum) { casualEnemyNum = newCasualEnemyNum; }
    void setSpecialEnemyNum(int newSpecialEnemy) { specialEnemy = newSpecialEnemy; }
    void setHumanLevels(int newLevels) { humanLevels = newLevels; }
    void setZombieLevels(int newLevels) { zombieLevels = newLevels; }

    // methods:
    bool humanQualified(Player *player);
    bool zombieQualified(Player *player);
    bool isUnlocked(Player *player);
    virtual bool isPassed(Player *player) = 0;
    void start();
    void story();
    void middleGame();
    void display();
    void playerTurn();
    void enemyTurn();
    void endWave();
    virtual void end(bool lost);
};

class ZombieMission : public Mission
{
public:
    // constructors:
    ZombieMission(int newMissionNum, int newSpecialEnemy);
    bool isPassed(Player *player) override;
    void end(bool lost) override;
};

class HumanMission : public Mission
{
public:
    // constructor:
    HumanMission(int newMissionNum, int newSpecialEnemy);
    bool isPassed(Player *player) override;
    void end(bool lost) override;
};

// a map for connecting missioins to their ID:
map<string, Mission *> missionMap;

// vectors for saving missions:
vector<Mission *> zombieMissions;
vector<Mission *> humanMissions;

void initializeMissions();