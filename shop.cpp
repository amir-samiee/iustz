#pragma once
#include "headers.h"

void Shop :: displayShop() {
    int input ;
    string options = "1-Throwables\n2-Potions\n3-Weapon\n\n4-Back" ; 
    
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
        shopsItem(3);
        break;
        case 4:
            menu::mainMenu();
            break;
    }
}



void Shop ::shopsItem(int choice){
    int lastInput ;
    string option2 ;
    string option3 ;
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
                    break;}
            
    break;
    case 3:
            cout << "Permenet Weapons Items\n";
            option3 ="1-Melee \n 2-Firearm \n 3-Back";
            int thirdInput = getInput(option3 , 1 , 3 , true , "invalid input");
            switch (thirdInput)
            {
            case 1:
                cout << "Melees : \n";
                    for (int i = 0; i < melees.size(); i++)
                    {
                        cout << i + 1 << "- Name: " << melees[i]->getName() << " Price: " << melees[i]->getPrice() << " Stamina: " << melees[i]->getStamina() << " Damage: " << melees[i]->getSpecial() << endl;
                    }
                    lastInput = getInput(backOption , 0 , melees.size() , true , "invalid input");
                        if (lastInput == 0)
                            shopsItem(3);
                        else if (lastInput > 0 && lastInput <= melees.size())
                        {
                            player1->getBackpack()->addItem(melees[lastInput-1]->getName());
                            cout << message ;
                        }
                        break;
            case 2:
            cout << "Firearms : \n" ;
                for (int i = 0; i < firearms.size(); i++)
                {
                    cout << i + 1 << "- Name: " << firearms[i]->getName() << " Price: " << firearms[i]->getPrice() << " Stamina: " << firearms[i]->getStamina() << " Damage: " << firearms[i]->getSpecial() << endl;
                }
                lastInput = getInput(backOption , 0 , firearms.size() , true , "invalid input");
                    if (lastInput == 0)
                    shopsItem(3);
                    else if (lastInput > 0 && lastInput <= firearms.size())
                    {
                    player1->getBackpack()->addItem(firearms[lastInput-1]->getName());
                    cout << message ;
                    }
                    break;
            
            case 3:
            displayShop();
        
            }
        }
    }

