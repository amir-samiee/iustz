#pragma once
#include "headers.h"

vector<string> Mission::eventsLog = {};

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
    for (int i = 0; i < wavesInfo.size(); i++)
        casualEnemy = +i;
}

// Calculating the number of waves and enemies in each:
vector<int> Factory::getWave()
{
    vector<int> waves;
    int waveNum = (casualEnemy / 3);
    int remaining = casualEnemy % 3;

    if (waveNum == 0)
    {
        waves.push_back(remaining);
        return waves;
    }

    for (int i = 0; i < waveNum; i++)
        waves.push_back(3);

    int index = waveNum - 1;

    while (remaining != 0)
    {
        waves[index]++;
        index--;
        remaining--;
    }

    shuffle(waves.begin(), waves.end(), gen);
    return waves;
}

// Adding permanent items to a vector of enemies:
void Factory::addPermanent(vector<Character *> unshuffeledEn, vector<string> addingItem)
{
    // Generating a random number of permanents:
    int randomPermanentNum = rand() % (casualEnemy / 2) + (casualEnemy / 4);

    for (int i = 0; i < randomPermanentNum; i++)
    {
        LimitedStorage *backpack = unshuffeledEn[i]->getBackpack();
        int randomWeapon = (rand() % missionPermanents.size());
        backpack->addItem(missionPermanents[randomWeapon]);
    }
}

// Adding removable items to a vector of enemies:
void Factory::addRemovable(vector<Character *> unshuffeledEn, vector<string> addingItem)
{
    shuffle(unshuffeledEn.begin(), unshuffeledEn.end(), gen);
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
void Factory::initRemovable(vector<Item *> adding, vector<string> &to)
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

vector<vector<Character *>> Factory::saveEnemies(vector<int> waves, vector<Character *> unshuffeledEn)
{
    vector<vector<Character *>> enemies;
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

    // Generating enemies backpacks with randomly generated number of permanents inside:
    for (int i = 0; i < casualEnemy; i++)
    {
        int statLevel;
        if(level == 1){statLevel = 1;}
        else
            statLevel = ((level - 1) / 3) + 1 + (rand() % 2);

        // Creating the enemy based on type:
        Character *enemy = new HumanEnemy("", 30, "male", LimitedStorage(), Stat(100, statLevel), Stat(100, statLevel),
                                          level + (rand() % 2), level + (rand() % 2), 1, {player1}, (level * 10));
        // Saving enemy in a primary vector:
        unshuffeledEn.push_back(enemy);
    }

    // Adding mission permanents to the created enemies:
    addPermanent(unshuffeledEn, missionPermanents);
    shuffle(unshuffeledEn.begin(), unshuffeledEn.end(), gen);

    // Adding mission removables to the created enemies:
    addRemovable(unshuffeledEn, missionHpPotions);
    addRemovable(unshuffeledEn, missionStaminaPotions);
    addRemovable(unshuffeledEn, missionPowerPotions);
    addRemovable(unshuffeledEn, missionThrowables);
    shuffle(unshuffeledEn.begin(), unshuffeledEn.end(), gen);

    // Setting names:
    for (int i = 0; i < unshuffeledEn.size(); ++i)
        unshuffeledEn[i]->setName("Human" + to_string(1 + i));

    // Saving enemies in a usable format:
    return saveEnemies(waves, unshuffeledEn);
}

// Main body of creating ZombieEnemies:
vector<vector<Character *>> ZombieFactory::createEnemy(vector<int> waves)
{
    vector<vector<Character *>> enemies;
    vector<Character *> mixedEn;
    vector<Character *> casualEn;
    vector<Character *> specialEn;

    for (int i = 0; i < casualEnemy; i++)
    {
        int statLevel;
        if(level == 1){statLevel = 1;}
        else
            statLevel = ((level - 1) / 3) + 1 + (rand() % 2);

        // Creating the enemy based on type:
        Character *enemy = new ZombieEnemy("", 1000, "male", LimitedStorage(), Stat(100, statLevel), Stat(100 , statLevel),
                                           level + (rand() % 2), level + (rand() % 2), 1, {player1}, (level * 10));
        // Saving enemy in a primary vector:
        casualEn.push_back(enemy);
        mixedEn.push_back(enemy);
    }
    // Adding mission permanents to the created enemies:
    addPermanent(casualEn, missionPermanents);
    shuffle(mixedEn.begin(), mixedEn.end(), gen);
    shuffle(casualEn.begin(), casualEn.end(), gen);

    // Generating special enemies:
    for (int i = 0; i < specialEnemy; i++)
    {
        LimitedStorage backpack;
        int bestWeapon = (missionPermanents.size() - 1);
        backpack.addItem(missionPermanents[bestWeapon]);

        Character *enemy = new SpecialZombie("", 1000, "male", backpack, Stat(200, ((level - 1) / 3) + 1), Stat(200, ((level - 1) / 3) + 1),
                                             (level + rand() % 3 + 1), level + (rand() % 2 + 1), 1, {player1}, (level * 20));
        characterLeakHandle.push_back(enemy);
        specialEn.push_back(enemy);
        mixedEn.push_back(enemy);
    }

    // Adding mission removables to the created enemies:
    addRemovable(mixedEn, missionHpPotions);
    addRemovable(mixedEn, missionStaminaPotions);
    addRemovable(mixedEn, missionPowerPotions);
    addRemovable(mixedEn, missionThrowables);

    shuffle(casualEn.begin(), casualEn.end(), gen);

    // Setting names:
    for (int i = 0; i < casualEn.size(); ++i)
        casualEn[i]->setName("Zombie" + to_string(1 + i));
    for (int i = 0; i < specialEn.size(); ++i)
        specialEn[i]->setName("Special Zombie" + to_string(1 + i));

    // Saving enemies in a usable format:
    enemies = saveEnemies(waves, casualEn);
    if (specialEnemy > 0)
        enemies.push_back(specialEn);

    return enemies;
}

ZombieFactory::ZombieFactory(int lvl, int casualEn, int specialEn)
    : Factory(lvl, casualEn, specialEn) { initInventory(); }

HumanFactory::HumanFactory(int lvl, int casualEn, int specialEn)
    : Factory(lvl, casualEn, specialEn) { initInventory(); }

//////////////////////////////////////////////////////////

void Mission::setNameAuto()
{
    ifstream storyFile("Stories/" + id + ".txt");
    if (storyFile.is_open())
    {
        string name;
        getline(storyFile, name);
        this->name = name.substr(1, name.size() - 2);
        storyFile.close();
    }
    else
        name = "Mission " + to_string(missionNum);
}

Mission::Mission(int newMissionNum, int specialEnemy)
{
    missionNum = newMissionNum;
    if (missionNum == 1)
        casualEnemyNum = 2;
    else
        // Random number of enemies based on level:
        casualEnemyNum = (rand() % 4) + missionNum + 2;
    this->specialEnemy = specialEnemy;
}

bool Mission::humanQualified(Player *player)
{
    return player->getHumanLevels() >= humanLevels;
}

bool Mission::zombieQualified(Player *player)
{
    return player->getZombieLevels() >= zombieLevels;
}

bool Mission::isUnlocked(Player *player)
{
    return humanQualified(player) && zombieQualified(player);
}

void Mission::story()
{
    clearScreen();
    cout << cyan;
    ifstream file("Stories/" + id + ".txt");
    pprint("Mission " + to_string(missionNum) + ": " + name);
    if (file.is_open())
    {
        string line;
        getline(file, line);
        cout << endl;
        while (getline(file, line))
            pprint(line, 400);

        file.close();
    }
    else
        cerr << red << "Unable to open file! " << endl;
    getchPress();
}

void Mission::enemyTurn()
{
    Character *enemy = player1->currentEnemy();
    StateName currentState;
    fsm.setSelf(enemy);
    fsm.resetState();
    do
    {
        currentState = fsm.getCurrentState();

        string data = currentTime() + ": fsm state code: " + to_string(static_cast<int>(currentState));
        dumpData("Data/fsmLog.txt", data, ios::app);

        fsm.runTurn();
    } while (currentState != StateName::Attack);
}

void Mission::playerTurn()
{
    while (1)
    {
        display();
        eventsLog.clear();
        int choice;
        Item *selectedItem = nullptr;
        while (1)
        {
            string options = "enter your choice (0 to quit): ";
            LimitedStorage *backpack = player1->getBackpack();
            choice = getInt(options, 0, backpack->getNames().size(), 0);
            if (choice == 0)
            {
                player1->getHp()->savePoint();
                player1->getHp()->setCurrentPoint(0);
                break;
            }
            selectedItem = itemsMap[backpack->getNames()[choice - 1]];
            selectedItem->setOwner(player1);
            if (selectedItem->checkForUse())
                break;
            cout << yellow << "move is not confirmed" << reset << endl;
        }
        if (choice == 0)
            break;
        selectedItem->useItem();
        if (dynamic_cast<Permanent *>(selectedItem) != nullptr || dynamic_cast<Throwable *>(selectedItem) != nullptr)
            break;
    }
}

void Mission::endWave()
{
    // Adding hp:
    int currentHp = player1->getHp()->getCurrentPoint();
    player1->getHp()->setCurrentPoint((currentHp * 5) / 4);

    // Refilling stamina:
    player1->getStamina()->fill();
}

void Mission::display()
{
    clearScreen(); // this line might better be commented for debugging
    vector<Character *> wave = player1->getWave();
    for (int i = wave.size() - 1; i > 0; i--)
        wave[i]->display();
    if (!wave.empty())
    {
        player1->currentEnemy()->display(1);
        cout << endl;
    }
    player1->display();
    cout << cyan + "Backpack:" + reset << endl;
    player1->getBackpack()->printStorage();
    cout << endl;
    for (auto news : eventsLog)
    {
        dumpData("Data/eventsLog.txt", currentTime() + ": " + removeColors(news), ios::app);
        pprint(news, 400, 0);
    }
}

void Mission::start()
{
    eventsLog.clear();
    waves.clear();
    player1->getHp()->fill();
    player1->getStamina()->fill();
    player1->getBackpack()->saveItems();

    // Feeding data to factory:
    if (dynamic_cast<ZombieMission *>(this) != nullptr)
    {
        ZombieFactory factory(missionNum, casualEnemyNum, specialEnemy);
        setWaves(factory.createEnemy(factory.getWave()));
    }
    else if (dynamic_cast<HumanMission *>(this) != nullptr)
    {
        HumanFactory factory(missionNum, casualEnemyNum, specialEnemy);
        setWaves(factory.createEnemy(factory.getWave()));
    }
    clearScreen();
    cout << "do you wish to skip the story?(y/n...): ";
    string choice;
    getline(cin, choice);
    if (choice != "y")
        story();
    dumpData("Data/eventsLog.txt", currentTime() + ": " + "mission started", ios::app);
    middleGame();
}

void Mission::middleGame()
{
    bool lost = 0; // this boolean prevents too many isAlive() function calls
    for (int i = 0; i < waves.size(); i++)
    {
        player1->setWave(waves[i]);
        eventsLog.push_back("\033[0;100m wave " + to_string(i + 1) + " begins " + reset);

        while (1)
        {
            playerTurn();
            if (!player1->isAlive())
            {
                lost = 1;
                break;
            }

            if (player1->currentEnemy() != nullptr)
                enemyTurn();
            else
                break;
            if (!player1->isAlive())
            {
                lost = 1;
                break;
            }
        }
        if (lost)
            break;

        player1->getHp()->savePoint();
        player1->getStamina()->savePoint();
        endWave();
    }
    end(lost);
}

void Mission::end(bool lost)
{
    if (lost)
    {
        player1->getRewardItems()->clearStorage();
        player1->getBackpack()->loadItems();
        player1->setRewardCoins(0);
        eventsLog.push_back("\033[0;41myou lost!" + reset);
    }
    else
    {
        player1->getHp()->loadPoint();
        player1->getStamina()->loadPoint();
        /*

        here, first backpack transfers to inventory to prevent adding
        a permanent reward to inventory while already included in backpack

        then we transfer back the removed items from backpack.
        conservation of items is preserved here.

        */
        LimitedStorage *backpack = player1->getBackpack();
        Storage *inventory = player1->getInventory();
        LimitedStorage temp = *backpack;
        transfer(backpack, inventory);
        transfer(player1->getRewardItems(), inventory);
        inventory->removeItem(temp.getItems());
        transfer(&temp, backpack);
        player1->setCoins(player1->getCoins() + player1->getRewardCoins());
        player1->setRewardCoins(0);

        eventsLog.push_back("\033[0;42myou won!" + reset);
        eventsLog.push_back("new items added to your inventory");
        eventsLog.push_back("go check them out!");
        save();
    }
    display();
    dumpData("Data/eventsLog.txt", currentTime() + ": " + "mission ended\n", ios::app);
    for (auto wave : waves)
        for (auto enemy : wave)
            delete enemy;
    waves.clear();
    getchPress();
}

ZombieMission::ZombieMission(int missionNum, int specialEnemy)
    : Mission(missionNum, specialEnemy)
{
    // Setting Human and Zombie levels
    zombieLevels = missionNum - 1;
    humanLevels = 3 * (zombieLevels / 3);

    // Setting the ID:
    id = "z" + to_string(missionNum);
    setNameAuto();

    // Saving mission:
    zombieMissions.push_back(this);
}

bool ZombieMission::isPassed(Player *player)
{
    return player->getZombieLevels() > zombieLevels && humanQualified(player);
}

bool HumanMission::isPassed(Player *player)
{
    return player->getHumanLevels() > humanLevels && zombieQualified(player);
}

void ZombieMission::end(bool lost)
{
    Mission::end(lost);
    // saving player progress
    if (!lost)
    {
        int current = player1->getZombieLevels();
        player1->setZombieLevels(max(zombieLevels + 1, current));
    }
}

HumanMission::HumanMission(int newMissionNum, int specialEnemy)
    : Mission(newMissionNum, specialEnemy)
{
    // Setting Human and Zombie levels
    humanLevels = missionNum - 1;
    zombieLevels = 3 * (humanLevels / 3);

    // Setting the ID:
    id = "h" + to_string(missionNum);
    setNameAuto();

    // saving mission:
    humanMissions.push_back(this);
}

void HumanMission::end(bool lost)
{
    Mission::end(lost);
    // saving player progress
    if (!lost)
    {
        int current = player1->getHumanLevels();
        player1->setHumanLevels(max(humanLevels + 1, current));
    }
}

void initializeMissions()
{
    for (int i = 0; i < 9; ++i)
    {
        int missionNum = i + 1;
        int specialEnemyZombie = 0;
        if (missionNum % 3 == 0)
            specialEnemyZombie = 1;

        ZombieMission *newZombieMission = new ZombieMission(missionNum, specialEnemyZombie);
        HumanMission *newHumanmission = new HumanMission(missionNum, 0);
    }
}