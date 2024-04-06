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
            return 1;
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

bool States::wastingPotion(Item *potion){
    if(dynamic_cast< HpPotion* > (potion) != nullptr){
        if(self->getHp()->getCurrentPoint() + potion->getSpecial() > 100.0 )
            return 0;}
    if(dynamic_cast< StaminaPotion* > (potion) != nullptr){
        if(self->getStamina()->getCurrentPoint() + potion->getSpecial() > self->getStamina()->getMaxPoint())
        return 0;}
    
    return 1;
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
void Attack::runState()
{
    string myWeapon;
    int maxDamage;
    vector<string> weapons = self->getBackpack()->getWeapons();
    for (int i = 0; i < weapons.size(); i++)
    {
        int damage = itemsMap[weapons[i]]->getSpecial();
        if (dynamic_cast<Firearm *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= self->getFirearmLevel() * self->getPowerBoost();
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() < self->getStamina()->getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
        if (dynamic_cast<Melee *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= self->getMeleeLevel() * self->getPowerBoost();
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() < self->getStamina()->getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
        if (dynamic_cast<Throwable *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= self->getPowerBoost();
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() < self->getStamina()->getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
    }
    itemsMap[myWeapon]->setOwner(self);
    itemsMap[myWeapon]->useItem();
}
// class LowHp:
void LowHp::runState()
{
    string hpName;
    vector<string>enemyHpPotion = self->getBackpack()->getHpPotions();
    if(self->getBackpack()->getStaminaPotions().size() > 0){
        for(int i = enemyHpPotion.size()-1 ; i>=0 ; i--){
            if (itemsMap[enemyHpPotion[i]]->getStamina() < self->getStamina()->getCurrentPoint())
                itemsMap[enemyHpPotion[i]]->useItem();
        }
    }
    else
    {
        for (int i = 0 ; i < enemyHpPotion.size(); i++)
        {
            if (self->getHp()->getCurrentPoint() + itemsMap[enemyHpPotion[i]]->getSpecial() > 50.0 && !wastingPotion(itemsMap[enemyHpPotion[i]]))
                itemsMap[enemyHpPotion[i]]->useItem();
        }
        
    }
}

// class LowStamina:
void LowStamina :: runState(){
    vector<string>enemyStaminaPotion = self->getBackpack()->getStaminaPotions();
        for (int i =  enemyStaminaPotion.size()-1 ; i >= 0; i--)
        {
            if(!wastingPotion(itemsMap[enemyStaminaPotion[i]]))
            itemsMap[enemyStaminaPotion[i]]->useItem() ;
        }
}
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