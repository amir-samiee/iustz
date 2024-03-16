#pragma once
#include "headers.h"

void Stat::setCurrentPoint(int newValue)
{
    if (newValue > maxPoint)
        currentPoint = maxPoint;
    else if(newValue < 0)
        currentPoint = 0;
    else
        currentPoint = newValue;
}

int Stat::level()
{
    return (((maxPoint - 100) / 30) + 1);
}

/// @brief ////////////////////////////////////////////////////

int Character::level() { return firearmLevel + meleeLevel + hp.level() + stamina.level(); }
void Character::takeDamage(int newPoint){
    if(newPoint == 0)
        this->die();
    else
        this->getHp().setCurrentPoint(newPoint);
}

/// @brief /////////////////////////////////////////////////////

void Player::turn() {}
void Player::die() {}
void Enemy::turn() {}
void Enemy::die() {}
void SpecialZombie::turn() {}
