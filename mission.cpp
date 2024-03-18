#pragma once
#include "headers.h"

Factory::Factory(int level , int casualEnemy , int specialEnemy , Storage *inventory){
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

void Factory::setFactory(int level , int casualEnemy , int specialEnemy , Storage *inventory){
    this->setLevel(level);
    this->setCasualEnemy(casualEnemy);
    this->setSpecialEnemy(specialEnemy);
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

void Mission ::playerDeath(){
    
}

void Mission ::end()
{
}

void Mission::start(){

}
