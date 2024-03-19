#include "../headers.h"

int main()
{
    cout << endl
         << "tester proogram started ...\n"
         << endl;

    Player player1("rostam", 24, "male", LimitedStorage(), Stat(), Stat(), 1, 2, 1, vector<Character *>{}, 200, Storage(), 3, 3);
    Enemy player2("sohrab", 24, "male", LimitedStorage(), Stat(), Stat(), 1, 2, 1, vector<Character *>{dynamic_cast<Character *>(&player1)}, 200);
    player1.setWave(vector<Character *>{dynamic_cast<Character *>(&player2)});

    cout << player1.getStamina()->getCurrentPoint() << endl;
    cout << player2.getHp()->getCurrentPoint() << endl;
    throwable6.setOwner(&player1);
    // throwable1.checkAndTakeStamina();
    throwable6.useItem();
    cout << player1.getStamina()->getCurrentPoint() << endl;
    cout << player2.getHp()->getCurrentPoint() << endl;

    Storage allItems;
    map<string, int> allItemsMap;
    for (auto i : itemsMap)
    {
        allItemsMap.insert({i.first, 1});
    }
    allItems.setItems(allItemsMap);
    allItems.printStorage();

    cout << "\nthrowable items:" << endl;
    for (auto i : throwables)
    {
        cout << "\t" << i->getName() << endl;
    }

    cout << "\nconsumable items:" << endl;
    for (auto i : consumables)
    {
        cout << "\t" << i->getName() << endl;
    }

    cout << "\npermanent items:" << endl;
    for (auto i : permanents)
    {
        cout << "\t" << i->getName() << endl;
    }
}