#pragma once
#include "headers.h"

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

    // setters
    void setName(const string newName) { name = newName; }
    void setPrice(int newPrice) { price = newPrice; }
    void setOwner(Character *newOwner) { owner = newOwner; }
    void setStamina(int newStamina) { stamina = newStamina; }
    virtual void setSpecial(int newSpecial) = 0;

    // others
    bool checkForUse();
    void takeStamina();
    virtual void useItem() = 0;
};

class Removable : public Item
{
public:
    Removable(string name, int price, Character *owner, int stamina);

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

    // setters
    void setSpecial(int newDamage) override { damage = newDamage; }

    // others
    void useItem();
};

class Consumable : public Removable
{
public:
    Consumable(string name, int price, Character *owner, int stamina);
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

    // setters
    void setSpecial(int newAmount) override { healingAmount = newAmount; }

    // others
    void useItem() override;
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

    // setters
    void setSpecial(int newAmount) override { boostAmount = newAmount; }

    // others
    void useItem() override;
};

class PowerPotion : public Consumable
{
protected:
    double empowerment;

public:
    PowerPotion(string name, int price, Character *owner, int stamina, double empowerment);

    // getters
    double getSpecial() const override { return empowerment; }

    // setters
    void setSpecial(int newEmpowerment) override { empowerment = newEmpowerment; }

    // others
    void useItem() override;
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

    // setters
    void setSpecial(int newdamage) override { damage = newdamage; }
};

class Melee : public Permanent
{
public:
    // constructor
    Melee(string name, int price, Character *owner, int stamina, int damage);
    // others
    void useItem() override;
};

class Firearm : public Permanent
{
public:
    // constructor
    Firearm(string name, int price, Character *owner, int stamina, int damage);
    // others
    void useItem() override;
};

// do not change the order of items declarations
// do not change the order of items declarations
// do not change the order of items declarations

// objects of Throwable class
Throwable throwable1("Grenade", 5, nullptr, 5, 5);
Throwable throwable2("Freezer Grenade", 10, nullptr, 10, 10);
Throwable throwable3("Acid Bottle", 20, nullptr, 15, 15);
Throwable throwable4("Molotov Cocktails", 30, nullptr, 20, 20);
Throwable throwable5("Taser Darts", 50, nullptr, 25, 25);
Throwable throwable6("Drone", 100, nullptr, 50, 150);
Throwable throwable7("Armored Personnel Carrier", 200, nullptr, 100, 300);
Throwable throwable8("Attack Helicopter", 300, nullptr, 100, 250);
Throwable throwable9("Fighter Jet", 400, nullptr, 150, 300);
Throwable throwable10("Gunship", 500, nullptr, 200, 400);

// objects of permanant class
// "melee"
Melee melee0("Punch", 0, nullptr, 0, 5);
Melee melee1("Knife", 10, nullptr, 5, 15);
Melee melee2("Axe", 10, nullptr, 10, 20);
Melee melee3("Nunchaku", 20, nullptr, 15, 30);
Melee melee4("Sword", 20, nullptr, 15, 30);
Melee melee5("Katana", 30, nullptr, 20, 40);
Melee melee6("Dagger", 30, nullptr, 20, 40);
Melee melee7("Spear", 40, nullptr, 25, 50);
Melee melee8("Halberd", 40, nullptr, 25, 50);
Melee melee9("Rapier", 45, nullptr, 25, 50);
Melee melee10("Chainsaw", 50, nullptr, 30, 60);

//"fireArm"
Firearm fireArm1("Desert Eagle", 10, nullptr, 10, 20);
Firearm fireArm2("Glock 17", 20, nullptr, 20, 40);
Firearm fireArm3("Shutgun", 30, nullptr, 25, 50);
Firearm fireArm4("Rifle", 40, nullptr, 25, 50);
Firearm fireArm5("Submachine gun", 50, nullptr, 30, 60);
Firearm fireArm6("Carbine", 60, nullptr, 30, 60);
Firearm fireArm7("Assault rifle", 70, nullptr, 35, 70);
Firearm fireArm8("Sniper rifle", 80, nullptr, 40, 80);
Firearm fireArm9("Machine gun", 90, nullptr, 40, 80);
Firearm fireArm10("FN SCAR", 100, nullptr, 45, 90);

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
