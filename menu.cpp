#include "headers.h"
using namespace std;

namespace menu
{
    void zombies()
    {
        string zombieMissions = "\n1. Mission1 \n2. Mission2 \n3. Mission3 \n4. Mission4\n5. Mission5\n6. Mission6 \n7. Mission7 \n8. Mission8 \n9. Mission9\n0. Back\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + zombieMissions, 0, 9, true, "invalid input");

        if (intInput == 0)
            return;
    }

    void humans()
    {
        string humanMissions = "\n1. Mission1 \n2. Mission2 \n3. Mission3 \n4. Mission4\n5. Mission5\n6. Mission6 \n7. Mission7 \n8. Mission8 \n9. Mission9\n0. Back\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + humanMissions, 0, 9, true, "invalid input");

        if (intInput == 0)
            return;
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
                zombies();
                break;
            case 2:
                humans();
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
        cout << "Profile" << endl;
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
                if (!player1->getBackpack()->isFull())
                {
                    string itemName = player1->getInventory()->getNames()[choice - 1];
                    player1->getInventory()->removeItem(itemName);
                    player1->getBackpack()->addItem(itemName);
                }
            }
            else if (choice < 0) // remove item from backpack and add to inventory
            {
                string itemName = player1->getBackpack()->getNames()[-choice - 1];
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
            string menu = "\n1. Attack \n2. Shop \n3. Profile \n4. Invnetory\n0. Exit\nenter your choice: ";
            int intInput = getInput(iustzTitle + menu, 0, 4, true, "invalid input");

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
                return;
            }
        }
    }
}
