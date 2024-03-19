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

int Character::level() { return (firearmLevel + meleeLevel + hp.level() + stamina.level()) / 4; }
void Character::takeDamage(int takenDamage)
{
    int newPoint = this->getHp()->getCurrentPoint() - takenDamage;
    this->getHp()->setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
Character ::Character(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                      int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : name(name), age(age), gender(gender), backpack(backpack),
                                                                                                    hp(hp), stamina(stamina), firearmLevel(firearmLevel), meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins) {}

Player ::Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins, Storage inventory, int humanLevels, int zombieLevels) : Character(name, age, gender, backpack, hp, stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins), inventory(inventory), humanLevels(humanLevels), zombieLevels(zombieLevels) {}

Enemy::Enemy(string name, int age, string gender, LimitedStorage backpack,
             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Character(name, age, gender, backpack, hp,
                                                                                                                                              stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

HumanEnemy::HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
                       Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                    stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

ZombieEnemy::ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                         Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                      stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

SpecialZombie::SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : ZombieEnemy(name, age, gender, backpack, hp,
                                                                                                                                                                stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

/// @brief /////////////////////////////////////////////////////

void Player::turn() {}
void Player::die() {}
void Enemy::turn() {}
void Enemy::die() {}
void SpecialZombie::turn() {}
