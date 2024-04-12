#pragma once
#include "headers.h"

void Stat::setCurrentPoint(int newValue)
{
    if (newValue > maxPoint)
        currentPoint = maxPoint;
    else if (newValue < 0)
        currentPoint = 0;
    else
        currentPoint = newValue;
}

void Stat::loadStat(json data)
{
    basePoint = data["basePoint"];
    maxPoint = data["maxPoint"];
}

json Stat::dumpStat()
{
    json data;
    data["basePoint"] = basePoint;
    data["maxPoint"] = maxPoint;
    return data;
}

void Stat::savePoint()
{
    lastSavedPoint = currentPoint;
}

void Stat::loadPoint()
{
    currentPoint = lastSavedPoint;
    lastSavedPoint = 0;
}

void Stat::fill()
{
    currentPoint = maxPoint;
}

int Stat::level()
{
    return (((maxPoint - basePoint) / 30) + 1);
}

///////////////////////////////////////////////////////////////

Character *Player::currentEnemy(bool isViewd)
{
    if (!currentWave.empty())
        return currentWave[0];
    else
    {
        if (isViewd)
            cout << yellow << "empty wave!!!" << reset << endl;
        return nullptr;
    }
}

bool Player::isAlive() { return hp.getCurrentPoint() > 0; }
int Player::level() { return (firearmLevel + meleeLevel + hp.level() + stamina.level()) / 4; }
void Player::takeDamage(int takenDamage)
{
    int newPoint = hp.getCurrentPoint() - takenDamage;
    hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
void Player::display(bool isFighting)
{
    cout << green << "Name: " << reset << name << left << endl
         << cyan << "HP: " << reset << setw(8) << hp.getCurrentPoint()
         << cyan << "Stamina: " << reset << setw(6) << stamina.getCurrentPoint()
         << cyan << "Power Boost: " << reset << setw(5) << powerBoost
         << cyan << "Firearm Level: " << reset << setw(6) << firearmLevel
         << cyan << "Melee Level: " << reset << setw(5) << meleeLevel
         << reset << endl;
}

void Player::addRewardCoins(int addedCoins) { rewardCoins += addedCoins; }

void Player::loadPlayer(json data)
{
    name = data["name"];
    age = data["age"];
    gender = data["gender"];
    backpack.loadStorage(data["backpack"]);
    hp.loadStat(data["hp"]);
    stamina.loadStat(data["stamina"]);
    firearmLevel = data["firearmLevel"];
    meleeLevel = data["meleeLevel"];
    coins = data["coins"];
    inventory.loadStorage(data["inventory"]);
    humanLevels = data["humanLevels"];
    zombieLevels = data["zombieLevels"];
}

json Player::dumpPlayer()
{
    json data;
    data["name"] = name;
    data["age"] = age;
    data["gender"] = gender;
    data["backpack"] = backpack.dumpStorage();
    data["hp"] = hp.dumpStat();
    data["stamina"] = stamina.dumpStat();
    data["firearmLevel"] = firearmLevel;
    data["meleeLevel"] = meleeLevel;
    data["coins"] = coins;
    data["inventory"] = inventory.dumpStorage();
    data["humanLevels"] = humanLevels;
    data["zombieLevels"] = zombieLevels;
    return data;
}

Player::Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
               int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins, Storage inventory, int humanLevels, int zombieLevels)
    : name(name), age(age), gender(gender), backpack(backpack), hp(hp), stamina(stamina), firearmLevel(firearmLevel), meleeLevel(meleeLevel),
      powerBoost(powerBoost), currentWave(currentWave), coins(coins), inventory(inventory), humanLevels(humanLevels), zombieLevels(zombieLevels)
{
    this->backpack.addItem("Punch");
}

Player::Player(const Player &other)
{
    *this = other;
}
////////////////////////////////////////////////////////////////////

MVC::EnemyModel::EnemyModel(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                            int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : name(name), age(age), gender(gender), backpack(backpack), hp(hp), stamina(stamina), firearmLevel(firearmLevel),
      meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins) {}

bool MVC::EnemyModel::isAlive() { return hp.getCurrentPoint() > 0; }

void MVC::EnemyView::display(const EnemyModel &model, bool isFighting)
{
    if (isFighting)
    {
        cout << red << "Name: " << reset << model.name << left << endl
             << magenta << "HP: " << reset << setw(8) << model.hp.getCurrentPoint()
             << magenta << "Stamina: " << reset << setw(6) << model.stamina.getCurrentPoint()
             << magenta << "Power Boost: " << reset << setw(5) << model.powerBoost
             << magenta << "Firearm Level: " << reset << setw(6) << model.firearmLevel
             << magenta << "Melee Level: " << reset << setw(5) << model.meleeLevel
             << magenta << "\nBackpack:  ";
        for (auto t : vector<vector<string>>{model.backpack.getWeapons(),
                                             model.backpack.getHpPotions(),
                                             model.backpack.getPowerPotions(),
                                             model.backpack.getStaminaPotions()})
            for (auto i : t)
            {
                Item *itemPtr = itemsMap[i];
                cout << yellow << i << red + "(" << itemPtr->getType()[0] << "/" << itemPtr->getSpecial() << ")  " + reset;
            }

        cout << reset << endl;
    }
    else
        cout << gray
             << "Name: " << model.name << left << endl
             << "HP: " << setw(8) << model.hp.getCurrentPoint()
             << "Stamina: " << setw(6) << model.stamina.getCurrentPoint()
             << "Power Boost: " << setw(5) << model.powerBoost
             << "Firearm Level: " << setw(6) << model.firearmLevel
             << "Melee Level: " << setw(5) << model.meleeLevel
             << reset << endl;
}

void MVC::EnemyController::takeDamage(int takenDamage)
{
    int newPoint = model->hp.getCurrentPoint() - takenDamage;
    model->hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}

// this function used to be called in Mission::enemyTurn() but we decided to transfer the code to that function itself.
// althoug the function will stay here due to the possibility of further need.
bool MVC::EnemyController::move()
{
    fsm.setSelf(self);
    StateName currentState = fsm.getCurrentState();
    fsm.runTurn();
    return (currentState != StateName::Attack);
}

void MVC::EnemyController::die()
{
    Player *myplayer = dynamic_cast<Player *>(self->currentEnemy());
    // setting rewards:
    transfer(self->getBackpack(), myplayer->getRewardItems());
    player1->addRewardCoins(model->coins);

    // removing enemy from wave:
    vector<Character *> updatedWave = self->currentEnemy()->getWave();
    for (int i = 0; i < updatedWave.size(); i++)
    {
        if (updatedWave[i] == dynamic_cast<Character *>(self))
        {
            updatedWave.erase(updatedWave.begin() + i);
            break;
        }
    }
    self->currentEnemy()->setWave(updatedWave);
    Mission::eventsLog.push_back(model->name + magenta + " (enemy) " + red + "died" + reset);
}

void MVC::SpecialEnemyController::takeDamage(int takenDamage)
{
    int newPoint = model->hp.getCurrentPoint() - (takenDamage / ((rand() % 3) + 1));
    model->hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}

////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
             int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : model(new MVC::EnemyModel(name, age, gender, backpack, hp, stamina, firearmLevel,
                                meleeLevel, powerBoost, currentWave, coins)),
      view(new MVC::EnemyView)
{
    controller = new MVC::EnemyController(model, view, this);
    model->backpack.addItem("Punch");
}

Enemy::~Enemy()
{
    delete model;
    delete view;
    delete controller;
}

Character *Enemy::currentEnemy(bool isViewd)
{
    if (!model->currentWave.empty())
        return model->currentWave[0];
    else
    {
        if (isViewd)
            cout << yellow << "empty wave!!!" << reset << endl;
        return nullptr;
    }
}

bool Enemy::isAlive() { return model->isAlive(); }
int Enemy::level() { return (model->firearmLevel + model->meleeLevel + model->hp.level() + model->stamina.level()) / 4; }
void Enemy::takeDamage(int damage) { controller->takeDamage(damage); }

HumanEnemy::HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
                       Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : Enemy(name, age, gender, backpack, hp,
            stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

ZombieEnemy::ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                         Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : Enemy(name, age, gender, backpack, hp,
            stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}
void ZombieEnemy::takeDamage(int damage) { controller->takeDamage(damage); }

SpecialZombie::SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, double powerBoost, vector<Character *> currentWave, int coins)
    : ZombieEnemy(name, age, gender, backpack, hp, stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins)
{
    delete controller;
    controller = new MVC::SpecialEnemyController(model, view, this);
}

void SpecialZombie::takeDamage(int damage) { this->controller->takeDamage(damage); }

////////////////////////////////////////////////////////////////

// this function used to be called in Mission::playerTurn() but we decided to transfer the code to that function itself.
// although the function will stay here due to the possibility of further need.
bool Player::move()
{
    int choice;
    Item *selectedItem;
    while (1)
    {
        string options = "enter your choice (0 to quit): ";
        choice = getInt(options, 0, backpack.getNames().size(), 0);
        if (choice == 0)
        {
            hp.setCurrentPoint(0);
            return 0;
        }
        selectedItem = itemsMap[backpack.getNames()[choice - 1]];
        selectedItem->setOwner(this);
        if (selectedItem->checkForUse())
            break;
        cout << yellow << "move is not confirmed" << reset << endl;
    }
    selectedItem->useItem();
    if (dynamic_cast<Permanent *>(selectedItem) != nullptr || dynamic_cast<Throwable *>(selectedItem) != nullptr)
    {
        return 0;
    }
    return 1;
}

double SpecialZombie::getPowerBoost()
{

    if (this->getHp()->getCurrentPoint() <= (0.2 * getHp()->getMaxPoint()))
        return model->powerBoost * 1.5;

    return model->powerBoost;
}

void Player::die() { Mission::eventsLog.push_back(name + cyan + " (player) " + red + "died!" + reset); }

MVC::EnemyController::EnemyController(EnemyModel *model, EnemyView *view, Enemy *self) : model(model), view(view), self(self) {}

bool Enemy::move() { return controller->move(); }
void Enemy::die() { controller->die(); }
void Enemy::display(bool isFighting) { view->display(*model, isFighting); }
