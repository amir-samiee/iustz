#include "headers.h"

enum class StateName
{
    StartPoint,
    Attack,
    LowHp,
    LowStamina,
    BoostPower
};

class States
{
protected:
    Character *self;

public:
    States(Character *self) : self(self) {}

    // conditions:
    bool canUse(string myItem); //have enough stamina to use an item
    bool canUse(vector<string> myItems); //have enough stamina to use a type of item
    bool canKill();
    bool lowStamina() { return self->getStamina()->getCurrentPoint() < 0.1 * self->getStamina()->getMaxPoint(); }
    bool lowHp() { return self->getHp()->getCurrentPoint() < 0.3 * self->getHp()->getMaxPoint(); }
    bool haveStaminaPotion() { return !self->getBackpack()->getStaminaPotions().empty(); }
    bool haveHpPotion() { return !self->getBackpack()->getHpPotions().empty(); }
    bool havePowerPotion() { return !self->getBackpack()->getPowerPotions().empty(); }
    bool highStamina() { return self->getStamina()->getCurrentPoint() > 0.5 * self->getStamina()->getMaxPoint(); }
    bool wastingPotion(vector<string> potions, Stat myStat); // check if there is a potion of a type that wont go to waste
    bool wastingPotion(Item *potion, Stat myStat); // check if a certain potion wont go to waste
    string appropriateStamina(Stat myStat);
    string appropriateWeapon(double powerBoost, Stat myStamina);

    virtual void runState() {}
    virtual StateName nextState();
};

class StartPoint : public States
{
public:
    StartPoint(Character *self) : States(self) {}
};

class Attack : public States
{
public:
    Attack(Character *self) : States(self) {}
    void runState();
    StateName nextState() { return StateName::StartPoint; }
};

class LowHp : public States
{
public:
    LowHp(Character *self) : States(self) {}
    void runState();
    // StateName nextState();
};

class LowStamina : public States
{
public:
    LowStamina(Character *self) : States(self) {}
    void runState();
    // StateName nextState();
};

class BoostPower : public States
{
public:
    BoostPower(Character *self) : States(self) {}
    void runState();
    // StateName nextState();
};

class FSM
{
protected:
    StateName currentState;
    StartPoint *startPoint;
    Attack *attack;
    LowHp *lowHp;
    LowStamina *lowStamina;
    BoostPower *boostPower;
    map<StateName, States *> statesMap;

public:
    FSM(Character *self);
    FSM() = default;
    ~FSM();
    void runTurn();
    StateName getCurrentState() { return currentState; }
};