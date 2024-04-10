#pragma once
#include "headers.h"

vector<string> Mission::eventsLog = {};

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

void Item::useItem()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " used " + name;
    Mission::eventsLog.push_back(news);
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
    info();
    if (checkForUse())
    {
        double special = getSpecial() * ((rand() % 51 + 75) / 100.0);
        for (int i = owner->getWave().size() - 1; i >= 0; i--)
        {
            owner->getWave()[i]->takeDamage((special * owner->getPowerBoost()) / (i + 1));
            owner->setPowerBoost(1);
        }
        takeStamina();
        removeFromBackpack();
    }
}

void Throwable::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " threw a " + name;
    Mission::eventsLog.push_back(news);
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
    info();
    if (checkForUse())
    {
        int special = getSpecial() * ((rand() % 51 + 75) / 100.0);
        double skill = 1 + ((owner->getMeleeLevel() - 1) / (6.0));
        owner->currentEnemy()->takeDamage(special * skill * owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
}

void Melee::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " hit with " + name;
    Mission::eventsLog.push_back(news);
}

Firearm::Firearm(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
{
    Item *basePtr = this;
    firearms.push_back(basePtr);
}
void Firearm::useItem()
{
    info();
    if (checkForUse())
    {
        int special = getSpecial() * ((rand() % 51 + 75) / 100.0);
        owner->getWave()[0]->takeDamage(special * (1 + ((owner->getFirearmLevel() - 1) / 6)) * owner->getPowerBoost());
        owner->setPowerBoost(1);
        takeStamina();
    }
};

void Firearm::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " fired the " + name;
    Mission::eventsLog.push_back(news);
}

HpPotion::HpPotion(string name, int price, Character *owner, int stamina, int healingAmount) : Consumable(name, price, owner, stamina)
{
    this->healingAmount = healingAmount;
    Item *basePtr = this;
    hpPotions.push_back(basePtr);
}

void HpPotion::useItem()
{
    info();
    if (checkForUse())
    {
        int newPoint = owner->getHp()->getCurrentPoint() + getSpecial();
        owner->getHp()->setCurrentPoint(newPoint);
        takeStamina();
        removeFromBackpack();
    }
}

void HpPotion::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " Healed using " + name;
    Mission::eventsLog.push_back(news);
}

StaminaPotion::StaminaPotion(string name, int price, Character *owner, int stamina, int boostAmount) : Consumable(name, price, owner, stamina)
{
    this->boostAmount = boostAmount;
    Item *basePtr = this;
    staminaPotions.push_back(basePtr);
}

void StaminaPotion::useItem()
{
    info();
    int newPoint = owner->getStamina()->getCurrentPoint() + getSpecial();
    owner->getStamina()->setCurrentPoint(newPoint);
    removeFromBackpack();
}

void StaminaPotion::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " boosted stamina using " + name;
    Mission::eventsLog.push_back(news);
}

PowerPotion::PowerPotion(string name, int price, Character *owner, int stamina, double empowerment) : Consumable(name, price, owner, stamina)
{
    this->empowerment = empowerment;
    Item *basePtr = this;
    powerPotions.push_back(basePtr);
}

void PowerPotion::useItem()
{
    info();
    if (checkForUse())
    {
        owner->setPowerBoost(getSpecial()*owner->getPowerBoost());
        takeStamina();
        removeFromBackpack();
    }
}

void PowerPotion::info()
{
    string news;
    news += owner->getName();
    if (dynamic_cast<Player *>(owner) != nullptr)
        news += cyan + " (player)";
    else
        news += magenta + " (enemy)";
    news += reset + " boosted power using " + name;
    Mission::eventsLog.push_back(news);
}