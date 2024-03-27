#pragma once
#include "headers.h"

void Stat::setCurrentPoint(int newValue)
{
    if (newValue > maxPoint)
        currentPoint = maxPoint;
    else if (newValue < 0)
        currentPoint = 0;
    else
        currentPoint = newValue;
}

int Stat::level()
{
    return (((maxPoint - 100) / 30) + 1);
}

/// @brief ////////////////////////////////////////////////////
bool Player::isAlive() { return hp.getCurrentPoint() > 0; }
int Player::level() { return (firearmLevel + meleeLevel + hp.level() + stamina.level()) / 4; }
void Player::takeDamage(int takenDamage)
{
    int newPoint = hp.getCurrentPoint() - takenDamage;
    hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
Player ::Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins, Storage inventory, int humanLevels, int zombieLevels) : name(name), age(age), gender(gender), backpack(backpack),
                                                                                                                                                       hp(hp), stamina(stamina), firearmLevel(firearmLevel), meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins), inventory(inventory), humanLevels(humanLevels), zombieLevels(zombieLevels) {}

MVC::EnemyModel::EnemyModel(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                            int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : name(name), age(age), gender(gender), backpack(backpack), hp(hp), stamina(stamina), firearmLevel(firearmLevel),
      meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins) {}

bool MVC::EnemyModel::isAlive() { return hp.getCurrentPoint() > 0; }

void MVC::EnemyController::takeDamage(int takenDamage)
{
    int newPoint = model->hp.getCurrentPoint() - takenDamage;
    model->hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}

void MVC::EnemyController::die()
{
    //setting rewards:
    map<string, int> bpck = self->getBackpack()->getItems();
    Storage mystg = self->getWave()[0]->getReward();
    for (auto item : bpck)
        for (int i = 0; i < item.second; i++)
            mystg.addItem(item.first);
    self->getWave()[0]->setReward(mystg);

    //removing enemy from wave:
    vector<Character *> newvec = this->self->getWave()[0]->getWave();
    for (int i = 0; i < newvec.size(); i++)
    {
        if (newvec[i] == dynamic_cast<Character *>(self))
        {
            newvec.erase(newvec.begin() + i);
            break;
        }
    }
    this->self->getWave()[0]->setWave(newvec);
}

Enemy::Enemy(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
             int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : model(new MVC::EnemyModel(name, age, gender, backpack, hp, stamina, firearmLevel,
                                meleeLevel, powerBoost, currentWave, coins)),
      view(new MVC::EnemyView)
{
    this->controller = new MVC::EnemyController(model, view, this);
}
Enemy::~Enemy()
{
    delete model;
    delete view;
    delete controller;
}
bool Enemy::isAlive() { return model->isAlive(); }
int Enemy::level() { return (model->firearmLevel + model->meleeLevel + model->hp.level() + model->stamina.level()) / 4; }
void Enemy::takeDamage(int damage) { controller->takeDamage(damage); }

HumanEnemy::HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
                       Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                       stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

ZombieEnemy::ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                         Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                         stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

SpecialZombie::SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins) : ZombieEnemy(name, age, gender, backpack, hp,
                                                                                                                                                                   stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

/// @brief /////////////////////////////////////////////////////

void Player::turn()
{
    while (1)
    {
        int choice;
        do
        {
            choice = getInput(backpack.getStorageData(), 1, backpack.getSize(), 0);
            if (itemsMap[backpack.getNames()[choice - 1]]->checkStamina())
                break;
        } while (1);
        itemsMap[backpack.getNames()[choice - 1]]->setOwner(this);
        itemsMap[backpack.getNames()[choice - 1]]->useItem();

        if (dynamic_cast<Permanent *>(itemsMap[backpack.getNames()[choice - 1]]) != nullptr || dynamic_cast<Throwable *>(itemsMap[backpack.getNames()[choice - 1]]) != nullptr)
            break;
    }
}

void Player::die() {}
void Enemy::turn() {}
void Enemy::die() { controller->die(); }
void SpecialZombie::turn() {}
