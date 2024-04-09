#include "headers.h"

// class States:
bool States::canUse(string name)
{
    return (self->getStamina()->getCurrentPoint() >= itemsMap[name]->getStamina());
}

bool States::canUse(vector<string> myItems)
{
    for (int i = 0; i < myItems.size(); ++i)
        if (canUse(myItems[i]))
            return 1;
    return 0;
}

bool States::canKill()
{
    vector<string> weapons = self->getBackpack()->getWeapons();
    int currentPoint = self->currentEnemy()->getHp()->getCurrentPoint();
    for (int i = 0; i < weapons.size(); i++)
        if (currentPoint <= itemsMap[weapons[i]]->getSpecial() && canUse(weapons[i]))
            return 1;
    return 0;
}

bool States::wastingPotion(vector<string> potions, Stat myStat)
{
    for (int i = 0; i < potions.size(); ++i)
        if (itemsMap[potions[i]]->getSpecial() > myStat.getMaxPoint() - myStat.getCurrentPoint())
            return 1;
    return 0;
}

bool States::wastingPotion(Item *potion, Stat myStat)
{
    if (dynamic_cast<HpPotion *>(potion) != nullptr)
    {
        if (myStat.getCurrentPoint() + potion->getSpecial() > 100.0)
            return 0;
    }
    if (dynamic_cast<StaminaPotion *>(potion) != nullptr)
    {
        if (myStat.getCurrentPoint() + potion->getSpecial() > myStat.getMaxPoint())
            return 0;
    }

    return 1;
}

string States::appropriateStamina(Stat myStamina)
{
    vector<string> enemyStaminaPotion = self->getBackpack()->getStaminaPotions();
    for (int i = enemyStaminaPotion.size() - 1; i >= 0; i--)
    {
        if (!wastingPotion(itemsMap[enemyStaminaPotion[i]], myStamina))
            return enemyStaminaPotion[i];
    }
    return "";
}

string States::appropriateWeapon(double powerBoost, Stat myStamina)
{
    string myWeapon;
    int maxDamage = 0;
    vector<string> weapons = self->getBackpack()->getWeapons();
    for (int i = 0; i < weapons.size(); i++)
    {
        int damage = itemsMap[weapons[i]]->getSpecial();
        if (dynamic_cast<Firearm *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= (1 + ((self->getFirearmLevel() - 1) / 6)) * powerBoost;
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() <= myStamina.getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
        if (dynamic_cast<Melee *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= (1 + ((self->getMeleeLevel() - 1) / 6)) * powerBoost;
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() <= myStamina.getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
        if (dynamic_cast<Throwable *>(itemsMap[weapons[i]]) != nullptr)
        {
            damage *= powerBoost;
            if (damage > maxDamage && itemsMap[weapons[i]]->getStamina() <= myStamina.getCurrentPoint())
            {
                maxDamage = damage;
                myWeapon = weapons[i];
            }
        }
    }
    
    return myWeapon;
}

StateName States::nextState()
{
    if (canKill())
    {
        return StateName::Attack;
    }
    else if (haveStaminaPotion() && (!wastingPotion(self->getBackpack()->getStaminaPotions(), *self->getStamina())))
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
    string myWeapon = appropriateWeapon(self->getPowerBoost(), *self->getStamina());
    itemsMap[myWeapon]->setOwner(self);
    itemsMap[myWeapon]->useItem();
}
// class LowHp:
void LowHp::runState()
{
    string hpName;
    vector<string> myHpPotion = self->getBackpack()->getHpPotions();
    if (self->getBackpack()->getStaminaPotions().size() > 0)
    {
        for (int i = myHpPotion.size() - 1; i >= 0; i--)
            if (itemsMap[myHpPotion[i]]->getStamina() < self->getStamina()->getCurrentPoint())
                hpName = myHpPotion[i];
    }
    else
    {
        for (int i = 0; i < myHpPotion.size(); ++i)
        {
            Stat myStat = *self->getHp();
            int newHpAmount = myStat.getCurrentPoint() + itemsMap[myHpPotion[i]]->getSpecial();
            if (newHpAmount > 50.0 && !wastingPotion(itemsMap[myHpPotion[i]], myStat))
                hpName = myHpPotion[i];
        }
    }
    itemsMap[hpName]->setOwner(self);
    itemsMap[hpName]->useItem();
}

// class LowStamina:
void LowStamina ::runState()
{
    Stat myStat = *self->getStamina();
    string staminaPotion = appropriateStamina(myStat);
    if (staminaPotion != "")
    {
        itemsMap[staminaPotion]->setOwner(self);
        itemsMap[staminaPotion]->useItem();
    }
}

// class BoostPower:
void BoostPower::runState()
{
    int maxDamage = 0;
    string myPowerPotion;
    vector<string> staminaPotions = player1->getBackpack()->getStaminaPotions();
    vector<string> powerPotions = player1->getBackpack()->getPowerPotions();
    for (int i = powerPotions.size() - 1; i >= 0; --i)
    {
        Stat newStamina = *player1->getStamina();
        newStamina.setCurrentPoint(newStamina.getCurrentPoint() - itemsMap[powerPotions[i]]->getStamina());
        string staminaItem = appropriateStamina(newStamina);
        if (staminaItem != "")
            newStamina.setCurrentPoint(newStamina.getCurrentPoint() + itemsMap[staminaItem]->getSpecial());

        string weapon = appropriateWeapon(itemsMap[powerPotions[i]]->getSpecial(), newStamina);

        int currentDamage = itemsMap[weapon]->getSpecial() * itemsMap[powerPotions[i]]->getSpecial();

        if (dynamic_cast<Firearm *>(itemsMap[weapon]) != nullptr)
            currentDamage *= self->getFirearmLevel();

        else if (dynamic_cast<Melee *>(itemsMap[weapon]) != nullptr)
            currentDamage *= self->getMeleeLevel();

        if (currentDamage > maxDamage)
        {
            maxDamage = currentDamage;
            myPowerPotion = powerPotions[i];
        }
    }
    itemsMap[myPowerPotion]->setOwner(self);
    itemsMap[myPowerPotion]->useItem();
}

// class FSM:
FSM::FSM(Character *self) : self(self)
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

FSM::~FSM()
{
    deletePtr(startPoint);
    deletePtr(attack);
    deletePtr(lowHp);
    deletePtr(lowStamina);
    deletePtr(boostPower);
}

void FSM::runTurn()
{
    States *current = statesMap[currentState];
    current->setSelf(self);
    current->runState();
    currentState = current->nextState();
}