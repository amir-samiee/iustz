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
    maxPoint = data["maxPoint"];
}

json Stat::dumpStat()
{
    json data;
    data["maxPoint"] = maxPoint;
    return data;
}

void Stat::fill()
{
    currentPoint = maxPoint;
}

int Stat::level()
{
    return (((maxPoint - 100) / 30) + 1);
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
void Player::display()
{
    cout << green
         << "Player: " << name << endl
         << "HP: " << hp.getCurrentPoint() << endl
         << "Stamina: " << stamina.getCurrentPoint() << endl
         << "Power Boost: " << powerBoost << endl
         << "Current Enemies Count: " << currentWave.size() << endl
         << reset;
}

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

void MVC::EnemyView::display(const EnemyModel &model) {}

void MVC::EnemyController::takeDamage(int takenDamage)
{
    int newPoint = model->hp.getCurrentPoint() - takenDamage;
    model->hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}

bool MVC::EnemyController::move()
{
    fsm.setSelf(self);
    StateName currentState = fsm.getCurrentState();
    // cout << "state code: " << static_cast<int>(currentState) << endl;
    fsm.runTurn();
    return (currentState != StateName::Attack);
}

MVC::EnemyController::~EnemyController()
{
}

void MVC::EnemyController::die()
{
    Player *myplayer = dynamic_cast<Player *>(self->currentEnemy());
    // setting rewards:
    transfer(self->getBackpack(), myplayer->getReward());

    // removing enemy from wave:
    vector<Character *> newvec = this->self->currentEnemy()->getWave();
    for (int i = 0; i < newvec.size(); i++)
    {
        if (newvec[i] == dynamic_cast<Character *>(self))
        {
            newvec.erase(newvec.begin() + i);
            break;
        }
    }
    this->self->currentEnemy()->setWave(newvec);
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
    deletePtr(model);
    deletePtr(view);
    deletePtr(controller);
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
    controller = new MVC::SpecialEnemyController(model, view, this);
}

void SpecialZombie::takeDamage(int damage) { this->controller->takeDamage(damage); }

////////////////////////////////////////////////////////////////

bool Player::move()
{
    int choice;
    Item *selectedItem;
    while (1)
    {
        string options = "enter your choice: ";
        choice = getInput(options, 1, backpack.getNames().size(), 0);
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

    if (this->getHp()->getMaxPoint() <= (20))
        return model->powerBoost * 1.5;

    return model->powerBoost;
}
void Player::die() {}

MVC::EnemyController::EnemyController(EnemyModel *model, EnemyView *view, Enemy *self) : model(model), view(view), self(self) {}

bool Enemy::move() { return controller->move(); }
void Enemy::die() { controller->die(); }
void Enemy::display()
{
    cout << red
         << "Enemy Name: " << model->name << endl
         << "HP: " << model->hp.getCurrentPoint() << endl
         << "Stamina: " << model->stamina.getCurrentPoint() << endl
         << "Power Boost: " << model->powerBoost << endl
         << reset;
}
