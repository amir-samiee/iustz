#include "headers.h"

int main()
{
    LimitedStorage *backpack = player1->getBackpack();
    Storage *inventory = player1->getInventory();
    // arshiya khar ast
    player1->setReward(Storage(map<string, int>{{"EMP", 4}}));
    backpack->addItem(map<string, int>{{"EMP", 3}});

    backpack->printStorage();
    inventory->printStorage();
    if (player1->isAlive())
    {
        LimitedStorage temp = *backpack;
        transfer(backpack, inventory);
        transfer(player1->getReward(), inventory);
        inventory->removeItem(temp.getItems());
        transfer(&temp, backpack);
    }
    else
    {
        cout << "dead" << endl;
        player1->getReward()->setItems({});
    }
    backpack->printStorage();
    inventory->printStorage();
    cleanUp();
}