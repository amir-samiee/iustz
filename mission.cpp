#pragma once
#include "headers.h"

Factory::Factory(int lvl, int specialEn,
                 const vector<string> &permanents,
                 const vector<string> &throwables,
                 const vector<string> &hpPotions,
                 const vector<string> &staminaPotions,
                 const vector<string> &powerPotions,
                 vector<int> wavesInfo)
    : level(lvl), specialEnemy(specialEn),
      missionPermanents(permanents), missionThrowables(throwables),
      missionHpPotions(hpPotions), missionStaminaPotions(staminaPotions),
      missionPowerPotions(powerPotions)
{
    for(int i=0; i<wavesInfo.size(); i++)
        casualEnemy =+ i;
}

// Calculating the number of waves and enemies in each:
vector<int> Factory::getWave()
{
    vector<int> waves;
    int waveNum = casualEnemy / 3;
    int remaining = casualEnemy % waveNum;

    for (int i = 0; i < waveNum; i++)
        waves.push_back(3);

    int index = waveNum - 1;

    while (remaining != 0)
    {
        waves[index]++;
        index--;
        remaining--;
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(waves.begin(), waves.end(), gen);

    return waves;
}

// Adding removable items to a vector of enemies:
void Factory::addRemoveable(vector<Character *> unshuffeledEn, vector<string> addingItem)
{
    int i = 0;
    while (!addingItem.empty())
    {
        int randomPotion = rand() % (addingItem.size());
        unshuffeledEn[i]->getBackpack()->addItem(addingItem[randomPotion]);
        addingItem.erase(addingItem.begin() + randomPotion);
        i++;
        if (i == casualEnemy)
            i = 0;
    }
}

// initializing removable items for a mission:
void Factory::initRemovable(vector<Item *> adding, vector<string> to)
{
    int index = 0;
    int potionNums = (casualEnemy * 2) + (rand() % (casualEnemy / 2)) - (casualEnemy / 4);
    if (level / (2.0) <= adding.size())
        index = (level - 1) / 2;
    else
        index = adding.size() - 1;

    for (int i = 0; i < potionNums; i++)
        to.push_back(adding[index]->getName());
}

// Intializing all items for a ZombieMission:
void ZombieFactory::initInventory()
{
    if (level < melees.size())
    {
        missionPermanents.push_back(melees[level]->getName());
        if (level != 1)
        {
            missionPermanents.push_back(melees[level - 1]->getName());
        }
    }
    else
    {
        missionPermanents.push_back(melees[melees.size() - 1]->getName());
        missionPermanents.push_back(melees[melees.size() - 2]->getName());
    }
    initRemovable(hpPotions, missionHpPotions);
    initRemovable(staminaPotions, missionStaminaPotions);
    initRemovable(powerPotions, missionPowerPotions);
}

// Intializing all items for a HumanMission:
void HumanFactory::initInventory()
{
    if (level < firearms.size())
    {
        this->missionPermanents.push_back(firearms[level - 1]->getName());
        if (level != 1)
        {
            this->missionPermanents.push_back(firearms[level - 2]->getName());
        }
    }
    else
    {
        this->missionPermanents.push_back(firearms[firearms.size() - 1]->getName());
        this->missionPermanents.push_back(firearms[firearms.size() - 2]->getName());
    }
    initRemovable(hpPotions, missionHpPotions);
    initRemovable(staminaPotions, missionStaminaPotions);
    initRemovable(powerPotions, missionPowerPotions);
    initRemovable(throwables, missionThrowables);
}

// Main body of creating HumanEnemies:
vector<vector<Character *>> HumanFactory::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    vector<Character *> unshuffeledEn;

    // Generating a random number of permanents:
    int randomPermanentNum = rand() % (casualEnemy / 2) + (casualEnemy / 4);

    // Generating enemies backpacks with randomly generated number of permanents inside:
    for (int i = 0; i < casualEnemy; i++)
    {
        LimitedStorage *backpack = new LimitedStorage;
        if (i < randomPermanentNum && missionPermanents.size() != 0)
        {
            int randomWeapon = (rand() % missionPermanents.size());
            backpack->addItem(missionPermanents[randomWeapon]);
        }
        Stat hp;
        Stat stamina;

        // The value is not decided yet:
        int firearmLvl;
        int meleeLvl;
        int coins;

        // Creating the enemy based on type:
        Character *enemy;
        enemy = new HumanEnemy("human" + 1 + i, 9, "female", *backpack, hp, stamina,
                               firearmLvl, meleeLvl, 1, {player1}, coins);

        // Saving enemy in a primary vector:
        unshuffeledEn.push_back(enemy);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(unshuffeledEn.begin(), unshuffeledEn.end(), gen);

    // Adding missions removables to the created enemies:
    addRemoveable(unshuffeledEn, missionHpPotions);
    addRemoveable(unshuffeledEn, missionStaminaPotions);
    addRemoveable(unshuffeledEn, missionPowerPotions);
    addRemoveable(unshuffeledEn, missionThrowables);

    shuffle(unshuffeledEn.begin(), unshuffeledEn.end(), gen);

    // Saving enemies in a usable format:
    for (int i = 0; i < waves.size(); i++)
    {
        vector<Character *> addingChars;
        for (int j = 0; j < waves[i]; j++)
        {
            addingChars.push_back(unshuffeledEn[0]);
            unshuffeledEn.erase(unshuffeledEn.begin());
        }
        enemies.push_back(addingChars);
    }

    return enemies;
}

// Main body of creating ZombieEnemies:
vector<vector<Character *>> ZombieFactory::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    vector<Character *> mixedEn;
    vector<Character *> casualEn;
    vector<Character *> specialEn;
    Character *enemy;

    // Generating enemies backpacks with randomly generated number of permanents inside:
    int randomPermanentNum = rand() % (casualEnemy / 2) + (casualEnemy / 4);

    for (int i = 0; i < casualEnemy; i++)
    {
        LimitedStorage *backpack = new LimitedStorage;
        if (i < randomPermanentNum && missionPermanents.size() != 0)
        {
            int randomWeapon = (rand() % missionPermanents.size());
            backpack->addItem(missionPermanents[randomWeapon]);
        }
        Stat hp;
        Stat stamina;

        // The value is not decided yet:
        int firearmLvl;
        int meleeLvl;
        int coins;

        // Creating the enemy based on type:
        enemy = new ZombieEnemy("zombie" + 1 + i, 1000, "male", *backpack, hp, stamina,
                                firearmLvl, meleeLvl, 1, {player1}, coins);

        // Saving enemy in a primary vector:
        casualEn.push_back(enemy);
        mixedEn.push_back(enemy);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(mixedEn.begin(), mixedEn.end(), gen);
    shuffle(casualEn.begin(), casualEn.end(), gen);

    // Generating special enemies:
    for (int i = 0; i < specialEnemy; i++)
    {
        LimitedStorage *backpack = new LimitedStorage;
        int bestWeapon = (missionPermanents.size() - 1);
        backpack->addItem(missionPermanents[bestWeapon]);

        Stat hp;
        Stat stamina;
        // The value is not decided yet:
        int firearmLvl;
        int meleeLvl;
        int coins;

        enemy = new SpecialZombie("zombie" + 1 + i, 1000, "male", *backpack, hp, stamina,
                                  firearmLvl, meleeLvl, 1, {player1}, coins);
        specialEn.push_back(enemy);
        mixedEn.push_back(enemy);
    }

    // Adding missions removables to the created enemies:
    addRemoveable(mixedEn, missionHpPotions);
    addRemoveable(mixedEn, missionStaminaPotions);
    addRemoveable(mixedEn, missionPowerPotions);
    addRemoveable(mixedEn, missionThrowables);

    shuffle(casualEn.begin(), casualEn.end(), gen);

    // Saving enemies in a usable format:
    for (int i = 0; i < waves.size(); i++)
    {
        vector<Character *> addingChars;
        for (int j = 0; j < waves[i]; j++)
        {
            addingChars.push_back(casualEn[0]);
            casualEn.erase(casualEn.begin());
        }
        enemies.push_back(addingChars);
    }

    enemies.push_back(specialEn);

    return enemies;
}

ZombieFactory::ZombieFactory(int lvl, int casualEn, int specialEn)
    : Factory(lvl, casualEn, specialEn) { initInventory(); }

HumanFactory::HumanFactory(int lvl, int casualEn, int specialEn)
    : Factory(lvl, casualEn, specialEn) { initInventory(); }

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, int specialEnemy)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    // Random number of enemies based on level:
    this->casualEnemyNum = (rand() % 4) + missionNum + 2;
    this->specialEnemy = specialEnemy;
}

void Mission ::story()
{
    ifstream file("Stories/" + name + ".txt");
    if (file.is_open())
    {
        string line;
        cout << "Mission " << missionNum << " - " << name << ":\n";
        while (getline(file, line))
        {
            cout << line << endl;
            Sleep(2000);
        }
        file.close();
    }
    else
        cerr << "Unable to open file! " << endl;

    cout << "Press any key to start\n";
    _getch();
    clearScreen();
}
void Mission ::enemyTurn()
{
}
void Mission ::endWave()
{
    // Adding hp:
    int currentHp = player1->getHp()->getCurrentPoint();
    player1->getHp()->setCurrentPoint((currentHp * 5) / 4);

    // Refilling stamina:
    int newStamina = player1->getStamina()->getMaxPoint();
    player1->getStamina()->setCurrentPoint(newStamina);
}

void Mission ::end()
{
    if (player1->isAlive())
        transfer(player1->getReward(), player1->getInventory());
    else
    {
        player1->getReward()->setItems({});
    }
}

void Mission::start()
{
    story();
    for (int i = 0; i < waves.size(); i++)
    {
        player1->setWave(waves[i]);

        while (!player1->getWave().empty() && player1->isAlive())
        {
            player1->turn();

            if (!player1->getWave().empty())
                enemyTurn();
        }

        if (!player1->isAlive())
            break;

        endWave();
    }
    end();
}

ZombieMission::ZombieMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // Setting the ID:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // Feeding data to factory:
    ZombieFactory factory(newMissionNum, casualEnemyNum, specialEnemy);
    waves = factory.createEnemy(factory.getWave());

    // Saving mission:
    zombieMissions.push_back(this);
}

ZombieMission::ZombieMission(const string &name, int missionNum, int specialEnemy,
                             const vector<string> &missionPermanents,
                             const vector<string> &missionThrowables,
                             const vector<string> &missionHpPotions,
                             const vector<string> &missionStaminaPotions,
                             const vector<string> &missionPowerPotions,
                             const vector<int> wavesInfo)
    : Mission(name, missionNum, 0, specialEnemy)
{
    // Setting the ID:
    string id = "z" + missionNum;
    missionMap[id] = this;

    // Feeding data to factory:
    ZombieFactory factory(missionNum, specialEnemy,
                          missionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions, wavesInfo);
    waves = factory.createEnemy(wavesInfo);
    casualEnemyNum = factory.getCasualEnemy();//no real point to this

    // Saving mission:
    zombieMissions.push_back(this);
}

HumanMission::HumanMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // Setting the ID:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // Feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy);
    waves = factory.createEnemy(factory.getWave());

    // saving mission:
    humanMissions.push_back(this);
}

HumanMission::HumanMission(const string &name, int missionNum, int specialEnemy,
                           const vector<string> &missionPermanents,
                           const vector<string> &missionThrowables,
                           const vector<string> &missionHpPotions,
                           const vector<string> &missionStaminaPotions,
                           const vector<string> &missionPowerPotions,
                           const vector<int> wavesInfo)
    : Mission(name, missionNum, 0, specialEnemy)
{
    // Setting the id:
    string id = "h" + missionNum;
    missionMap[id] = this;

    // Feeding data to factory:
    HumanFactory factory(missionNum, specialEnemy,
                         missionPermanents, missionThrowables, missionHpPotions,
                         missionStaminaPotions, missionPowerPotions, wavesInfo);

    waves = factory.createEnemy(wavesInfo);
    casualEnemyNum = factory.getCasualEnemy();//no real point to this

    // Saving mission:
    humanMissions.push_back(this);
}
