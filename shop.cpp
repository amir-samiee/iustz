#pragma once
#include "headers.h"

void Shop::displayShop()
{
    while (1)
    {
        stringstream data;
        data << "Welcome to the shop! You can buy and sell items here:\n";
        data << green << "1- Buy" << reset << endl;
        data << red << "2- Sell" << reset << endl;
        data << "\n0- Back\n";
        data << "\nenter your choice: ";
        int choice = getInt(data.str(), 0, 2);
        switch (choice)
        {
        case 0:
            return;
        case 1:
            displayBuy();
            break;
        case 2:
            displaySell();
            break;
        }
    }
}

void Shop::displaySell()
{
    while (1)
    {
        stringstream data;
        data << "COINS: " << player1->getCoins() << endl
             << endl;
        data << "Here are the items you can sell:\n";
        data << "Inventory:" << endl;
        data << player1->getInventory()->getStorageData("", "- ", 1);
        data << "\n\n 0- Back\n";
        data << "\nenter your choice: ";
        int choice = getInt(data.str(), 0, player1->getInventory()->getNames().size());
        if (choice == 0)
            return;
        clearScreen();
        string itemName = player1->getInventory()->getNames()[choice - 1];
        player1->getInventory()->removeItem(itemName);
        player1->setCoins(player1->getCoins() + (itemsMap[itemName]->getPrice() * 0.7));
        cout << green << itemName << " sold!" << reset << endl;
        getchPress();
    }
}
void Shop::displayBuy()
{
    while (1)
    {
        string options1 = "Here are the items available for purchase:\n";
        options1 += "1- Throwables\n2- Potions\n3- Weapons\n4- Upgrade\n\n0- Back\nenter your choice: ";
        int firstInput = getInt(options1, 0, 4);
        int secondInput;
        string options2;
        string option3;

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
                secondInput = getInt(options2, 0, 3);
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
                options2 = "Permenet Weapons Items\n1- Melees\n2- Firearms\n0- Back\n\nenter your choice: ";
                secondInput = getInt(options2, 0, 2);
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
        case 4: // upgrade
            upgrade();
            break;
        case 0: // Back
            return;
            break;
        }
    }
}

void Shop::subShop(vector<Item *> shopItems, string title, string special)
{
    const string backOption = " 0- Back\n";
    while (1)
    {
        int maxLength = 8;
        for (int i = 0; i < shopItems.size(); ++i)
        {
            string itemName = shopItems[i]->getName();
            if (itemName.size() > maxLength)
                maxLength = itemName.size();
        }
        stringstream result;
        result << "COINS: " << player1->getCoins() << endl
               << endl;
        result << title << endl;
        result << left
               << setw(maxLength + 5) << "    NAME" << right
               << setw(20) << "PRICE"
               << setw(20) << "STAMINA"
               << setw(20) << special << endl;
        for (int i = 0; i < shopItems.size(); ++i)
        {
            int index = i + 1;
            Item *item = shopItems[i];
            result << right << setw(2) << index << "- " << left
                   << setw(maxLength + 5) << item->getName() << right
                   << setw(15) << item->getPrice() << string(5, ' ')
                   << setw(14) << item->getStamina() << string(6, ' ')
                   << setw(14) << item->getSpecial() << endl;
        }
        result << backOption << endl
               << "enetr your choice: ";
        int input = getInt(result.str(), 0, shopItems.size());

        if (input == 0)
            return;

        buy(shopItems[input - 1]);
    }
}

void Shop::buy(Item *item)
{
    string itemName = item->getName();
    clearScreen();
    int newCoin = player1->getCoins() - item->getPrice();
    map<string, int> backpackItems = player1->getBackpack()->getItems();
    map<string, int> inventoryItems = player1->getInventory()->getItems();
    if (dynamic_cast<Permanent *>(item) != nullptr && (backpackItems[itemName] != 0 || inventoryItems[itemName] != 0))
        cout << red << "You already own this permanent item!" << reset << endl;
    else if (newCoin < 0)

        cout << red << "Insufficient coins! You need to gather more coins to acquire this item!" << reset << endl;
    else
    {
        player1->getInventory()->addItem((item)->getName());
        player1->setCoins(newCoin);
        cout << green << "Item added to your inventory!" << reset << endl;
    }
    getchPress();
}

void Shop ::upgrade()
{
    while (1)
    {
        stringstream result;
        string result1;
        int secondInput;

        result << "COINS: " << player1->getCoins() << endl
               << endl;

        result << left << "   NAME " << right << setw(20)
               << "LEVEL" << setw(20)
               << "ESCALATION" << setw(20)
               << "PRICE" << endl;

        result << "1- Hp" << setw(21)
               << player1->getHp()->level()
               << setw(22) << "1 =30 hp"
               << setw(18) << upgradePrice("hp", player1->getHp()->level()) << endl;

        result << "2- Stamina" << setw(16)
               << player1->getStamina()->level()
               << setw(24) << "1 = 30 stamina"
               << setw(16) << upgradePrice("stamina", player1->getStamina()->level()) << endl;

        result << "3- Firearm Level" << setw(10)
               << player1->getFirearmLevel() << setw(23)
               << "1 = 1 level" << setw(17)
               << upgradePrice("firearm", player1->getFirearmLevel()) << endl;

        result << "4- Melee Level" << setw(12)
               << player1->getMeleeLevel() << setw(23)
               << "1 = 1 level" << setw(17)
               << upgradePrice("melee", player1->getMeleeLevel()) << endl;

        result1 = result.str() + "\n0- Back\nenter your choice : ";
        secondInput = getInt(result1, 0, 4);
        clearScreen();
        switch (secondInput)
        {
        case 1:
        {
            int upgradeCost = upgradePrice("hp", player1->getHp()->level());
            if (player1->getCoins() >= upgradeCost)
            {
                // Deduct the upgrade cost from player's coins
                player1->setCoins(player1->getCoins() - upgradeCost);
                // Perform the upgrade
                player1->getHp()->setMaxPoint(player1->getHp()->getMaxPoint() + 30);
                cout << green << "Hp upgraded successfully!" << reset << endl;
                getchPress();
            }
            else
            {
                cout << red << "Not enough coins to upgrade Hp." << reset << endl;
                getchPress();
            }
            break;
        }
        case 2:
        {
            int upgradeCost = upgradePrice("stamina", player1->getStamina()->level());
            if (player1->getCoins() >= upgradeCost)
            {
                // Deduct the upgrade cost from player's coins
                player1->setCoins(player1->getCoins() - upgradeCost);
                // Perform the upgrade
                player1->getStamina()->setMaxPoint(player1->getStamina()->getMaxPoint() + 30);
                cout << green << "Stamina upgraded successfully!" << reset << endl;
                getchPress();
            }
            else
            {
                cout << red << "Not enough coins to upgrade Stamina." << reset << endl;
                getchPress();
            }
            break;
        }
        case 3:
        {
            int upgradeCost = upgradePrice("firearm", player1->getFirearmLevel());
            if (player1->getCoins() >= upgradeCost)
            {
                // Deduct the upgrade cost from player's coins
                player1->setCoins(player1->getCoins() - upgradeCost);
                // Perform the upgrade
                player1->setFirearmLevel(player1->getFirearmLevel() + 1);
                cout << green << "Firearm level upgraded successfully!" << reset << endl;
                getchPress();
            }
            else
            {
                cout << red << "Not enough coins to upgrade Firearm level." << reset << endl;
                getchPress();
            }
            break;
        }
        case 4:
        {
            int upgradeCost = upgradePrice("melee", player1->getMeleeLevel());
            if (player1->getCoins() >= upgradeCost)
            {
                // Deduct the upgrade cost from player's coins
                player1->setCoins(player1->getCoins() - upgradeCost);
                // Perform the upgrade
                player1->setMeleeLevel(player1->getMeleeLevel() + 1);
                cout << green << "Melee level upgraded successfully!" << reset << endl;
                getchPress();
            }
            else
            {
                cout << red << "Not enough coins to upgrade Melee level." << reset << endl;
                getchPress();
            }
            break;
        }
        case 0:
            return;
        }
    }
}

int Shop::upgradePrice(string type, int choice)
{
    int upgradeResult;
    if (type == "hp")
    {
        upgradeResult = 15 + (choice - 1) * 15;
        return upgradeResult;
    }
    else if (type == "stamina")
    {
        upgradeResult = 10 + (choice - 1) * 10;
        return upgradeResult;
    }
    else if (type == "firearm")
    {
        upgradeResult = 25 * pow(1.5, choice - 1);
        return upgradeResult;
    }
    else if (type == "melee")
    {
        upgradeResult = 20 * pow(1.2, choice - 1);
        return upgradeResult;
    }
    else
        cout << "\ncan't upgrade price" << endl;

    return 0;
}
