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

bool Item::checkStamina()
{
    if (owner->getStamina()->getCurrentPoint() < stamina)
    {
        cout << "insufficient stamina\n";
        return false;
    }
    return true;
}

void Item::takeStamina()
{
    int newPoint = owner->getStamina()->getCurrentPoint() - stamina;
    owner->getStamina()->setCurrentPoint(newPoint);
}

Removable::Removable(string name, int price, Character *owner, int stamina) : Item(name, price, owner, stamina) {}

void Removable::removeFromBackpack() { owner->getBackpack()->removeItem(name); }

Throwable::Throwable(string name, int price, Character *owner, int stamina, int damage) : Removable(name, price, owner, stamina)
{

    this->damage = damage;
    Item *basePtr = this;
    throwables.push_back(basePtr);
}
void Throwable::useItem()
{
    if (checkStamina())
    {
        for (int i = owner->getWave().size() - 1; i >= 0; i--)
        {
            owner->getWave()[i]->takeDamage((getSpecial() * owner->getPowerBoost()) / (i + 1));
            owner->setPowerBoost(1);
        }
        takeStamina();
        removeFromBackpack();
    }
}

Consumable::Consumable(string name, int price, Character *owner, int stamina) : Removable(name, price, owner, stamina) {}

Permanent::Permanent(string name, int price, Character *owner, int stamina, int damage) : Item(name, price, owner, stamina)
{
    this->damage = damage;
}

Melee::Melee(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    melees.push_back(basePtr);
}
void Melee::useItem()
{
    if (checkStamina())
    {
        owner->getWave()[0]->takeDamage(getSpecial() * owner->getMeleeLevel() * owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
}

Firearm::Firearm(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    firearms.push_back(basePtr);
}
void Firearm::useItem()
{
    if (checkStamina())
    {
        owner->getWave()[0]->takeDamage(getSpecial() * owner->getFirearmLevel() * owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
};

HpPotion::HpPotion(string name, int price, Character *owner, int stamina, int healingAmount) : Consumable(name, price, owner, stamina)
{
    this->healingAmount = healingAmount;
    Item *basePtr = this;
    hpPotions.push_back(basePtr);
}

void HpPotion::useItem()
{
    if (checkStamina())
    {
        int newPoint = owner->getHp()->getCurrentPoint() + getSpecial();
        owner->getHp()->setCurrentPoint(newPoint);
        takeStamina();
        removeFromBackpack();
    }
}

StaminaPotion::StaminaPotion(string name, int price, Character *owner, int stamina, int boostAmount) : Consumable(name, price, owner, stamina)
{
    this->boostAmount = boostAmount;
    Item *basePtr = this;
    staminaPotions.push_back(basePtr);
}
void StaminaPotion::useItem()
{
    int newPoint = owner->getStamina()->getCurrentPoint() + getSpecial();
    owner->getStamina()->setCurrentPoint(newPoint);
    removeFromBackpack();
}

PowerPotion::PowerPotion(string name, int price, Character *owner, int stamina, double empowerment) : Consumable(name, price, owner, stamina)
{
    this->empowerment = empowerment;
    Item *basePtr = this;
    powerPotions.push_back(basePtr);
}
void PowerPotion::useItem()
{
    if (checkStamina())
    {
        owner->setPowerBoost(getSpecial());
        takeStamina();
        removeFromBackpack();
    }
}
