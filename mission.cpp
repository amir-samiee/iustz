#pragma once
#include "headers.h"

Factory::Factory(int level, int casualEnemy, int specialEnemy, Storage *inventory)
{
    this->level = level;
    this->casualEnemy = casualEnemy;
    this->specialEnemy = specialEnemy;
    this->inventory = inventory;
}

vector<int> Factory::getWave()
{
    vector<int> waves;
    return waves;
}

/// @brief ////////////////////////////////////

HumanFactory::HumanFactory(int level, int casualEnemy, int specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}

vector<vector<Character *>> HumanFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief //////////////////////////////

ZombieFactory::ZombieFactory(int level, int casualEnemy, int specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}

vector<vector<Character *>> ZombieFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, int newCasualEnemyNum, int newSpecialEnemyNum)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    this->casualEnemyNum = newCasualEnemyNum;
    this->specialEnemyNum = newSpecialEnemyNum;
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


ZombieMission::ZombieMission(string newName, int newMissionNum, int newCasualEnemyNum,
                             int newSpecialEnemyNum, vector<vector<Character *>> newEnemies)
    : Mission(newName, newMissionNum, newCasualEnemyNum, newSpecialEnemyNum)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    ZombieFactory factory(newMissionNum, newCasualEnemyNum, newSpecialEnemyNum, this->getInventory());
    this->enemies = factory.createEnemy();
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
    addPotion(hpPotions , this);
    addPotion(staminaPotions , this);
    addPotion(powerPotions , this);
}

HumanMission::HumanMission(string newName, int newMissionNum, int newCasualEnemyNum,
                           int newSpecialEnemyNum, vector<vector<Character *>> newEnemies)
    : Mission(newName, newMissionNum, newCasualEnemyNum, newSpecialEnemyNum)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    HumanFactory factory(newMissionNum, newCasualEnemyNum, newSpecialEnemyNum, this->getInventory());
    this->enemies = factory.createEnemy();
    humanMissions.push_back(this);
}
void HumanMission::initInventory()
{
    if (missionNum < firearms.size())
    {
        inventory->addItem(firearms[missionNum-1]->getName());
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
    addPotion(hpPotions , this);
    addPotion(staminaPotions , this);
    addPotion(powerPotions , this);
}
