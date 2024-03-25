#pragma once
#include "headers.h"

Factory::Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory)
{
    this->level = level;
    this->casualEnemy = casualEnemy;
    this->specialEnemy = specialEnemy;
    this->inventory = inventory;
}

Factory::Factory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo)
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

HumanFactory::HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}
HumanFactory::HumanFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo) : Factory(level, casualEnemy, specialEnemy, inventory, waveInfo) {}

vector<vector<Character *>> HumanFactory ::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief //////////////////////////////

ZombieFactory::ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory) : Factory(level, casualEnemy, specialEnemy, inventory) {}
ZombieFactory::ZombieFactory(int level, int casualEnemy, bool specialEnemy, Storage *inventory, int **waveInfo) : Factory(level, casualEnemy, specialEnemy, inventory, waveInfo) {}

vector<vector<Character *>> ZombieFactory ::createEnemy(vector<int> waves)
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

void Mission::addPotion(vector<Item *> addingItem)
{
    int index = 0, number;
    Storage *inventory = this->getInventory();

    if ((this->getMissionNum()) / (2.0) <= addingItem.size())
        index = (this->getMissionNum() - 1) / 2;
    else
        index = addingItem.size() - 1;

    for (int i = 0; i < number; i++)
        inventory->addItem(addingItem[(this->getMissionNum() - 1) / 2]->getName());

    this->setInventory(inventory);
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
    this->enemies = factory.createEnemy(factory.getWave());

    // saving mission:
    zombieMissions.push_back(this);
}

ZombieMission::ZombieMission(string newName, int newMissionNum, int newCasualEnemy,
                             bool specialEnemy, Storage *newInventory, int **waveInfo)
    : Mission(newName, newMissionNum, newCasualEnemy, specialEnemy, newInventory)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
    ZombieFactory factory(missionNum, casualEnemyNum, specialEnemy, this->getInventory(), waveInfo);
    vector<int> waves; // give the customized waves:
    this->enemies = factory.createEnemy(waves);

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
    addPotion(hpPotions);
    addPotion(staminaPotions);
    addPotion(powerPotions);
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
    this->enemies = factory.createEnemy(factory.getWave());

    // saving mission:
    humanMissions.push_back(this);
}

HumanMission::HumanMission(string newName, int newMissionNum, int newCasualEnemy,
                           bool specialEnemy, Storage *newInventory, int **waveInfo)
    : Mission(newName, newMissionNum, newCasualEnemy, specialEnemy, newInventory)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy, this->getInventory(), waveInfo);
    vector<int> waves; // give the customized waves
    this->enemies = factory.createEnemy(waves);

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
    addPotion(hpPotions);
    addPotion(staminaPotions);
    addPotion(powerPotions);
}
