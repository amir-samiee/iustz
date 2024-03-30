#pragma once
#include "headers.h"

void Shop ::displayShop()
{
    int input;
    string options = "";
    options += "Welcome to the shop! Here are the items available for purchase:\n";
    options += "1-Throwables\n2-Potions\n3-Weapon\n\n0-Back\n";
    int firstInput = getInput(options, 0, 3);

    if (firstInput == 0)
        menu::mainMenu();
    else
        shopsItem(firstInput);
}

void Shop ::shopsItem(int choice)
{
    int lastInput;
    int secondInput;
    int thirdInput;
    string option2;
    string option3;
    string backOption = "0-Back\n";
    string message = "Item added to your backpack!\n";
    stringstream result;

    switch (choice)
    {
    case 1:
        result << "Throwables Items : \n";
        result << setw(20) << left << setw(20) << "  NAME"
               << setw(20) << "PRICE"
               << setw(20) << "STAMINA"
               << setw(20) << "DAMAGE" << endl;
        for (int i = 0; i < throwables.size(); ++i)
        {
            int index = i + 1;
            result << left << index << "-" << setw(20) << throwables[i]->getName()
                   << setw(20) << throwables[i]->getPrice()
                   << setw(20) << throwables[i]->getStamina()
                   << setw(20) << throwables[i]->getSpecial() << endl;
        }
        result << backOption;
        lastInput = getInput(result.str(), 0, throwables.size());
        result.str("");

        if (lastInput == 0)
        {
            displayShop(); // Go back to Shops main menu
            break;
        }
        player1->getInventory()->addItem(throwables[lastInput - 1]->getName());
        cout << message << endl;
        break;

    case 2:

        result << "Potions Items :\n1-Hp Potions\n2-Stamina Potions\n3-Power Potions\n0-Back\n";

        secondInput = getInput(result.str(), 0, 3);
        result.str("");
        cout << secondInput;
        switch (secondInput)
        {
        case 1:
            result << "Hp Potions : \n";
            result << setw(20) << left << setw(20) << "  NAME"
                   << setw(20) << "PRICE"
                   << setw(20) << "STAMINA"
                   << setw(20) << "HEALING AMOUNT" << endl;
            for (int i = 0; i < hpPotions.size(); i++)
            {
                int index = i + 1;
                result << left << index << "-" << setw(20) << hpPotions[i]->getName()
                       << setw(20) << hpPotions[i]->getPrice()
                       << setw(20) << hpPotions[i]->getStamina()
                       << setw(20) << hpPotions[i]->getSpecial() << endl;
            }
            result << backOption;
            lastInput = getInput(result.str(), 0, hpPotions.size());
            result.str("");

            if (lastInput == 0)
            {
                shopsItem(2);
                break;
            }

            player1->getInventory()->addItem(hpPotions[lastInput - 1]->getName());
            cout << message;
            break;

        case 2:
            result << "Stamina Potions : \n";
            result << setw(20) << left << setw(20) << "  NAME"
                   << setw(20) << "PRICE"
                   << setw(20) << "STAMINA"
                   << setw(20) << "BOOST AMOUNT" << endl;
            for (int i = 0; i < staminaPotions.size(); i++)
            {
                int index = i + 1;
                result << left << index << "-" << setw(20) << staminaPotions[i]->getName()
                       << setw(20) << staminaPotions[i]->getPrice()
                       << setw(20) << staminaPotions[i]->getStamina()
                       << setw(20) << staminaPotions[i]->getSpecial() << endl;
            }

            result << backOption;
            lastInput = getInput(result.str(), 0, staminaPotions.size());
            result.str("");

            if (lastInput == 0)
            {
                shopsItem(2);
                break;
            }

            player1->getInventory()->addItem(staminaPotions[lastInput - 1]->getName());
            cout << message;
            break;

        case 3:
            result << "Power potions : \n";
            result << setw(20) << left << setw(20) << "  NAME"
                   << setw(20) << "PRICE"
                   << setw(20) << "STAMINA"
                   << setw(20) << "BOOST AMOUNT" << endl;
            for (int i = 0; i < powerPotions.size(); i++)
            {
                int index = i + 1;
                result << left << index << "-" << setw(20) << powerPotions[i]->getName()
                       << setw(20) << powerPotions[i]->getPrice()
                       << setw(20) << powerPotions[i]->getStamina()
                       << setw(20) << powerPotions[i]->getSpecial() << endl;
            }

            result << backOption;
            lastInput = getInput(result.str(), 0, powerPotions.size());
            result.str("");

            if (lastInput == 0)
            {
                shopsItem(2);
                break;
            }

            player1->getInventory()->addItem(powerPotions[lastInput - 1]->getName());
            cout << message;
            break;

        case 0:
            displayShop();
            break;
        }

        break;

    case 3:

        result << "Permenet Weapons Items\n1-Melee\n2-Firearm\n0-Back\n";
        thirdInput = getInput(result.str(), 0, 2);
        result.str("");

        switch (thirdInput)
        {
        case 1:
            result << "Melees : \n";
            result << setw(20) << left << setw(20) << "  NAME"
                   << setw(20) << "PRICE"
                   << setw(20) << "STAMINA"
                   << setw(20) << "DAMAGE" << endl;
            for (int i = 0; i < melees.size(); i++)
            {
                int index = i + 1;
                result << left << index << "-" << setw(20) << melees[i]->getName()
                       << setw(20) << melees[i]->getPrice()
                       << setw(20) << melees[i]->getStamina()
                       << setw(20) << melees[i]->getSpecial() << endl;
            }

            result << backOption;
            lastInput = getInput(result.str(), 0, melees.size());
            result.str("");

            if (lastInput == 0)
            {
                shopsItem(3);
                break;
            }

            player1->getInventory()->addItem(melees[lastInput - 1]->getName());
            cout << message;
            break;

        case 2:
            result << "Firearms : \n";
            result << setw(20) << left << setw(20) << "  NAME"
                   << setw(20) << "PRICE"
                   << setw(20) << "STAMINA"
                   << setw(20) << "DAMAGE" << endl;

            for (int i = 0; i < firearms.size(); i++)
            {
                int index = i + 1;
                result << left << index << "-" << setw(20) << firearms[i]->getName()
                       << setw(20) << firearms[i]->getPrice()
                       << setw(20) << firearms[i]->getStamina()
                       << setw(20) << firearms[i]->getSpecial() << endl;
            }

            result << backOption;
            lastInput = getInput(result.str(), 0, firearms.size());
            result.str("");

            if (lastInput == 0)
            {
                shopsItem(3);
                break;
            }

            player1->getInventory()->addItem(firearms[lastInput - 1]->getName());
            cout << message;
            break;

        case 0:
            displayShop();
        }
    }
}
