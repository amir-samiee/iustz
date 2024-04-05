#include "headers.h"

// class States:
bool States::canUse(string name)
{
    if (self->getStamina()->getCurrentPoint() >= itemsMap[name]->getStamina())
    {
        return 1;
    }
    return 0;
}
bool States::canUse(vector<string> myItems)
{
    for (int i = 0; i < myItems.size(); ++i)
    {
        if (canUse(myItems[i]))
            return 1;
    }
    return 0;
}

bool States::canKill()
{
    vector<string> weapons = self->getBackpack()->getWeapons();
    int currentPoint = self->getWave()[0]->getHp()->getCurrentPoint();
    for (int i = 0; i < weapons.size(); i++)
        if (currentPoint <= itemsMap[weapons[i]]->getSpecial() && canUse(weapons[i]))
        {
            return 1;
        }
    return 0;
}

bool States::wastingPotion(string type)
{
    vector<string> potions;
    Stat *myStat;
    if (type == "stamina")
    {
        potions = self->getBackpack()->getStaminaPotions();
        myStat = self->getStamina();
    }
    else if (type == "hp")
    {
        potions = self->getBackpack()->getHpPotions();
        myStat = self->getHp();
    }
    else
        cout << "invalid type in fsm.cpp/States::wastingPotion()";

    for (int i = 0; i < potions.size(); ++i)
    {
        if (itemsMap[potions[i]]->getSpecial() > myStat->getMaxPoint() - myStat->getCurrentPoint())
            return 1;
    }
    return 0;
}

StateName States::nextState()
{
    if (canKill())
    {
        return StateName::Attack;
    }
    else if (haveStaminaPotion() && (!wastingPotion("stamina")))
    {
        return StateName::LowStamina;
    }
    else if (lowHp() && haveHpPotion() && canUse(self->getBackpack()->getHpPotions()))
    {
        return StateName::LowHp;
    }
    else if (highStamina() && havePowerPotion() && canUse(self->getBackpack()->getPowerPotions()))
    {
        return StateName::BoostPower;
    }
    return StateName::Attack;
}

// class Attack:
// class LowHp:
// class LowStamina:
// class BoostPower:

// class FSM:
FSM::FSM(Character *self)
{
    currentState = StateName::StartPoint;
    startPoint = new StartPoint(self);
    attack = new Attack(self);
    lowHp = new LowHp(self);
    lowStamina = new LowStamina(self);
    boostPower = new BoostPower(self);
    map<StateName, States *> statesMap = {
        {StateName::StartPoint, startPoint},
        {StateName::Attack, attack},
        {StateName::LowHp, lowHp},
        {StateName::LowStamina, lowStamina},
        {StateName::BoostPower, boostPower}};
}

void FSM::runTurn()
{
    statesMap[currentState]->runState();
    currentState = statesMap[currentState]->nextState();
}