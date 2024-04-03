#include "headers.h"

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
    //statesMap[currentState]->runState();
    //currentState = statesMap[currentState]->nextState();
}