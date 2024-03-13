#include <iostream>
using namespace std;

class character; // Forward declaration

class Items
{
public:
    string name;
    int price;
    character *owner;
    int level = 0;
    int stamina = 0;

    virtual void useItem() {}

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
    Items(string name, int price, character *owner, int level, int stamina)
    {
        this->name = name;
        this->price = price;
        this->owner = owner;
        this->level = level;
        this->stamina = stamina;
    }
  Items() = default;
};

class Throwable : public Items
{
public:
    int damage;

    void useItem() override {}

    // constructor:
    Throwable(string name, int price, character *owner, int level, int stamina, int damage) : Items(name, price, owner, level, stamina)
    {
        this->damage = damage;
    }
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

class Consumable : public virtual Items
{

protected :
     virtual void removeFromBackpack() {}

};

class Permanent : public Items
{
public:
    int damage;
    string type;

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
    // constructor:
    Permanent(string name, int price, character *owner, int level, int stamina, int damage, string type) : Items(name, price, owner, level, stamina)
    {
        this->damage = damage;
        this->type = type;
    }
};

class HpPotion : public Consumable
{
public:
    int healingAmount;

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
    HpPotion(string name, int price, character *owner, int level, int stamina, int healingAmount) : Items(name, price, owner, level, stamina)
    {
        this->healingAmount = healingAmount;
    }
};

class StaminaPotion : public Consumable
{
public:
    int boostAmount;

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

    StaminaPotion(string name, int price, character *owner, int level, int stamina, int boostAmount) : Items(name, price, owner, level, stamina)
    {
        this->boostAmount = boostAmount;
    }
};

class PowerPotion : public Consumable
{
public:
    double empowerment;

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
    PowerPotion(string name, int price, character *owner, int level, int stamina, double empowerment) : Items(name, price, owner, level, stamina)
    {
        this->empowerment = empowerment;
    }
};

// objects of Throwable class

Throwable Throwable1("Grenade", 5, nullptr, 0, 5, 5);
Throwable Throwable2("Freezer Grenade", 10, nullptr, 1, 10, 10);
Throwable Throwable3("acid Bottle", 20, nullptr, 15, 1, 15);
Throwable Throwable4("Molotov Cocktails", 30, nullptr, 20, 2, 20);
Throwable Throwable5("Taser Darts", 50, nullptr, 3, 25, 25);
Throwable Throwable6("Drone", 100, nullptr, 3, 50, 150);
Throwable Throwable7("Armored Personnel Carrier", 200, nullptr, 4, 100, 300);
Throwable Throwable8("Attack Helicopter", 300, nullptr, 4, 200, 500);
Throwable Throwable9("Fighter Jet", 400, nullptr, 5, 300, 600);
Throwable Throwable10("Gunship", 500, nullptr, 5, 450, 900);

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

//"firearm"
Permanent firearm1("Desert Eagle", 10, nullptr, 1, 10, 20, "firearm");
Permanent firearm2("Glock 17", 20, nullptr, 1, 20, 40, "firearm");
Permanent firearm3("Shutgun", 30, nullptr, 2, 30, 60, "firearm");
Permanent firearm4("Rifle", 40, nullptr, 2, 40, 80, "firearm");
Permanent firearm5("Submachine gun", 50, nullptr, 3, 50, 100, "firearm");
Permanent firearm6("Carbine", 60, nullptr, 3, 60, 120, "firearm");
Permanent firearm7("Assault rifle", 70, nullptr, 4, 70, 140, "firearm");
Permanent firearm8("Sniper rifle", 80, nullptr, 4, 80, 160, "firearm");
Permanent firearm9("Machine gun", 90, nullptr, 5, 90, 180, "firearm");
Permanent firearm10("FN SCAR", 100, nullptr, 5, 100, 200, "firearm");

// object of consumable class
// hp potion
HpPotion hppotion1("First Aid Kits", 5, nullptr, 0, 0, 5);
HpPotion hppotion2("Bandages", 10, nullptr, 1, 0, 10);
HpPotion hppotion3("Medkits", 15, nullptr, 2, 0, 20);
HpPotion hppotion4("Healing Salve", 20, nullptr, 3, 0, 40);
HpPotion hppotion5("Potion of Vitality", 35, nullptr, 4, 0, 75);
HpPotion hppotion6("Diamond Elixir", 50, nullptr, 5, 0, 100);

// stamina potion
StaminaPotion staminapotion1("Vigor Rush", 5, nullptr, 1, 0, 10);
StaminaPotion staminapotion2("Energy Surge", 10, nullptr, 2, 0, 20);
StaminaPotion staminapotion3("Turbo Tonic", 20, nullptr, 3, 0, 30);
StaminaPotion staminapotion4("Endurance Elixir", 35, nullptr, 4, 0, 40);
StaminaPotion staminapotion5("Stamina Spark", 50, nullptr, 5, 0, 50);

// power potion
PowerPotion powerpotion1("Savage Serum", 5, nullptr, 1, 0, 1.5);
PowerPotion powerpotion2("Titan Tonic", 25, nullptr, 2, 0, 2);
PowerPotion powerpotion3("Cataclysmic", 125, nullptr, 3, 0, 2.5);
PowerPotion powerpotion4("Blitzkrieg Booster", 225, nullptr, 4, 0, 3);
PowerPotion powerpotion5("Eternal Valor Elixir", 500, nullptr, 5, 0, 5);
