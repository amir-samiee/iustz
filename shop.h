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
    template<class K>
    static void buy(int input , vector<K>items);
};

Shop shop;