#pragma once
#include "headers.h"

void Shop::displayShop()
{
    while (1)
    {
        string options1 = "Welcome to the shop! Here are the items available for purchase:\n";
        options1 += "1- Throwables\n2- Potions\n3- Weapons\n\n0- Back\nenter your choice: ";
        int firstInput = getInput(options1, 0, 3);
        int secondInput;
        string options2;

        bool breakFlag = 0;
        switch (firstInput)
        {
        case 1: // Throwables
            subShop(throwables, "Throwable Items:", "DAMAGE");
            break;
        case 2: // Potions
            while (!breakFlag)
            {
                options2 = "Potions Items :\n1- Hp Potions\n2- Stamina Potions\n3- Power Potions\n0- Back\n\nenter your choice: ";
                secondInput = getInput(options2, 0, 3);
                switch (secondInput)
                {
                case 1:
                    subShop(hpPotions, "HP Potions:", "BOOST");
                    break;
                case 2:
                    subShop(staminaPotions, "Stamina Potions:", "BOOST");
                    break;
                case 3:
                    subShop(powerPotions, "Power potions:", "BOOST");
                    break;
                case 0:
                    breakFlag = 1;
                    break;
                }
            }
            break;
        case 3: // Weapons
            while (!breakFlag)
            {
                options2 = "Permenet Weapons Items\n1-Melee\n2-Firearm\n0-Back\n\nenter your choice: ";
                secondInput = getInput(options2, 0, 2);
                switch (secondInput)
                {
                case 1:
                    subShop(melees, "Melees:", "DAMAGE");
                    break;
                case 2:
                    subShop(firearms, "Firearms:", "DAMAGE");
                    break;
                case 0:
                    breakFlag = 1;
                    break;
                }
            }
            break;
        case 0: // Back
            return;
        }
    }
}

template <class K>
void Shop::subShop(vector<K> items, string title, string special)
{
    string backOption = "0- Back\n";
    string message = "Item added to your backpack!\n";
    stringstream result;
    result << title << endl;
    result << left
           << setw(20) << "  NAME"
           << setw(20) << "PRICE"
           << setw(20) << "STAMINA"
           << setw(20) << special << endl;
    for (int i = 0; i < items.size(); ++i)
    {
        int index = i + 1;
        result << left << index << "-" << setw(20) << items[i]->getName()
               << setw(20) << items[i]->getPrice()
               << setw(20) << items[i]->getStamina()
               << setw(20) << items[i]->getSpecial() << endl;
    }
    result << backOption << endl
           << "enetr your choice: ";
    int input = getInput(result.str(), 0, items.size());

    if (input == 0)
        return;
    buy(input, items);
}

template <class K>
void Shop::buy(int input, vector<K> items)
{
    string message = "Item added to your backpack!\n";
    if (player1->getCoins() >= items[input - 1]->getPrice())
    {
        player1->getInventory()->addItem(items[input - 1]->getName());
        int newCoins = player1->getCoins() - items[input - 1]->getPrice();
        player1->setCoins(newCoins);
        cout << message << endl;
    }
    else
        cout << "Insufficient coins! You need to gather more coins to acquire this item" << endl;
}