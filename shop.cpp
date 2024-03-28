#pragma once
#include "headers.h"

void Shop :: displayShop() {
    int input ;
    string options = "1-Throwables\n2-Potions\n3-Weapon\n" ; 
    
    cout << "-------------------------------------------------------------\n";
    cout << "Welcome to the shop! Here are the items available for purchase:\n";
    cout << "1-Throwables\n2-Potions\n3-Weapon\n4-back" ;
    cout << "-------------------------------------------------------------\n";
    
    int firstInput = getInput(options , 1 , 4 , true , "invalid input") ;
    int lastInput ;
    string backOption = "0-Back\n";
     switch (firstInput) {
        case 1:
            // Handle Throwables menu
          
            break;
        case 2:
            // Handle Potions menu
            cout << "Potions Items\n";
            break;
        case 3:
            // Handle Weapon menu
            cout << "Weapon Menu\n";
           
            break;
        case 4:
            menu::mainMenu();
            break;
        default:
            cout << "Invalid input\n Please choose again ";
            
            break;
    }
    

}
