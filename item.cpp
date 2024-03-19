#pragma once
#include "headers.h"

Item::Item(string name, int price, Character *owner, int stamina)
{
    this->name = name;
    this->price = price;
    this->owner = owner;
    this->stamina = stamina;
    itemsMap[name] = this;
}

bool Item::checkAndTakeStamina()
{
    if (owner->getStamina()->getCurrentPoint() < this->getStamina())
    {
        cout << "not enough stamina\n";
        return false;
    }
    int newPoint = owner->getStamina()->getCurrentPoint() - this->getStamina();
    owner->getStamina()->setCurrentPoint(newPoint);
    return true;
}
Removable::Removable(string name, int price, Character *owner, int stamina) : Item(name, price, owner, stamina) {}

void Removable::removeFromBackpack() {}

Throwable::Throwable(string name, int price, Character *owner, int stamina, int damage) : Removable(name, price, owner, stamina)
{

    this->damage = damage;
    Item *basePtr = this;
    throwables.push_back(basePtr);
}
void Throwable::useItem()
{
    if (this->checkAndTakeStamina())
    {
        for (int i = owner->getWave().size() - 1; i >= 0 ; i--)
        {
            int currentPoint = owner->getWave()[i]->getHp()->getCurrentPoint();
            int newPoint = currentPoint - ((this->getSpecial() * owner->getPowerBoost()) / (i + 1));
            owner->getWave()[i]->takeDamage(newPoint);
            owner->setPowerBoost(1);
        }
    }
}

Consumable::Consumable(string name, int price, Character *owner, int stamina) : Removable(name, price, owner, stamina) {}

Permanent::Permanent(string name, int price, Character *owner, int stamina, int damage) : Item(name, price, owner, stamina)
{
    this->damage = damage;
}
void Permanent::useItem() {}

Melee::Melee(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    permanents.push_back(basePtr);
}
void Melee::useItem()
{
    if (this->checkAndTakeStamina())
    {
        int currentPoint = owner->getWave()[0]->getHp()->getCurrentPoint();
        int newPoint = currentPoint - (this->getSpecial() * owner->getMeleeLevel() * owner->getPowerBoost());
        owner->getWave()[0]->takeDamage(newPoint);
        owner->setPowerBoost(1);
    }
}

Firearm::Firearm(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    permanents.push_back(basePtr);
}
void Firearm::useItem()
{
    if (this->checkAndTakeStamina())
    {
        int currentPoint = owner->getWave()[0]->getHp()->getCurrentPoint();
        int newPoint = currentPoint - (this->getSpecial() * owner->getFirearmLevel() * owner->getPowerBoost());
        owner->getWave()[0]->takeDamage(newPoint);
        owner->setPowerBoost(1);
    }
};

HpPotion::HpPotion(string name, int price, Character *owner, int stamina, int healingAmount) : Consumable(name, price, owner, stamina)
{
    this->healingAmount = healingAmount;
    Item *basePtr = this;
    consumables.push_back(basePtr);
}

void HpPotion::useItem()
{
    if (this->checkAndTakeStamina())
    {
        int newPoint = owner->getHp()->getCurrentPoint() + this->getSpecial();
        owner->getHp()->setCurrentPoint(newPoint);
    }
}

StaminaPotion::StaminaPotion(string name, int price, Character *owner, int stamina, int boostAmount) : Consumable(name, price, owner, stamina)
{
    this->boostAmount = boostAmount;
    Item *basePtr = this;
    consumables.push_back(basePtr);
}
void StaminaPotion::useItem()
{
    if (this->checkAndTakeStamina())
    {
        int newPoint = owner->getStamina()->getCurrentPoint() + this->getSpecial();
        owner->getStamina()->setCurrentPoint(newPoint);
    }
}

PowerPotion::PowerPotion(string name, int price, Character *owner, int stamina, double empowerment) : Consumable(name, price, owner, stamina)
{
    this->empowerment = empowerment;
    Item *basePtr = this;
    consumables.push_back(basePtr);
}
void PowerPotion::useItem()
{
    if (this->checkAndTakeStamina())
    {
        owner->setPowerBoost(this->getSpecial());
    }
}
