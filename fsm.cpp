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
        if (wastingPotion(itemsMap[potions[i]] , myStat))
            return 1;
    return 0;
}

bool States::wastingPotion(Item *potion, Stat myStat)
{
    return myStat.getCurrentPoint() + potion->getSpecial() - myStat.getMaxPoint() > potion->getSpecial()*0.2;
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
    else if (lowHp() && haveHpPotion() && canUse(self->getBackpack()->getHpPotions()) && (!wastingPotion(self->getBackpack()->getHpPotions(), *self->getHp())))
    {
        return StateName::LowHp;
    }
    else if (havePowerPotion() && canUse(self->getBackpack()->getPowerPotions()) && !wastingPowerPotion)
    {
        return StateName::BoostPower;
    }
    return StateName::Attack;
}

// class StartPoint:
void StartPoint::runState() { wastingPowerPotion = 0; }

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
    string hpName = "";
    vector<string> myHpPotions = self->getBackpack()->getHpPotions();
    if (!self->getBackpack()->getStaminaPotions().size() > 0)
    {
        for (int i = 0; i < myHpPotions.size(); ++i)
        {
            Stat myStat = *self->getHp();
            int newHpAmount = myStat.getCurrentPoint() + itemsMap[myHpPotions[i]]->getSpecial();
            if (newHpAmount > 0.4*myStat.getMaxPoint() && !wastingPotion(itemsMap[myHpPotions[i]], myStat))
                hpName = myHpPotions[i];
        }
    }
    if (hpName == "")
    {
        for (int i = myHpPotions.size() - 1; i >= 0; i--)
            if (canUse(myHpPotions[i]))
                if (!wastingPotion(itemsMap[myHpPotions[i]], *self->getHp()))
                    hpName = myHpPotions[i];
    }
    if (hpName != "")
    {
        itemsMap[hpName]->setOwner(self);
        itemsMap[hpName]->useItem();
    }
    else
        cerr << "error in hp state";
}

// class LowStamina:
void LowStamina ::runState()
{
    string staminaPotion = appropriateStamina(*self->getStamina());
    if (staminaPotion != "")
    {
        itemsMap[staminaPotion]->setOwner(self);
        itemsMap[staminaPotion]->useItem();
    }
}

// class BoostPower:
void BoostPower::runState()
{
    Item *beforeBoostWeapon = itemsMap[appropriateWeapon(self->getPowerBoost(), *self->getStamina())];
    int maxDamage = beforeBoostWeapon->getSpecial() * self->getPowerBoost();

    if (dynamic_cast<Firearm *>(beforeBoostWeapon) != nullptr)
        maxDamage *= self->getFirearmLevel();
    else if (dynamic_cast<Melee *>(beforeBoostWeapon) != nullptr)
        maxDamage *= self->getMeleeLevel();

    string myPowerPotion = "";
    vector<string> staminaPotions = self->getBackpack()->getStaminaPotions();
    vector<string> powerPotions = self->getBackpack()->getPowerPotions();
    for (int i = powerPotions.size() - 1; i >= 0; --i)
    {
        Stat newStamina = *self->getStamina();
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
    if (myPowerPotion != "")
    {
        itemsMap[myPowerPotion]->setOwner(self);
        itemsMap[myPowerPotion]->useItem();
        return;
    }
    wastingPowerPotion = 1;
}

// class FSM:
FSM::FSM(Character *self) : self(self) {}

FSM::~FSM()
{
    delete startPoint;
    delete attack;
    delete lowHp;
    delete lowStamina;
    delete boostPower;
}

void FSM::runTurn()
{
    States *current = statesMap[currentState];
    current->setSelf(self);
    current->runState();
    currentState = current->nextState();
}