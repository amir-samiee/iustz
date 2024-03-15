#pragma once
#include "headers.h"
using namespace std;

class Character; // Forward declaration
class Item;

vector<Item *> throwablee;
vector<Item *> consumablee;
vector<Item *> permanentt;
map<string, Item *> dictionary;

class Item
{
protected:
    string name;
    int price;
    Character *owner;
    int stamina = 0;

public:
    Item(string name, int price, Character *owner, int stamina)
    {
        this->name = name;
        this->price = price;
        this->owner = owner;
        this->stamina = stamina;
        dictionary[name] = this;
    }

    Item() = default;
    virtual void useItem() = 0;

    // getters
    string getName() const
    {
        return name;
    }
    int getPrice() const
    {
        return price;
    }
    Character *getOwner() const
    {
        return owner;
    }
    int getStamina() const
    {
        return stamina;
    }
    virtual int getSpecial() { return 0;}

    // setters
    void setName(const string &newName)
    {
        name = newName;
    }
    void setPrice(int newPrice)
    {
        price = newPrice;
    }
    void setOwner(Character *newOwner)
    {
        owner = newOwner;
    }
    void setStamina(int newStamina)
    {
        stamina = newStamina;
    }
    virtual void setSpecial(int newSpecial) {}
};

class Throwable : public Item
{
protected:
    int damage;

public:
    // constructor:
    Throwable(string name, int price, Character *owner, int stamina, int damage) : Item(name, price, owner, stamina)
    {
        this->damage = damage;
        Item *basePtr = dynamic_cast<Item *>(this);
        throwablee.push_back(basePtr);
    }
    virtual void useItem() {}

    // getters
    int getSpecial() override
    {
        return damage;
    }

    // setters
    void setSpecial(int newDamage) override
    {
        damage = newDamage;
    }
};

class Consumable : public Item
{
protected:
    virtual void removeFromBackpack() {}

public:
    Consumable(string name, int price, Character *owner, int stamina) : Item(name, price, owner, stamina) {}
    virtual int getSpecial() { return 0; }
    virtual void setSpecial() {}
};

class Permanent : public Item
{
protected:
    int damage = 0;

public:
    // constructor:
    Permanent(string name, int price, Character *owner, int stamina, int damage) : Item(name, price, owner, stamina)
    {
        this->damage = damage;
    }
    virtual void useItem() {}

    // getters
    int getSpecial () override
    {
        return damage;
    }

    // setters
    void setSpecial(int newdamage) override
    {
        damage = newdamage;
    }
};

class Melee : public Permanent
{
public:
    // constructor
    Melee(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
    {
        Item *basePtr = this;
        permanentt.push_back(basePtr);
    }
    // others
    void useItem() override{};
};

class Firearm : public Permanent
{
public:
    // constructor
    Firearm(string name, int price, Character *owner, int stamina, int damage) : Permanent(name, price, owner, stamina, damage)
    {
        Item *basePtr = this;
        permanentt.push_back(basePtr);
    }
    // others
    void useItem() override{};
};

class HpPotion : public Consumable
{
protected:
    int healingAmount;

public:
    // constructor
    HpPotion(string name, int price, Character *owner, int stamina, int healingAmount) : Consumable(name, price, owner, stamina)
    {
        this->healingAmount = healingAmount;
        Item *basePtr = dynamic_cast<Item *>(this);
        consumablee.push_back(basePtr);
    }

    // getters
    int getSpecial() override
    {
        return healingAmount;
    }

    // setters
    void setSpecial(int newAmount) override
    {
        healingAmount = newAmount;
    }

    // others
    void useItem() override
    {
        // Implementation for healing logic
    }
};

class StaminaPotion : public Consumable
{
protected:
    int boostAmount;

public:
    // constructor
    StaminaPotion(string name, int price, Character *owner, int stamina, int boostAmount) : Consumable(name, price, owner, stamina)
    {
        this->boostAmount = boostAmount;
        Item *basePtr = dynamic_cast<Item *>(this);
        consumablee.push_back(basePtr);
    }

    // getters
    int getSpecial() override
    {
        return boostAmount;
    }

    // setters
    void setSpecial(int newAmount) override
    {
        boostAmount = newAmount;
    }

    // others
    void useItem() override
    {
        // Implementation for stamina boost logic
    }
};

class PowerPotion : public Consumable
{
protected:
    double empowerment;

public:
    PowerPotion(string name, int price, Character *owner, int stamina, double empowerment) : Consumable(name, price, owner, stamina)
    {
        this->empowerment = empowerment;
        Item *basePtr = dynamic_cast<Item *>(this);
        consumablee.push_back(basePtr);
    }
    void useItem() override
    {
        // Implementation for power increase logic
    }

    // getters
    int getSpecial() override
    {
        return empowerment;
    }

    // setters
    void setSpecial(int newEmpowerment) override
    {
        empowerment = newEmpowerment;
    }
};

// objects of Throwable class

Throwable throwable1("Grenade", 5, nullptr, 5, 5);
Throwable throwable2("Freezer Grenade", 10, nullptr, 10, 10);
Throwable throwable3("acid Bottle", 20, nullptr, 15, 15);
Throwable throwable4("Molotov Cocktails", 30, nullptr, 20, 20);
Throwable throwable5("Taser Darts", 50, nullptr, 25, 25);
Throwable throwable6("Drone", 100, nullptr, 50, 150);
Throwable throwable7("Armored Personnel Carrier", 200, nullptr, 100, 300);
Throwable throwable8("Attack Helicopter", 300, nullptr, 200, 500);
Throwable throwable9("Fighter Jet", 400, nullptr, 300, 600);
Throwable throwable10("Gunship", 500, nullptr, 450, 900);

// objects of permanant class
// "melee"
Melee melee1("Punch", 0, nullptr, 0, 5);
Melee melee2("Axe", 10, nullptr, 10, 20);
Melee melee3("Nunchaku", 50, nullptr, 10, 20);
Melee melee4("Sword", 20, nullptr, 20, 40);
Melee melee5("Katana", 25, nullptr, 20, 40);
Melee melee6("Dagger", 30, nullptr, 30, 60);
Melee melee7("Spear", 35, nullptr, 30, 60);
Melee melee8("Halberd", 40, nullptr, 40, 80);
Melee melee9("Rapier", 45, nullptr, 40, 80);
Melee melee10("Chainsaw", 50, nullptr, 50, 100);

//"fireArm"
Firearm fireArm1("Desert Eagle", 10, nullptr, 10, 20);
Firearm fireArm2("Glock 17", 20, nullptr, 20, 40);
Firearm fireArm3("Shutgun", 30, nullptr, 30, 60);
Firearm fireArm4("Rifle", 40, nullptr, 40, 80);
Firearm fireArm5("Submachine gun", 50, nullptr, 50, 100);
Firearm fireArm6("Carbine", 60, nullptr, 60, 120);
Firearm fireArm7("Assault rifle", 70, nullptr, 70, 140);
Firearm fireArm8("Sniper rifle", 80, nullptr, 80, 160);
Firearm fireArm9("Machine gun", 90, nullptr, 90, 180);
Firearm fireArm10("FN SCAR", 100, nullptr, 100, 200);

// object of consumable class
// hp potion
HpPotion hpPotion1("First Aid Kits", 5, nullptr, 2, 5);
HpPotion hpPotion2("Bandages", 10, nullptr, 5, 10);
HpPotion hpPotion3("Medkits", 15, nullptr, 10, 20);
HpPotion hpPotion4("Healing Salve", 20, nullptr, 20, 40);
HpPotion hpPotion5("Potion of Vitality", 35, nullptr, 30, 75);
HpPotion hpPotion6("Diamond Elixir", 50, nullptr, 50, 100);

// stamina potion
StaminaPotion staminaPotion1("Vigor Rush", 5, nullptr, 0, 10);
StaminaPotion staminaPotion2("Energy Surge", 10, nullptr, 0, 20);
StaminaPotion staminaPotion3("Turbo Tonic", 20, nullptr, 0, 30);
StaminaPotion staminaPotion4("Endurance Elixir", 35, nullptr, 0, 40);
StaminaPotion staminaPotion5("Stamina Spark", 50, nullptr, 0, 50);

// power potion
PowerPotion powerPotion1("Savage Serum", 5, nullptr, 0, 2);
PowerPotion powerPotion2("Titan Tonic", 25, nullptr, 0, 3);
PowerPotion powerPotion3("Cataclysmic", 125, nullptr, 0, 4);
PowerPotion powerPotion4("Blitzkrieg Booster", 225, nullptr, 0, 5);
PowerPotion powerPotion5("Eternal Valor Elixir", 500, nullptr, 0, 6);
