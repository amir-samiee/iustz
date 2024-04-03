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
    //virtual void runState() = 0;
    //virtual StateName nextState() = 0;
    bool canUse(string myItem);
    bool canKill();
};

class StartPoint : public States
{
public:
    StartPoint(Character *self) : States(self) {}
    //void runState();
    //StateName nextState();
};

class Attack : public States
{
public:
    Attack(Character *self) : States(self) {}
    //void runState();
    //StateName nextState();
};

class LowHp : public States
{
public:
    LowHp(Character *self) : States(self) {}
    //void runState();
    //StateName nextState();
};

class LowStamina : public States
{
public:
    LowStamina(Character *self) : States(self) {}
    //void runState();
    //StateName nextState();
};

class BoostPower : public States
{
public:
    BoostPower(Character *self) : States(self) {}
    //void runState();
    //StateName nextState();
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
    FSM(Character* self);
    void runTurn();
};