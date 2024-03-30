#pragma once
#include "headers.h"

class Shop
{
protected:
    void shopsItem(int choice);

public:
    // methods
    template <class K>
    static void subShop(vector<K> items, string title, string special);
    void displayShop();
    void buy();
};
