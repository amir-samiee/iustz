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

bool Item::checkForUse()
{
    if (owner->getStamina()->getCurrentPoint() < stamina)
    {
        cout << red << "insufficient stamina\n"
             << reset;
        return false;
    }
    if (owner->getBackpack()->getItems()[name] == 0)
    {
        
        cout << red << "user doesn't own the item\n"
             << reset;
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

void Removable::info(){}

Throwable::Throwable(string name, int price, Character *owner, int stamina, int damage) : Removable(name, price, owner, stamina)
{

    this->damage = damage;
    Item *basePtr = this;
    throwables.push_back(basePtr);
}
void Throwable::useItem()
{
    if (checkForUse())
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
void Throwable::info() {
    cout << owner->getName() << "threw" << name << endl;
}

Consumable::Consumable(string name, int price, Character *owner, int stamina) : Removable(name, price, owner, stamina) {}

void Consumable::info() {
    cout << owner->getName() << "consumed" << name << endl;
}

Permanent::Permanent(string name, int price, Character *owner, int stamina, int damage) : Item(name, price, owner, stamina)
{
    this->damage = damage;
}

void Permanent::info() {
    cout << owner->getName() << "attacked with" << name << endl;
}

Melee::Melee(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    melees.push_back(basePtr);
}
void Melee::useItem()
{
    if (checkForUse())
    {
        owner->getWave()[0]->takeDamage(getSpecial() *(1+((owner->getMeleeLevel()-1)/6)) * owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
}

void Melee::info() {
    cout << owner->getName() << "hit" << name << endl;
}

Firearm::Firearm(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    firearms.push_back(basePtr);
}
void Firearm::useItem()
{
    if (checkForUse())
    {
        owner->getWave()[0]->takeDamage(getSpecial() * (1+((owner->getFirearmLevel()-1)/6) )* owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
};

void Firearm::info() {
    cout << owner->getName() << "shot" << name << endl;
}

HpPotion::HpPotion(string name, int price, Character *owner, int stamina, int healingAmount) : Consumable(name, price, owner, stamina)
{
    this->healingAmount = healingAmount;
    Item *basePtr = this;
    hpPotions.push_back(basePtr);
}

void HpPotion::useItem()
{
    if (checkForUse())
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
    if (checkForUse())
    {
        owner->setPowerBoost(getSpecial());
        takeStamina();
        removeFromBackpack();
    }
}
