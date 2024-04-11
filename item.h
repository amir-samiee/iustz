#pragma once
#include "headers.h"

const string firearmType = "Firearm";
const string meleeType = "Melee";
const string throwableType = "Throwable";
const string hpType = "HP Potion";
const string staminaType = "Stamina Potion";
const string powerType = "Power Potion";

class Character; // Forward declaration
class Item;

// this partition will be used in the shop as the user will select which type of items they are going to buy
vector<Item *> throwables;
vector<Item *> hpPotions;
vector<Item *> staminaPotions;
vector<Item *> powerPotions;
vector<Item *> melees;
vector<Item *> firearms;
map<string, Item *> itemsMap;

class Item
{
protected:
    string name;
    int price;
    Character *owner;
    int stamina = 0;

public:
    Item(string name, int price, Character *owner, int stamina);
    Item() = default;

    // getters
    string getName() const { return name; }
    int getPrice() const { return price; }
    Character *getOwner() const { return owner; }
    int getStamina() const { return stamina; }
    virtual double getSpecial() const = 0;
    virtual string getType() const = 0;

    // setters
    void setName(const string newName) { name = newName; }
    void setPrice(int newPrice) { price = newPrice; }
    void setOwner(Character *newOwner) { owner = newOwner; }
    void setStamina(int newStamina) { stamina = newStamina; }
    virtual void setSpecial(int newSpecial) = 0;

    // others
    bool checkForUse();
    void takeStamina();
    virtual void useItem();
    virtual void info() = 0;
};

class Removable : public Item
{
public:
    Removable(string name, int price, Character *owner, int stamina);
    virtual string getType() const = 0;

protected:
    void removeFromBackpack();
};

class Throwable : public Removable
{
protected:
    int damage;

public:
    // constructor:
    Throwable(string name, int price, Character *owner, int stamina, int damage);

    // getters
    double getSpecial() const override { return damage; }
    virtual string getType() const override { return throwableType; }

    // setters
    void setSpecial(int newDamage) override { damage = newDamage; }

    // others
    void useItem();
    virtual void info() override;
};

class Consumable : public Removable
{
public:
    Consumable(string name, int price, Character *owner, int stamina);
    virtual string getType() const = 0;
};

class HpPotion : public Consumable
{
protected:
    int healingAmount;

public:
    // constructor
    HpPotion(string name, int price, Character *owner, int stamina, int healingAmount);

    // getters
    double getSpecial() const override { return healingAmount; }
    virtual string getType() const override { return hpType; }

    // setters
    void setSpecial(int newAmount) override { healingAmount = newAmount; }

    // others
    void useItem() override;
    virtual void info() override;
};

class StaminaPotion : public Consumable
{
protected:
    int boostAmount;

public:
    // constructor
    StaminaPotion(string name, int price, Character *owner, int stamina, int boostAmount);

    // getters
    double getSpecial() const override { return boostAmount; }
    virtual string getType() const override { return staminaType; }

    // setters
    void setSpecial(int newAmount) override { boostAmount = newAmount; }

    // others
    void useItem() override;
    virtual void info() override;
};

class PowerPotion : public Consumable
{
protected:
    double empowerment;

public:
    PowerPotion(string name, int price, Character *owner, int stamina, double empowerment);

    // getters
    double getSpecial() const override { return empowerment; }
    virtual string getType() const override { return powerType; }

    // setters
    void setSpecial(int newEmpowerment) override { empowerment = newEmpowerment; }

    // others
    void useItem() override;
    virtual void info() override;
};

class Permanent : public Item
{
protected:
    int damage = 0;

public:
    // constructor:
    Permanent(string name, int price, Character *owner, int stamina, int damage);

    // getters
    double getSpecial() const override { return damage; }
    virtual string getType() const = 0;

    // setters
    void setSpecial(int newdamage) override { damage = newdamage; }
};

class Melee : public Permanent
{
public:
    // constructor
    Melee(string name, int price, Character *owner, int stamina, int damage);
    // getters
    virtual string getType() const override { return meleeType; }
    // others
    void useItem() override;
    virtual void info() override;
};

class Firearm : public Permanent
{
public:
    // constructor
    Firearm(string name, int price, Character *owner, int stamina, int damage);
    // getters
    virtual string getType() const override { return firearmType; }
    // others
    void useItem() override;
    virtual void info() override;
};

// do not change the order of items declarations
// do not change the order of items declarations
// do not change the order of items declarations

// objects of Throwable class
Throwable throwable1("Grenade", 5, nullptr, 5, 2);
Throwable throwable2("Biotic Grenade", 10, nullptr, 10, 3);
Throwable throwable3("Molotov Cocktails", 15, nullptr, 20, 6);
Throwable throwable4("Acid Bottle", 20, nullptr, 15, 8);
Throwable throwable5("EMP", 25, nullptr, 25, 12);
Throwable throwable6("Drone", 50, nullptr, 50, 18);
Throwable throwable7("Armata", 75, nullptr, 100, 24);
Throwable throwable8("Bell 201", 100, nullptr, 100, 30);
Throwable throwable9("Kiowa", 125, nullptr, 150, 40);
Throwable throwable10("Gunship", 150, nullptr, 200, 50);

// objects of permanant class
// "melee"
Melee melee0("Punch", 0, nullptr, 0, 3);
Melee melee1("Knife", 10, nullptr, 5, 6);
Melee melee2("Axe", 15, nullptr, 10, 9);
Melee melee3("Nunchaku", 20, nullptr, 15, 12);
Melee melee4("Sword", 25, nullptr, 15, 15);
Melee melee5("Katana", 30, nullptr, 20, 18);
Melee melee6("Dagger", 35, nullptr, 20, 21);
Melee melee7("Spear", 40, nullptr, 25, 24);
Melee melee8("Halberd", 45, nullptr, 25, 27);
Melee melee9("Rapier", 50, nullptr, 25, 30);
Melee melee10("Chainsaw", 60, nullptr, 30, 33);

//"fireArm"
Firearm fireArm1("Desert Eagle", 10, nullptr, 10, 4);
Firearm fireArm2("Glock 17", 20, nullptr, 20, 8);
Firearm fireArm3("Shutgun", 30, nullptr, 25, 12);
Firearm fireArm4("Rifle", 40, nullptr, 25, 16);
Firearm fireArm5("Submachine", 50, nullptr, 30, 20);
Firearm fireArm6("Carbine", 60, nullptr, 30, 24);
Firearm fireArm7("Assault R", 70, nullptr, 35, 28);
Firearm fireArm8("Sniper R", 80, nullptr, 40, 28);
Firearm fireArm9("Machine gun", 90, nullptr, 40, 32);
Firearm fireArm10("FN SCAR", 100, nullptr, 45, 36);

// object of consumable class
// hp potion
HpPotion hpPotion1("FirstAid Kits", 5, nullptr, 2, 10);
HpPotion hpPotion2("Bandages", 10, nullptr, 5, 15);
HpPotion hpPotion3("Medkits", 15, nullptr, 10, 20);
HpPotion hpPotion4("CureCask", 20, nullptr, 20, 40);
HpPotion hpPotion5("Vitality", 35, nullptr, 30, 75);
HpPotion hpPotion6("EnduElixir", 50, nullptr, 50, 100);

// stamina potion
StaminaPotion staminaPotion1("Vigor Rush", 5, nullptr, 0, 10);
StaminaPotion staminaPotion2("Energy Surge", 10, nullptr, 0, 20);
StaminaPotion staminaPotion3("Turbo Tonic", 20, nullptr, 0, 30);
StaminaPotion staminaPotion4("ReviveRush", 35, nullptr, 0, 40);
StaminaPotion staminaPotion5("StamBlitz", 50, nullptr, 0, 50);

// power potion
PowerPotion powerPotion1("Savage Serum", 25, nullptr, 0, 1.1);
PowerPotion powerPotion2("Titan Tonic", 50, nullptr, 0, 1.2);
PowerPotion powerPotion3("Cataclysmic", 75, nullptr, 0, 1.3);
PowerPotion powerPotion4("Blitzkrieg", 100, nullptr, 0, 1.4);
PowerPotion powerPotion5("Valor Elixir", 150, nullptr, 0, 1.5);
