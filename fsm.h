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
    // virtual void runState() = 0;
    // virtual StateName nextState() = 0;
    bool canUse(string myItem);
    bool canKill();
    bool lowStamina() { return self->getStamina()->getCurrentPoint() < 0.1*self->getStamina()->getMaxPoint(); }
    bool lowHp() { return self->getHp()->getCurrentPoint() < 0.3*self->getHp()->getMaxPoint(); }
    bool haveStaminaPotion() { return !self->getBackpack()->getStaminaPotions().empty(); }
    bool haveHpPotion() { return !self->getBackpack()->getHpPotions().empty(); }
    bool highStamina() { return self->getStamina()->getCurrentPoint() > 0.5*self->getStamina()->getMaxPoint(); }
    bool wastingPotion(string type);
};

class StartPoint : public States
{
public:
    StartPoint(Character *self) : States(self) {}
    // void runState();
    // StateName nextState();
};

class Attack : public States
{
public:
    Attack(Character *self) : States(self) {}
    // void runState();
    // StateName nextState();
};

class LowHp : public States
{
public:
    LowHp(Character *self) : States(self) {}
    // void runState();
    // StateName nextState();
};

class LowStamina : public States
{
public:
    LowStamina(Character *self) : States(self) {}
    // void runState();
    // StateName nextState();
};

class BoostPower : public States
{
public:
    BoostPower(Character *self) : States(self) {}
    // void runState();
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
    void runTurn();
};