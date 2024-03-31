#pragma once
#include "headers.h"

class Shop
{
protected:

public:
    // methods
    template <class K>
    static void subShop(vector<K> items, string title, string special);
    void displayShop();
    void buy();
};

Shop shop;