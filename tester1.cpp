#include "headers.h"

int main()
{

    Enemy *p2 = new Enemy("hamid", 21, "other", LimitedStorage(), Stat(), Stat(), 1, 1, 1, vector<Character *>{player1}, 12);
    Enemy *p3 = new Enemy("navid", 21, "other", LimitedStorage(), Stat(), Stat(), 1, 1, 1, vector<Character *>{player1}, 12);
    // player1->setWave(vector<Character *>{p2, p3});
    // // player1->getStamina()->setCurrentPoint(5);
    // player1->getBackpack()->setItems(map<string, int>{
    //     {"Punch", 1},
    //     {throwable5.getName(), 4},
    //     {staminaPotion2.getName(), 3},
    //     {powerPotion4.getName(), 2}});
    // while (1)
    // {
    //     // cout << player1->getStamina()->getCurrentPoint() << endl;
    //     player1->display();
    //     player1->turn();
    //     player1->takeDamage(35);
    // }

    // cout << player1->getBackpack()->getSize() << endl;
    // map<string, int> newS = {{"Punch", 22}};
    // player1->getBackpack()->setItems(map<string, int>{{"Punch", 12}});
    // player1->getBackpack()->addItem(throwable3.getName());
    // player1->getBackpack()->printStorage();
    // cout << player1->getStamina()->getCurrentPoint() << endl;
    // cout << p2->getHp()->getCurrentPoint() << endl;
    // throwable3.setOwner(player1);
    // throwable3.useItem();
    // cout << player1->getStamina()->getCurrentPoint() << endl;
    // cout << p2->getHp()->getCurrentPoint() << endl;
    // cout << p3->getHp()->getCurrentPoint() << endl;
    delete p3;
    delete p2;
    delete player1;

    vector<Item *> em;
}

// string name;
// int age;
// string gender; // -male -female -other
// LimitedStorage backpack;
// Stat hp;
// Stat stamina;
// int firearmLevel = 1;
// int meleeLevel = 1;
// double powerBoost = 1;
// int coins;
// vector<Character *> currentWave;
// Storage reward;
// Storage inventory;
// int humanLevels = 0;
// int zombieLevels = 0;