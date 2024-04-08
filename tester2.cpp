#include "headers.h"

int main()
{
    // player1->getBackpack()->addItem(throwable1.getName());
    // player1->getBackpack()->addItem(throwable1.getName());
    // player1->getBackpack()->addItem(throwable2.getName());
    // player1->getBackpack()->addItem(throwable2.getName());
    // player1->getBackpack()->addItem(throwable2.getName());
    // player1->getBackpack()->addItem(throwable2.getName());
    // player1->getBackpack()->addItem(throwable3.getName());
    // player1->getBackpack()->addItem(fireArm8.getName());
    // player1->getBackpack()->addItem(fireArm8.getName());
    // player1->getBackpack()->addItem(fireArm8.getName());
    // player1->getBackpack()->addItem(fireArm8.getName());
    // player1->getInventory()->addItem(melee2.getName());
    // player1->getInventory()->addItem(melee3.getName());
    // player1->getInventory()->addItem(melee3.getName());
    // player1->getInventory()->addItem(melee9.getName());
    // player1->getInventory()->addItem(melee10.getName());
    // player1->getInventory()->addItem(staminaPotion4.getName());
    // player1->getInventory()->addItem(staminaPotion4.getName());
    // player1->getInventory()->addItem(staminaPotion4.getName());

    // menu::inventory();
    // menu::mainMenu();
    // json data = loadData(usersFilePath);
    // player1->loadPlayer(data["username"]);
    // player1->display();
    // getch();
    // menu::inventory();

    // for (int i = 0; i < 5; i++)
    // {
    //     HumanMission *m = new HumanMission(i + 1, 0);
    //     // HumanMission m(i + 1, 1);
    //     m->setName("name " + to_string(i));
    //     // humanMissions.push_back(&m);
    // }

    initializeMissions();
    player1->getBackpack()->addItem(throwable5.getName());
    player1->getBackpack()->addItem(fireArm10.getName());
    player1->getHp()->setMaxPoint(100000);
    player1->getHp()->fill();
    player1->getStamina()->setMaxPoint(100000);
    player1->getStamina()->fill();
    // menu::missionSelect(zombieMissions);
    zombieMissions[0]->start();
    // zombieMissions[0]->display();
    cleanUp();

    // for (int i = 0; i < 5; i++)
    //     delete humanMissions[i];
}