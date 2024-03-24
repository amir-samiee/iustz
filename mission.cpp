#pragma once
#include "headers.h"

Factory::Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory)
{
    this->level = level;
    this->casualEnemy = casualEnemy;
    this->specialEnemy = specialEnemy;
    this->inventory = inventory;
}
Factory::Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int** waveInfo)
{
    this->level = level;
    this->casualEnemy = casualEnemy;
    this->specialEnemy = specialEnemy;
    this->inventory = inventory;
    this->waveInfo = waveInfo;
}

vector<int> Factory::getWave()
{
    vector<int> waves;
    return waves;
}

/// @brief ////////////////////////////////////

HumanFactory::HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}
HumanFactory::HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int** waveInfo) : Factory(level, casualEnemy, specialEnemy, inventory, waveInfo) {}

vector<vector<Character *>> HumanFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief //////////////////////////////

ZombieFactory::ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}
ZombieFactory::ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int** waveInfo) : Factory(level, casualEnemy, specialEnemy, inventory, waveInfo) {}

vector<vector<Character *>> ZombieFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, bool specialEnemy)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    casualEnemyNum = (rand() % 4) + missionNum + 2;
    this->specialEnemy = specialEnemy;
}
Mission ::Mission(string newName, int newMissionNum, int newCasualEnemyNum, bool specialEnemy, Storage *newInventory)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    this->casualEnemyNum = casualEnemyNum;
    this->specialEnemy = specialEnemy;
    this->inventory = newInventory;
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

ZombieMission::ZombieMission(string newName, int newMissionNum, bool specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    ZombieFactory factory(newMissionNum, casualEnemyNum, specialEnemy, this->getInventory());
    this->enemies = factory.createEnemy();

    // saving mission:
    zombieMissions.push_back(this);
}

ZombieMission::ZombieMission(string newName, int newMissionNum, int newCasualEnemy,
                             bool specialEnemy, Storage *newInventory , int** waveInfo)
    : Mission(newName, newMissionNum, newCasualEnemy, specialEnemy, newInventory)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
    ZombieFactory factory(missionNum, casualEnemyNum, specialEnemy, this->getInventory(), waveInfo);
    this->enemies = factory.createEnemy();

    // saving mission:
    zombieMissions.push_back(this);
}
void ZombieMission::initInventory()
{
    if (missionNum < melees.size())
    {
        inventory->addItem(melees[missionNum]->getName());
        if (missionNum != 1)
        {
            inventory->addItem(melees[missionNum - 1]->getName());
        }
    }
    else
    {
        inventory->addItem(melees[melees.size() - 1]->getName());
        inventory->addItem(melees[melees.size() - 2]->getName());
    }
    addPotion(hpPotions, this);
    addPotion(staminaPotions, this);
    addPotion(powerPotions, this);
}

HumanMission::HumanMission(string newName, int newMissionNum, bool specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy, this->getInventory());
    this->enemies = factory.createEnemy();

    // saving mission:
    humanMissions.push_back(this);
}

HumanMission::HumanMission(string newName, int newMissionNum, int newCasualEnemy,
                           bool specialEnemy, Storage *newInventory, int** waveInfo)
    : Mission(newName, newMissionNum, newCasualEnemy, specialEnemy, newInventory)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy, this->getInventory(), waveInfo);
    this->enemies = factory.createEnemy();

    // saving mission:
    humanMissions.push_back(this);
}

void HumanMission::initInventory()
{
    if (missionNum < firearms.size())
    {
        inventory->addItem(firearms[missionNum - 1]->getName());
        if (missionNum != 1)
        {
            inventory->addItem(firearms[missionNum - 2]->getName());
        }
    }
    else
    {
        inventory->addItem(firearms[firearms.size() - 1]->getName());
        inventory->addItem(firearms[firearms.size() - 2]->getName());
    }
    addPotion(hpPotions, this);
    addPotion(staminaPotions, this);
    addPotion(powerPotions, this);
}
