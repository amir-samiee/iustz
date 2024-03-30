#pragma once
#include "headers.h"

void Shop :: displayShop() {
    int input ;
    string options = "1-Throwables\n2-Potions\n3-Weapon\n\n0-Back" ; 
    
    cout << "-------------------------------------------------------------\n";
    cout << "Welcome to the shop! Here are the items available for purchase:\n";
    int firstInput = getInput(options , 0 , 3 , false , "Invalid input") ;
    cout << "-------------------------------------------------------------\n";
    
     switch (firstInput) {
        case 1:
            cout << "Throwables Items : \n";
            cout << setw(20) << left <<setw(20)<<"  NAME" 
                << setw(20) << "PRICE" 
                << setw(20) << "STAMINA" 
                << setw(20) << "DAMAGE" << endl;
            shopsItem(1);   
            
        break;
        case 2:
        shopsItem(2);
        break;
        case 3:
        shopsItem(3);
        break;
        case 0:
            menu::mainMenu();
            break;
    }
}



void Shop ::shopsItem(int choice){
    int lastInput ;
    int secondInput ;
    int thirdInput ;
    string option2 ;
    string option3 ;
    string backOption = "0-Back\n";
    string message = "Item added to your backpack!\n";
    switch (choice)
    {
    case 1: 
     cout << "Throwables Items : \n";
            for (int i = 0; i <throwables.size(); ++i){
                int index =i+1;
                std::cout << std::left <<index<<"-"<<setw(20)<<throwables[i]->getName() 
                << std::setw(20) << throwables[i]->getPrice() 
                << std::setw(20) << throwables[i]->getStamina() 
                << std::setw(20) << throwables[i]->getSpecial() << std::endl;} 
                lastInput = getInput(backOption, 0, throwables.size(), false, "Invalid input");
                if (lastInput == 0) 
                displayShop(); // Go back to main menu
            
               player1->getInventory()->addItem(throwables[lastInput - 1]->getName());
                cout << message ;
            
        break;
    case 2: 
            cout << "Potions Items :\n";
            option2 = "1-Hp Potions\n2-Stamina Potions\n3-Power Potions\n0-Back\n";
            secondInput=getInput(option2 , 0 ,3 ,false,"Invalid input");
            switch (secondInput)
            {
                case 1 :
                cout << "Hp Potions : \n" ;
                    cout << setw(20) << left <<setw(20)<<"  NAME" 
                    << setw(20) << "PRICE" 
                    << setw(20) << "STAMINA" 
                    << setw(20) << "HEALING AMOUNT" << endl;
                    for (int i = 0; i < hpPotions.size(); i++)
                    {
                    int index =i+1;
                    std::cout << std::left <<index<<"-"<<setw(20)<<hpPotions[i]->getName() 
                    << std::setw(20) << hpPotions[i]->getPrice() 
                    << std::setw(20) << hpPotions[i]->getStamina() 
                    << std::setw(20) << hpPotions[i]->getSpecial() << std::endl;
                        }
                    lastInput = getInput(backOption , 0 , hpPotions.size() , false , "Invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        
                            player1->getInventory()->addItem(hpPotions[lastInput-1]->getName());
                            cout << message ;
                        
                        break;
                case 2:
                cout << "Stamina Potions : \n"; cout << setw(20) << left <<setw(20)<<"  NAME" 
                    << setw(20) << "PRICE" 
                    << setw(20) << "STAMINA" 
                    << setw(20) << "BOOST AMOUNT" << endl;
                    for (int i = 0; i < hpPotions.size(); i++)
                    {
                    int index =i+1;
                    std::cout << std::left <<index<<"-"<<setw(20)<<staminaPotions[i]->getName() 
                    << std::setw(20) << staminaPotions[i]->getPrice() 
                    << std::setw(20) << staminaPotions[i]->getStamina() 
                    << std::setw(20) << staminaPotions[i]->getSpecial() << std::endl;
                    }
                    lastInput = getInput(backOption , 0 , staminaPotions.size() ,false , "Invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        
                            player1->getInventory()->addItem(staminaPotions[lastInput-1]->getName());
                            cout << message ;
                        
                            break;
                case 3:
                cout << "Power potions : \n";
                cout << setw(20) << left <<setw(20)<<"  NAME" 
                    << setw(20) << "PRICE" 
                    << setw(20) << "STAMINA" 
                    << setw(20) << "BOOST AMOUNT" << endl;
                    for (int i = 0; i < hpPotions.size(); i++)
                    {
                    int index =i+1;
                    std::cout << std::left <<index<<"-"<<setw(20)<<powerPotions[i]->getName() 
                    << std::setw(20) << powerPotions[i]->getPrice() 
                    << std::setw(20) << powerPotions[i]->getStamina() 
                    << std::setw(20) << powerPotions[i]->getSpecial() << std::endl;
                    }
                    lastInput = getInput(backOption , 0 , powerPotions.size() , false, "Invalid input");
                        if(lastInput == 0)
                            shopsItem(2);
                        
                            player1->getInventory()->addItem(staminaPotions[lastInput-1]->getName());
                            cout << message ;
                        
                        break;
                case 4:
                    displayShop();
                    break;}
            
    break;
    
    case 3:
            cout << "Permenet Weapons Items\n";
            option3 ="1-Melee\n2-Firearm\n0-Back";
            thirdInput = getInput(option3 , 0 , 2 , false , "Invalid input");
            switch (thirdInput)
            {
            case 1:
                cout << "Melees : \n";
                cout << setw(20) << left <<setw(20)<<"  NAME" 
                    << setw(20) << "PRICE" 
                    << setw(20) << "STAMINA" 
                    << setw(20) << "DAMAGE" << endl;
                    for (int i = 0; i < melees.size(); i++)
                    {
                    int index =i+1;
                    std::cout << std::left <<index<<"-"<<setw(20)<<melees[i]->getName() 
                    << std::setw(20) << melees[i]->getPrice() 
                    << std::setw(20) << melees[i]->getStamina() 
                    << std::setw(20) << melees[i]->getSpecial() << std::endl;
                    }
                    lastInput = getInput(backOption , 0 , melees.size() , false , "Invalid input");
                        if (lastInput == 0)
                            shopsItem(3);
                        
                            player1->getInventory()->addItem(melees[lastInput-1]->getName());
                            cout << message ;
                        
                        break;
            case 2:
            cout << "Firearms : \n" ;
            cout << setw(20) << left <<setw(20)<<"  NAME" 
                    << setw(20) << "PRICE" 
                    << setw(20) << "STAMINA" 
                    << setw(20) << "DAMAGE" << endl;
                  
                for (int i = 0; i < firearms.size(); i++)
                { 
                    int index =i+1;
                    std::cout << std::left <<index<<"-"<<setw(20)<<firearms[i]->getName() 
                    << std::setw(20) << firearms[i]->getPrice() 
                    << std::setw(20) << firearms[i]->getStamina() 
                    << std::setw(20) << firearms[i]->getSpecial() << std::endl;
                    }
                lastInput = getInput(backOption , 0 , firearms.size() , false , "Invalid input");
                    if (lastInput == 0)
                    shopsItem(3);
                    
                    player1->getInventory()->addItem(firearms[lastInput-1]->getName());
                    cout << message ;
                    
                    break;
            
            case 3:
            displayShop();
        
            }
        }
    }

