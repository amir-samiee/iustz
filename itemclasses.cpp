#include <iostream>
using namespace std;

class character; // Forward declaration

class Item
{
protected:
    string name;
    int price;
    character *owner;
    int level = 0;
    int stamina = 0;

public:
    Item(string name, int price, character *owner, int level, int stamina)
    {
        this->name = name;
        this->price = price;
        this->owner = owner;
        this->level = level;
        this->stamina = stamina;
    }
    Item() = default;
    virtual void useItem() = 0;

    // Getter for 'name'
    string getName() const
    {
        return name;
    }

    // Setter for 'name'
    void setName(const string &newName)
    {
        name = newName;
    }

    // Getter for 'price'
    int getPrice() const
    {
        return price;
    }

    // Setter for 'price'
    void setPrice(int newPrice)
    {
        price = newPrice;
    }

    // Getter for 'owner'
    character *getOwner() const
    {
        return owner;
    }

    // Setter for 'owner'
    void setOwner(character *newOwner)
    {
        owner = newOwner;
    }
};

class Throwable : public Item
{
protected:
    int damage;

public:
    // constructor:
    Throwable(string name, int price, character *owner, int level, int stamina, int damage) : Item(name, price, owner, level, stamina)
    {
        this->damage = damage;
    }
    void useItem() override {}

    // Getter for 'damage'
    int getDamage() const
    {
        return damage;
    }

    // Setter for 'damage'
    void setDamage(int newDamage)
    {
        damage = newDamage;
    }
};

class Consumable : public Item
{

protected:
    virtual void removeFromBackpack() {}

public:
    Consumable(string name, int price, character *owner, int level, int stamina) : Item(name, price, owner, level, stamina) {}
};

class Permanent : public Item
{
protected:
    int damage;
    string type;

public:
    // constructor:
    Permanent(string name, int price, character *owner, int level, int stamina, int damage, string type) : Item(name, price, owner, level, stamina)
    {
        this->damage = damage;
        this->type = type;
    }
    void useItem() override {}

    // Getter for 'damage'
    int getDamage() const
    {
        return damage;
    }

    // Setter for 'damage'
    void setDamage(int newdamage)
    {
        damage = newdamage;
    }

    // Getter for 'type'
    string getType() const
    {
        return type;
    }

    // Setter for 'type'
    void setType(const string &newType)
    {
        type = newType;
    }
};

class HpPotion : public Consumable
{
protected:
    int healingAmount;

public:
    HpPotion(string name, int price, character *owner, int level, int stamina, int healingAmount) : Consumable(name, price, owner, level, stamina)
    {
        this->healingAmount = healingAmount;
    }
    void useItem() override {}
    int heal(int hp)
    {
        // Implementation for healing logic
        // ...
        return 0; // Placeholder return value
    }

    // Getter for 'healingAmount'
    int getHealingAmount() const
    {
        return healingAmount;
    }

    // Setter for 'healingAmount'
    void setHealingAmount(int newAmount)
    {
        healingAmount = newAmount;
    }
};

class StaminaPotion : public Consumable
{
protected:
    int boostAmount;

public:
    StaminaPotion(string name, int price, character *owner, int level, int stamina, int boostAmount) : Consumable(name, price, owner, level, stamina)
    {
        this->boostAmount = boostAmount;
    }
    void useItem() override {}
    int boost()
    {
        // Implementation for stamina boost logic
        // ...
        return 0; // Placeholder return value
    }

    // Getter for 'boostAmount'
    int getBoostAmount() const
    {
        return boostAmount;
    }

    // Setter for 'boostAmount'
    void setBoostAmount(int newAmount)
    {
        boostAmount = newAmount;
    }
};

class PowerPotion : public Consumable
{
protected:
    double empowerment;

public:
    PowerPotion(string name, int price, character *owner, int level, int stamina, double empowerment) : Consumable(name, price, owner, level, stamina)
    {
        this->empowerment = empowerment;
    }
    void useItem() override {}
    double increaser()
    {
        // Implementation for power increase logic
        // ...
        return 0; // Placeholder return value
    }

    // Getter for 'empowerment'
    double getEmpowerment() const
    {
        return empowerment;
    }

    // Setter for 'empowerment'
    void setEmpowerment(double newEmpowerment)
    {
        empowerment = newEmpowerment;
    }
};

// objects of Throwable class

Throwable throwable1("Grenade", 5, nullptr, 0, 5, 5);
Throwable throwable2("Freezer Grenade", 10, nullptr, 1, 10, 10);
Throwable throwable3("acid Bottle", 20, nullptr, 15, 1, 15);
Throwable throwable4("Molotov Cocktails", 30, nullptr, 20, 2, 20);
Throwable throwable5("Taser Darts", 50, nullptr, 3, 25, 25);
Throwable throwable6("Drone", 100, nullptr, 3, 50, 150);
Throwable throwable7("Armored Personnel Carrier", 200, nullptr, 4, 100, 300);
Throwable throwable8("Attack Helicopter", 300, nullptr, 4, 200, 500);
Throwable throwable9("Fighter Jet", 400, nullptr, 5, 300, 600);
Throwable throwable10("Gunship", 500, nullptr, 5, 450, 900);

// objects of permanant class
// "melee"
Permanent melee1("Punch", 0, nullptr, 0, 5, 10, "melee");
Permanent melee2("Axe", 10, nullptr, 1, 10, 20, "melee");
Permanent melee3("Nunchaku", 50, nullptr, 1, 20, 10, "melee");
Permanent melee4("Sword", 20, nullptr, 2, 20, 40, "melee");
Permanent melee5("Katana", 25, nullptr, 2, 20, 40, "melee");
Permanent melee6("Dagger", 30, nullptr, 3, 30, 60, "melee");
Permanent melee7("Spear", 35, nullptr, 3, 30, 60, "melee");
Permanent melee8("Halberd", 40, nullptr, 4, 40, 80, "melee");
Permanent melee9("Rapier", 45, nullptr, 4, 40, 80, "melee");
Permanent melee10("Chainsaw", 50, nullptr, 5, 50, 100, "melee");

//"fireArm"
Permanent fireArm1("Desert Eagle", 10, nullptr, 1, 10, 20, "fireArm");
Permanent fireArm2("Glock 17", 20, nullptr, 1, 20, 40, "fireArm");
Permanent fireArm3("Shutgun", 30, nullptr, 2, 30, 60, "fireArm");
Permanent fireArm4("Rifle", 40, nullptr, 2, 40, 80, "fireArm");
Permanent fireArm5("Submachine gun", 50, nullptr, 3, 50, 100, "fireArm");
Permanent fireArm6("Carbine", 60, nullptr, 3, 60, 120, "fireArm");
Permanent fireArm7("Assault rifle", 70, nullptr, 4, 70, 140, "fireArm");
Permanent fireArm8("Sniper rifle", 80, nullptr, 4, 80, 160, "fireArm");
Permanent fireArm9("Machine gun", 90, nullptr, 5, 90, 180, "fireArm");
Permanent fireArm10("FN SCAR", 100, nullptr, 5, 100, 200, "fireArm");

// object of consumable class
// hp potion
HpPotion hpPotion1("First Aid Kits", 5, nullptr, 0, 0, 5);
HpPotion hpPotion2("Bandages", 10, nullptr, 1, 0, 10);
HpPotion hpPotion3("Medkits", 15, nullptr, 2, 0, 20);
HpPotion hpPotion4("Healing Salve", 20, nullptr, 3, 0, 40);
HpPotion hpPotion5("Potion of Vitality", 35, nullptr, 4, 0, 75);
HpPotion hpPotion6("Diamond Elixir", 50, nullptr, 5, 0, 100);

// stamina potion
StaminaPotion staminaPotion1("Vigor Rush", 5, nullptr, 1, 0, 10);
StaminaPotion staminaPotion2("Energy Surge", 10, nullptr, 2, 0, 20);
StaminaPotion staminaPotion3("Turbo Tonic", 20, nullptr, 3, 0, 30);
StaminaPotion staminaPotion4("Endurance Elixir", 35, nullptr, 4, 0, 40);
StaminaPotion staminaPotion5("Stamina Spark", 50, nullptr, 5, 0, 50);

// power potion
PowerPotion powerPotion1("Savage Serum", 5, nullptr, 1, 0, 1.5);
PowerPotion powerPotion2("Titan Tonic", 25, nullptr, 2, 0, 2);
PowerPotion powerPotion3("Cataclysmic", 125, nullptr, 3, 0, 2.5);
PowerPotion powerPotion4("Blitzkrieg Booster", 225, nullptr, 4, 0, 3);
PowerPotion powerPotion5("Eternal Valor Elixir", 500, nullptr, 5, 0, 5);
