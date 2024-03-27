#pragma once
#include "headers.h"

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

    return waves;
}

void Factory::addConsumable(vector<Character *> unorderedEn, vector<string> addingItem)
{
    int i = 0;
    while (!addingItem.empty())
    {
        int randomPotion = rand() % (addingItem.size());
        unorderedEn[i]->getBackpack()->addItem(addingItem[randomPotion]);
        addingItem.erase(addingItem.begin() + randomPotion);
        i++;
        if (i == casualEnemy)
            i = 0;
    }
}

/// @brief ////////////////////////////////////

vector<vector<Character *>> HumanFactory ::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    vector<Character *> unorderedEn;
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
        int firearmLvl;
        int meleeLvl;
        int coins;
        HumanEnemy human("human" + 1 + i, 9, "female", *backpack, hp, stamina,
                         firearmLvl, meleeLvl, 1, {player1}, coins);
        unorderedEn.push_back(&human);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(unorderedEn.begin(), unorderedEn.end(), gen);

    addConsumable(unorderedEn, missionHpPotions);
    addConsumable(unorderedEn, missionStaminaPotions);
    addConsumable(unorderedEn, missionPowerPotions);
    addConsumable(unorderedEn, missionThrowables);

    shuffle(unorderedEn.begin(), unorderedEn.end(), gen);

    for (int i = 0; i < waves.size(); i++)
    {
        vector<Character *> addingChars;
        for (int j = 0; j < waves[i]; j++)
        {
            addingChars.push_back(unorderedEn[0]);
            unorderedEn.erase(unorderedEn.begin());
        }
        enemies.push_back(addingChars);
    }

    return enemies;
}

/// @brief //////////////////////////////

vector<vector<Character *>> ZombieFactory ::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    vector<Character *> unorderedEn;
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
        int firearmLvl;
        int meleeLvl;
        int coins;
        ZombieEnemy zombie("zombie" + 1 + i, 1000, "male", *backpack, hp, stamina,
                           firearmLvl, meleeLvl, 1, {player1}, coins);
        unorderedEn.push_back(&zombie);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(unorderedEn.begin(), unorderedEn.end(), gen);

    addConsumable(unorderedEn, missionHpPotions);
    addConsumable(unorderedEn, missionStaminaPotions);
    addConsumable(unorderedEn, missionPowerPotions);

    shuffle(unorderedEn.begin(), unorderedEn.end(), gen);

    for (int i = 0; i < waves.size(); i++)
    {
        vector<Character *> addingChars;
        for (int j = 0; j < waves[i]; j++)
        {
            addingChars.push_back(unorderedEn[0]);
            unorderedEn.erase(unorderedEn.begin());
        }
        enemies.push_back(addingChars);
    }

    return enemies;
}

/// @brief ///////////////////////////////////////////////

Mission ::Mission(string newName, int newMissionNum, int specialEnemy)
{
    this->name = newName;
    this->missionNum = newMissionNum;
    this->casualEnemyNum = (rand() % 4) + missionNum + 2;
    this->specialEnemy = specialEnemy;
}


void Mission::initCon(vector<Item *> addingItem, string type)
{
    int index = 0;
    int potionNums = (casualEnemyNum * 2) + rand() % ((casualEnemyNum / 4) - (casualEnemyNum / 8));
    if ((this->getMissionNum()) / (2.0) <= addingItem.size())
        index = (this->getMissionNum() - 1) / 2;
    else
        index = addingItem.size() - 1;

    for (int i = 0; i < potionNums; i++)
        missionItemTypes[type].push_back(addingItem[index]->getName());
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
    
    cout<<"Press any key to start\n";
    getchar();
    clearScreen();
}
void Mission ::enemyTurn()
{
}
void Mission ::endWave()
{
}
void Mission ::removeDead()
{
}

void Mission ::playerDeath()
{
}

void Mission ::end()
{
}

void Mission::start()
{
    story();
    while (!waves.empty() && player1->isAlive())
    {
        while (!waves[0].empty() && player1->isAlive())
        {
            player1->turn();

            if (!waves[0].empty())
                enemyTurn();
        }
        endWave();
    }
    end();
}

ZombieMission::ZombieMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "z" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    ZombieFactory factory(newMissionNum, casualEnemyNum, specialEnemy,
                          missionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions);

    this->waves = factory.createEnemy(factory.getWave());

    // saving mission:
    zombieMissions.push_back(this);
}

ZombieMission::ZombieMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                             const vector<string> &missionPermanents,
                             const vector<string> &missionThrowables,
                             const vector<string> &missionHpPotions,
                             const vector<string> &missionStaminaPotions,
                             const vector<string> &missionPowerPotions,
                             const vector<int> wavesInfo)
    : Mission(name, missionNum, casualEnemyNum, specialEnemy, missionPermanents,
              missionThrowables, missionHpPotions, missionStaminaPotions, missionPowerPotions)
{
    // setting the id:
    string id = "z" + missionNum;
    missionMap[id] = this;

    // feeding data to factory:
    ZombieFactory factory(missionNum, casualEnemyNum, specialEnemy,
                          missionPermanents, missionThrowables, missionHpPotions,
                          missionStaminaPotions, missionPowerPotions, wavesInfo);
    this->waves = factory.createEnemy(wavesInfo);

    // saving mission:
    zombieMissions.push_back(this);
}
void ZombieMission::initInventory()
{
    if (missionNum < melees.size())
    {
        this->missionPermanents.push_back(melees[missionNum]->getName());
        if (missionNum != 1)
        {
            this->missionPermanents.push_back(melees[missionNum - 1]->getName());
        }
    }
    else
    {
        this->missionPermanents.push_back(melees[melees.size() - 1]->getName());
        this->missionPermanents.push_back(melees[melees.size() - 2]->getName());
    }
    initCon(hpPotions, "hp");
    initCon(staminaPotions, "sta");
    initCon(powerPotions, "pow");
}

HumanMission::HumanMission(string newName, int newMissionNum, int specialEnemy)
    : Mission(newName, newMissionNum, specialEnemy)
{
    // setting the id:
    string id = "h" + newMissionNum;
    missionMap[id] = this;

    // building inventory:
    initInventory();

    // feeding data to factory:
    HumanFactory factory(newMissionNum, casualEnemyNum, specialEnemy,
                         missionPermanents, missionThrowables, missionHpPotions,
                         missionStaminaPotions, missionPowerPotions);

    this->waves = factory.createEnemy(factory.getWave());

    // saving mission:
    humanMissions.push_back(this);
}

HumanMission::HumanMission(const string &name, int missionNum, int casualEnemyNum, int specialEnemy,
                           const vector<string> &missionPermanents,
                           const vector<string> &missionThrowables,
                           const vector<string> &missionHpPotions,
                           const vector<string> &missionStaminaPotions,
                           const vector<string> &missionPowerPotions,
                           const vector<int> wavesInfo)
    : Mission(name, missionNum, casualEnemyNum, specialEnemy, missionPermanents,
              missionThrowables, missionHpPotions, missionStaminaPotions, missionPowerPotions)
{
    // setting the id:
    string id = "h" + missionNum;
    missionMap[id] = this;

    // feeding data to factory:
    HumanFactory factory(missionNum, casualEnemyNum, specialEnemy,
                         missionPermanents, missionThrowables, missionHpPotions,
                         missionStaminaPotions, missionPowerPotions, wavesInfo);
    vector<int> waves; // give the customized waves
    this->waves = factory.createEnemy(waves);

    // saving mission:
    humanMissions.push_back(this);
}

void HumanMission::initInventory()
{
    if (missionNum < firearms.size())
    {
        this->missionPermanents.push_back(firearms[missionNum - 1]->getName());
        if (missionNum != 1)
        {
            this->missionPermanents.push_back(firearms[missionNum - 2]->getName());
        }
    }
    else
    {
        this->missionPermanents.push_back(firearms[firearms.size() - 1]->getName());
        this->missionPermanents.push_back(firearms[firearms.size() - 2]->getName());
    }
    initCon(hpPotions, "hp");
    initCon(staminaPotions, "sta");
    initCon(powerPotions, "pow");
    initCon(throwables, "thr");
}
