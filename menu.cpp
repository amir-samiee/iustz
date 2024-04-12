#pragma once
#include "headers.h"
using namespace std;

namespace menu
{
    void missionSelect(vector<Mission *> missions)
    {
        while (1)
        {
            stringstream options;
            options << endl;
            for (int i = 0; i < missions.size(); i++)
            {
                Mission *mission = missions[i];
                if (!mission->isUnlocked(player1))
                    options << gray;
                else if (mission->isPassed(player1))
                    options << strikethrough;
                else
                    options << white;
                options << i + 1 << ". " << mission->getName() << reset << endl;
            }
            options << "0. Back" << endl;
            options << "\nenter the mission number: ";
            int intInput = getInt(iustzTitle + options.str(), 0, 9, true, "invalid input");
            Mission *selected = missions[intInput - 1];
            if (intInput == 0)
                return;
            else if (selected->isUnlocked(player1))
                selected->start();
            else
            {
                clearScreen();
                cout << "you haven't unlocked this mission!  " << cyan << "(" << selected->getName() << ")" << reset
                     << "\nnotice: you might have to continue the other branch to unlock this mission"
                     << "\n\nRequired Human Levels: " << selected->getHumanLevels()
                     << "\nRequired Zombie Levels: " << selected->getZombieLevels()
                     << endl;
                getchPress();
            }
        }
    }

    void finale()
    {
        clearScreen();
        if (player1->getHumanLevels() == 9 && player1->getZombieLevels() == 9)
        {
            cout << cyan;
            ifstream file("Stories/finale.txt");
            string line;
            while (getline(file, line))
                pprint(line);
            file.close();
        }
        else
        {
            clearScreen();
            cout << "you haven't unlocked this mission!  " << cyan << "(Finale)" << reset
                 << "\nnotice: you might have to continue the other branch to unlock this mission"
                 << "\n\nRequired Human Levels: " << 9
                 << "\nRequired Zombie Levels: " << 9
                 << endl;
        }
        getchPress();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void attack()
    {
        int intInput;
        do
        {
            string attacksMenu = "\n1. Zombies \n2. Humans \n3. Finale \n0. Back\nenter your choice: ";
            intInput = getInt(iustzTitle + attacksMenu, 0, 3, true, "invalid input");
            switch (intInput)
            {
            case 1:
                missionSelect(zombieMissions);
                break;
            case 2:
                missionSelect(humanMissions);
                break;
            case 3:
                finale();
                break;
            default:
                return;
            }
        } while (intInput != 4);
    }

    void profile()
    {
        while (1)
        {
            clearScreen();
            stringstream options;
            options << gray
                    << "Hp Level: " << player1->getHp()->level() << endl
                    << "Stamina Level: " << player1->getStamina()->level() << endl
                    << "Gender: " << player1->getGender() << endl
                    << "Firearm Level: " << player1->getFirearmLevel() << endl
                    << "Melee Level: " << player1->getMeleeLevel() << endl
                    << "Coins: " << player1->getCoins() << endl
                    << "Human Levels: " << player1->getHumanLevels() << endl
                    << "Zombie Levels: " << player1->getZombieLevels() << endl
                    << reset << endl
                    << "1. Username: " << player1->getUsername() << endl
                    << "2. Name: " << player1->getName() << endl
                    << "3. Age: " << player1->getAge() << endl
                    << "4. Gender: " << player1->getGender() << endl
                    << "0. Back" << endl
                    << "\nenter a number to make changes: ";
            int choice = getInt(options.str(), 0, 4);

            int newAge, genderChoice;
            string newUsername, newName, newGender;

            clearScreen();
            switch (choice)
            {
            case 1:
                cout << "enter new username: ";
                getline(cin, newUsername);
                if (changeUsername(player1->getUsername(), newUsername))
                {
                    player1->setUsername(newUsername);
                    cout << green << "ussername changed successfully!" << reset;
                }
                else
                    cout << red << "this username is already taken!" << reset;
                break;
            case 2:
                cout << "enter new name: ";
                getline(cin, newName);
                player1->setName(newName);
                cout << green << "name changed successfully!" << reset;
                break;
            case 3:
                newAge = getInt("enter new age: ", 1, 200, 1);
                player1->setAge(newAge);
                cout << green << "age changed successfully!" << reset;
                break;
            case 4:
                genderChoice = getInt(genderOptions, 1, 3);
                newGender = genders[genderChoice - 1];
                player1->setGender(newGender);
                cout << green << "gender changed successfully!" << reset;
                break;
            case 0:
                return;
            }
            save();
            getchPress();
        }
    }

    void inventory()
    {
        clearScreen();
        while (1)
        {
            stringstream data;
            data << "Inventory:" << endl;
            data << player1->getInventory()->getStorageData(green + "+", reset);
            data << "\nBackpack:" << endl;
            data << player1->getBackpack()->getStorageData(red + "-", reset);
            if (player1->getBackpack()->isFull())
                data << yellow << "backpack is full!" << reset;
            else
                data << "Remained Space: " << player1->getBackpack()->remainedSpace();
            data << "\n\n 0   Back\n";
            data << "\nenter your choice: ";
            int choice = getInt(data.str(), -player1->getBackpack()->getNames().size(),
                                player1->getInventory()->getNames().size());

            if (choice == 0)
                return;
            else if (choice > 0) // add item from inventroy to backpack
            {
                string itemName = player1->getInventory()->getNames()[choice - 1];
                if (!player1->getBackpack()->isFull())
                {
                    player1->getInventory()->removeItem(itemName);
                    player1->getBackpack()->addItem(itemName, true);
                }
            }
            else if (choice < 0) // remove item from backpack and add to inventory
            {
                string itemName = player1->getBackpack()->getNames()[-choice - 1];
                if (itemName == "Punch")
                {
                    clearScreen();
                    cout << red << "you can't remove Punch from your backpack!" << reset << endl;
                    getchPress();
                    continue;
                }
                player1->getInventory()->addItem(itemName, true);
                player1->getBackpack()->removeItem(itemName);
            }
        }
    }

    bool deletedAccount()
    {
        clearScreen();
        cout << yellow << "this action will delete all your data " + red + "PERMANENTLY!!!" << endl;
        cout << yellow << "ENTER \"YES\" IF YOU ARE SURE YOU WANT TO DELETE YOUR ACCOUNT (anything will cancel the action): ";
        string deleteVerification;
        getline(cin, deleteVerification);
        if (deleteVerification == "YES")
        {
            removeUsername(player1->getUsername());
            cout << green << "account deleted successfully!!" << reset;
        }
        else
            cout << red << "action canceled!!" << reset;
        getchPress();
        if (deleteVerification == "YES")
            return 1;
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void mainMenu()
    {
        while (1)
        {
            string menu = "\n 1. Attack \n 2. Shop \n 3. Profile \n 4. Invnetory\n 5. Delete Account\n 0. Back\n-1. Exit\n\nenter your choice: ";
            int intInput = getInt(iustzTitle + menu, -1, 5, true, "invalid input");
            switch (intInput)
            {
            case 1:
                attack();
                break;
            case 2:
                shop.displayShop();
                save();
                break;
            case 3:
                profile();
                break;
            case 4:
                inventory();
                save();
                break;
            case 0:
                save();
                return;
            case 5:
                if (deletedAccount())
                    return;
                break;
            case -1:
                save();
                cleanUp();
                exit(0);
            }
        }
    }
}
