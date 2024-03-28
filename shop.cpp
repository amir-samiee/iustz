#pragma once
#include "headers.h"

void Shop :: displayShop() {
    int input ;
    string options = "1-Throwables\n2-Potions\n3-Weapon\n" ; 
    
    cout << "-------------------------------------------------------------\n";
    cout << "Welcome to the shop! Here are the items available for purchase:\n";
    int firstInput = getInput(options , 1 , 4 , true , "invalid input") ;
    cout << "-------------------------------------------------------------\n";
    
     switch (firstInput) {
        case 1:
        shopsItem(1);
           
            break;
        case 2:
        
          // Handle Potions menu
           
        case 3:
            // Handle Weapon menu
            cout << "Permenet weapons Items\n";
           
            break;
        case 4:
            menu::mainMenu();
            break;
        default:
            cout << "Invalid input\n Please choose again ";
            displayShop();
            break;
    }
}
void Shop ::shopsItem(int choice){
    int lastInput ;
    string option2 ;
    string backOption = "0-Back\n";
    string message = "Item added to your backpack!\n";
    switch (choice)
    {
    case 1: 
     cout << "Throwables Items : \n";
            for (int i = 0; i <throwables.size(); ++i)
            cout << i + 1 << "- Name: " << throwables[i]->getName() << " Price: " << throwables[i]->getPrice() << " Stamina: " << throwables[i]->getStamina() << " Damage: " << throwables[i]->getSpecial() << endl;
            lastInput = getInput(backOption, 0, throwables.size(), true, "Invalid input");
            if (lastInput == 0) {
                displayShop(); // Go back to main menu
            }
            else if (lastInput > 0 && lastInput <= throwables.size()) {
               player1->getBackpack()->addItem(throwables[lastInput - 1]->getName());
                cout << message ;
            }
        break;
    case 2:
    break;

    default:
        break;
    }
}

