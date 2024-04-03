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
            for (int i = 0; i < missions.size(); i++)
            {
                Mission *mission = missions[i];
                if (mission->isUnlocked(player1))
                    options << gray;
                options << i + 1 << ". " << mission->getName() << reset << endl;
            }
            options << "0. Back" << endl;
            options << "\nenter the mission number: ";
            int intInput = getInput(iustzTitle + options.str(), 0, 9, true, "invalid input");

            if (intInput == 0)
                return;
            else if (missions[intInput - 1]->isUnlocked(player1))
                missions[intInput - 1]->start();
        }
    }

    void finale()
    {
        cout << "finale" << endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void attack()
    {
        int intInput;
        do
        {
            string attacksMenu = "\n1. Zombies \n2. Humans \n3. Finale \n0. Back\nenter your choice: ";
            intInput = getInput(iustzTitle + attacksMenu, 0, 3, true, "invalid input");
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
        clearScreen();
        cout << "Username: " << player1->getUsername() << endl;
        player1->display();
        cout << "\npress any key to continue ...";
        getch();
    }
    void inventory()
    {
        clearScreen();
        while (1)
        {
            stringstream data;
            data << "Inventory:" << endl;
            data << player1->getInventory()->getStorageData(green + "+", reset + "   ", 5);
            data << "\nBackpack:" << endl;
            data << player1->getBackpack()->getStorageData(red + "-", reset + "   ", 5);
            if (player1->getBackpack()->isFull())
                data << yellow << "backpack is full!" << reset;
            else
                data << "Remained Space: " << player1->getBackpack()->remainedSpace();
            data << "\n\n 0   Back\n";
            data << "\nenter your choice: ";
            int choice = getInput(data.str(), -player1->getBackpack()->getNames().size(),
                                  player1->getInventory()->getNames().size());

            if (choice == 0)
                return;
            else if (choice > 0) // add item from inventroy to backpack
            {
                string itemName = player1->getInventory()->getNames()[choice - 1];
                if (!player1->getBackpack()->isFull())
                {
                    player1->getInventory()->removeItem(itemName);
                    player1->getBackpack()->addItem(itemName);
                }
            }
            else if (choice < 0) // remove item from backpack and add to inventory
            {
                string itemName = player1->getBackpack()->getNames()[-choice - 1];
                if (itemName == "Punch")
                {
                    clearScreen();
                    cout << red << "you can't remove Punch from your backpack!" << reset << endl;
                    cout << "enter any key to continue: ";
                    getch();
                    continue;
                }
                player1->getInventory()->addItem(itemName);
                player1->getBackpack()->removeItem(itemName);
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void mainMenu()
    {
        while (1)
        {
            string menu = "\n 1. Attack \n 2. Shop \n 3. Profile \n 4. Invnetory\n 0. Back\n-1. Exit\n\nenter your choice: ";
            int intInput = getInput(iustzTitle + menu, -1, 4, true, "invalid input");

            switch (intInput)
            {
            case 1:
                attack();
                break;
            case 2:
                shop.displayShop();
                break;
            case 3:
                profile();
                break;
            case 4:
                inventory();
                break;
            case 0:
                save();
                return;
            case -1:
                save();
                delete player1;
                exit(0);
            }
        }
    }
}
