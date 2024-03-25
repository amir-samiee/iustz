#pragma once
#include "headers.h"

vector<int> Factory::getWave()
{
    vector<int> waves;
    int waveNum = casualEnemy / 3;
    int remaining = casualEnemy % waveNum;
    for (int i = 0; i < waveNum; i++)
        waves.push_back(3);

    int index = waveNum - 1;

    while (remaining != 0)
    {
        waves[index]++;
        index--;
        remaining--;
    }

    return waves;
}

/// @brief ////////////////////////////////////

vector<vector<Character *>> HumanFactory ::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief //////////////////////////////

vector<vector<Character *>> ZombieFactory ::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, int specialEnemy)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    this->casualEnemyNum = (rand() % 4) + missionNum + 2;
    this->specialEnemy = specialEnemy;
}

void Mission ::story()
{
    ifstream file("Stories/" + name + ".txt");
    if (file.is_open())
    {
        string line;
        cout << "Mission " << missionNum << " - " << name << ":\n";
        while (getline(file, line))
        {
            cout << line << endl;
            Sleep(2000);
        }
        file.close();
    }
    else
        cerr << "Unable to open file! " << endl;
}

void Mission::addPotion(vector<Item *> addingItem, string type)
{
    int index = 0;
    if ((this->getMissionNum()) / (2.0) <= addingItem.size())
        index = (this->getMissionNum() - 1) / 2;
    else
        index = addingItem.size() - 1;

    for (int i = 0; i < (casualEnemyNum * 2); i++)
        missionItemTypes[type].push_back(addingItem[index]->getName());
}

void Mission ::playerTurn()
{
}

void Mission ::enemyTurn()
{
}

void Mission ::endWave()
{
}
void Mission ::removeDead()
{
}

void Mission ::playerDeath()
{
}

void Mission ::end()
{
}

void Mission::start()
{
}

ZombieMission::ZombieMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    ZombieFactory factory(newMissionNum, casualEnemyNum, specialEnemy,
                          misssionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions);

    this->enemies = factory.createEnemy(factory.getWave());

    // saving mission:
    zombieMissions.push_back(this);
}

ZombieMission::ZombieMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                             const vector<string> &misssionPermanents,
                             const vector<string> &missionThrowables,
                             const vector<string> &missionHpPotions,
                             const vector<string> &missionStaminaPotions,
                             const vector<string> &missionPowerPotions,
                             const vector<int> wavesInfo)
    : Mission(name, missionNum, casualEnemyNum, specialEnemy, misssionPermanents,
              missionThrowables, missionHpPotions, missionStaminaPotions, missionPowerPotions)
{
    // setting the id:
    string id = "z" + missionNum;
    missionMap[id] = this;

    // feeding data to factory:
    ZombieFactory factory(missionNum, casualEnemyNum, specialEnemy,
                          misssionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions , wavesInfo);
    this->enemies = factory.createEnemy(wavesInfo);

    // saving mission:
    zombieMissions.push_back(this);
}
void ZombieMission::initInventory()
{
    if (missionNum < melees.size())
    {
        this->misssionPermanents.push_back(melees[missionNum]->getName());
        if (missionNum != 1)
        {
            this->misssionPermanents.push_back(melees[missionNum - 1]->getName());
        }
    }
    else
    {
        this->misssionPermanents.push_back(melees[melees.size() - 1]->getName());
        this->misssionPermanents.push_back(melees[melees.size() - 2]->getName());
    }
    addPotion(hpPotions, "hp");
    addPotion(staminaPotions, "sta");
    addPotion(powerPotions, "pow");
}

HumanMission::HumanMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy,
                          misssionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions);
    
    this->enemies = factory.createEnemy(factory.getWave());

    // saving mission:
    humanMissions.push_back(this);
}

HumanMission::HumanMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                           const vector<string> &misssionPermanents,
                           const vector<string> &missionThrowables,
                           const vector<string> &missionHpPotions,
                           const vector<string> &missionStaminaPotions,
                           const vector<string> &missionPowerPotions,
                           const vector<int> wavesInfo)
    : Mission(name, missionNum, casualEnemyNum, specialEnemy, misssionPermanents,
              missionThrowables, missionHpPotions, missionStaminaPotions, missionPowerPotions)
{
    // setting the id:
    string id = "h" + missionNum;
    missionMap[id] = this;

    // feeding data to factory:
    HumanFactory factory(missionNum, casualEnemyNum, specialEnemy,
                          misssionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions , wavesInfo);
    vector<int> waves; // give the customized waves
    this->enemies = factory.createEnemy(waves);

    // saving mission:
    humanMissions.push_back(this);
}

void HumanMission::initInventory()
{
    if (missionNum < firearms.size())
    {
        this->misssionPermanents.push_back(firearms[missionNum - 1]->getName());
        if (missionNum != 1)
        {
            this->misssionPermanents.push_back(firearms[missionNum - 2]->getName());
        }
    }
    else
    {
        this->misssionPermanents.push_back(firearms[firearms.size() - 1]->getName());
        this->misssionPermanents.push_back(firearms[firearms.size() - 2]->getName());
    }
    addPotion(hpPotions, "hp");
    addPotion(staminaPotions, "sta");
    addPotion(powerPotions, "pow");
}
