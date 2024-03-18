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

vector<vector<Character *>> HumanFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

vector<vector<Character *>> ZombieFactory ::createEnemy()
{
    vector<vector<Character *>> enemies;
    return enemies;
}

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, int newCasualEnemyNum, int newSpecialEnemyNum, Storage *newInventory)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    this->casualEnemyNum = newCasualEnemyNum;
    this->specialEnemyNum = newSpecialEnemyNum;
    this->inventory = newInventory;
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
                             int newSpecialEnemyNum, Storage *newInventory, vector<vector<Character *>> newEnemies)
    : Mission(newName, newMissionNum, newCasualEnemyNum, newSpecialEnemyNum, newInventory)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
}

HumanMission::HumanMission(string newName, int newMissionNum, int newCasualEnemyNum,
                           int newSpecialEnemyNum, Storage *newInventory, vector<vector<Character *>> newEnemies)
    : Mission(newName, newMissionNum, newCasualEnemyNum, newSpecialEnemyNum, newInventory)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // feeding data to factory:
}