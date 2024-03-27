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

int Stat::level()
{
    return (((maxPoint - 100) / 30) + 1);
}

/// @brief ////////////////////////////////////////////////////

int Player::level() { return (firearmLevel + meleeLevel + hp.level() + stamina.level()) / 4; }
void Player::takeDamage(int takenDamage)
{
    int newPoint = hp.getCurrentPoint() - takenDamage;
    hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
Player ::Player(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins, Storage inventory, int humanLevels, int zombieLevels) : name(name), age(age), gender(gender), backpack(backpack),
                                                                                                                                                    hp(hp), stamina(stamina), firearmLevel(firearmLevel), meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins), inventory(inventory), humanLevels(humanLevels), zombieLevels(zombieLevels) {}

MVC::EnemyModel::EnemyModel(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
                            int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins)
    : name(name), age(age), gender(gender), backpack(backpack), hp(hp), stamina(stamina), firearmLevel(firearmLevel),
      meleeLevel(meleeLevel), powerBoost(powerBoost), currentWave(currentWave), coins(coins) {}

void MVC::EnemyController::takeDamage(int takenDamage)
{
    int newPoint = model->hp.getCurrentPoint() - takenDamage;
    model->hp.setCurrentPoint(newPoint);
    if (newPoint <= 0)
        this->die();
}
void MVC::EnemyController::die() {}

Enemy::Enemy(string name, int age, string gender, LimitedStorage backpack, Stat hp, Stat stamina, int firearmLevel,
             int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins)
    : model(new MVC::EnemyModel(name, age, gender, backpack, hp, stamina, firearmLevel,
                                meleeLevel, powerBoost, currentWave, coins)),
      view(new MVC::EnemyView),
      controller(new MVC::EnemyController(model, view)){};
Enemy::~Enemy()
{
    delete model;
    delete view;
    delete controller;
}
int Enemy::level() { return (model->firearmLevel + model->meleeLevel + model->hp.level() + model->stamina.level()) / 4; }
void Enemy::takeDamage(int damage) { controller->takeDamage(damage); }

HumanEnemy::HumanEnemy(string name, int age, string gender, LimitedStorage backpack,
                       Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                    stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

ZombieEnemy::ZombieEnemy(string name, int age, string gender, LimitedStorage backpack,
                         Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : Enemy(name, age, gender, backpack, hp,
                                                                                                                                                      stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

SpecialZombie::SpecialZombie(string name, int age, string gender, LimitedStorage backpack,
                             Stat hp, Stat stamina, int firearmLevel, int meleeLevel, int powerBoost, vector<Character *> currentWave, int coins) : ZombieEnemy(name, age, gender, backpack, hp,
                                                                                                                                                                stamina, firearmLevel, meleeLevel, powerBoost, currentWave, coins) {}

/// @brief /////////////////////////////////////////////////////

void Player::turn()
{
    int from = 1, to = backpack.getSize();
    bool cls = true;
    string errorMessage = "invalid input";
    string input;
    bool indexError = 0, typeError = 0, emptyString = 0, lowStamina = 0;
    do
    {
        if (cls)
            clearScreen();
        if (indexError || typeError || emptyString)
            cout << red << errorMessage << reset;
        cout << endl;
        backpack.printStorage();
        indexError = typeError = lowStamina = 0;
        getline(cin, input);
        if (input == "")
            emptyString = 1;
        else
        {
            emptyString = 0;
            if (isInteger(input))
            {
                cleanIntString(input);
                if (input.size() > max(to_string(to).size(), to_string(from).size()) || stoi(input) > to || stoi(input) < from)
                    indexError = 1;
                else{
                    if(!itemsMap[backpack.getNames()[stoi(input) - 1]]->checkStamina())
                        lowStamina = 1;
                }
            }
            else
                typeError = 1;
        }
    } while (indexError || typeError || emptyString || lowStamina);
    itemsMap[backpack.getNames()[stoi(input) - 1]]->useItem();
}

void Player::die() {}
void Enemy::turn() {}
void Enemy::die() { controller->die(); }
void SpecialZombie::turn() {}
