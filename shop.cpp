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
        shopsItem(2);
        break;
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
            cout << "Potions Items :\n";
            option2 = "1-Hp Potions\n2-Stamina Potions\n3-Power Potions\n4-Back\n";
            int secondInput=getInput(option2 , 1 ,4 ,true,"invalid input");
            switch (secondInput)
            {
                case 1 :
                cout << "Hp Potions : \n" ;
                    for (int i = 0; i < hpPotions.size(); i++)
                    {
                        cout << i + 1 << "- Name: " << hpPotions[i]->getName() << " Price: " << hpPotions[i]->getPrice() << " Stamina: " << hpPotions[i]->getStamina() << " HealingAmount: " << hpPotions[i]->getSpecial() << endl;
                    }
                    lastInput = getInput(backOption , 0 , hpPotions.size() , true , "Invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        else if(lastInput > 0 && lastInput <= hpPotions.size()){
                            player1->getBackpack()->addItem(hpPotions[lastInput-1]->getName());
                            cout << message ;
                        }
                        break;
                case 2:
                cout << "Stamina Potions : \n";
                    for(int i = 0; i < staminaPotions.size() ; i++){
                    cout << i + 1 << "- Name: " << staminaPotions[i]->getName() << " Price: " << staminaPotions[i]->getPrice() << " Stamina: " << staminaPotions[i]->getStamina() << " BoostAmount: " << staminaPotions[i]->getSpecial() << endl;
                }
                    lastInput = getInput(backOption , 0 , staminaPotions.size() ,true , "invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        else if(lastInput > 0 && lastInput <= hpPotions.size()){
                            player1->getBackpack()->addItem(staminaPotions[lastInput-1]->getName());
                            cout << message ;
                        }
                            break;
                case 3:
                cout << "Power potions : \n";
                    for (int i = 0; i < powerPotions.size(); i++)
                    {
                    cout << i + 1 << "- Name: " << powerPotions[i]->getName() << " Price: " << powerPotions[i]->getPrice() << " Stamina: " << powerPotions[i]->getStamina() << " empowerment: " << powerPotions[i]->getSpecial() << endl;
                    }
                    lastInput = getInput(backOption , 0 , powerPotions.size() , true , "invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        else if(lastInput > 0 && lastInput <= hpPotions.size()) {
                            player1->getBackpack()->addItem(staminaPotions[lastInput-1]->getName());
                            cout << message ;
                        }
                        break;
                case 4:
                    displayShop();
                    break;
            
    break;

    default:
        break;
    }
}}

