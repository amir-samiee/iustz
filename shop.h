#pragma once
#include "headers.h"

class Shop
{
protected:
public:
    // methods
    static void subShop(vector<Item *> items, string title, string special);
    void displayShop();
    static void buy(Item* shopItem);
};

Shop shop;