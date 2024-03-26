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

int Player::level() { return (firearmLevel + meleeLevel + hp.level() + stamina.level()) / 4; }
void Player::takeDamage(int takenDamage)
{
    int newPoint = this->getHp()->getCurrentPoint() - takenDamage;
    this->getHp()->setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
Player ::Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins, Storage inventory, int humanLevels, int zombieLevels) : name(name), age(age), gender(gender), backpack(backpack),
                                                                                                                                                    hp(hp), stamina(stamina), firearmLevel(firearmLevel), meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins), inventory(inventory), humanLevels(humanLevels), zombieLevels(zombieLevels) {}

int Enemy::level() { return (model.firearmLevel + model.meleeLevel + model.hp.level() + model.stamina.level()) / 4; }
void Enemy::takeDamage(int takenDamage)
{
    int newPoint = model.hp.getCurrentPoint() - takenDamage;
    this->getHp()->setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
// HumanEnemy::HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
//                        Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
//                                                                                                                                                     stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}
//
// ZombieEnemy::ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
//                          Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
//                                                                                                                                                       stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}
//
// SpecialZombie::SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
//                              Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : ZombieEnemy(name, age, gender, backpack, hp,
//                                                                                                                                                                 stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

/// @brief /////////////////////////////////////////////////////

void Player::turn() {}
void Player::die() {}
void Enemy::turn() {}
void Enemy::die() {}
void SpecialZombie::turn() {}
