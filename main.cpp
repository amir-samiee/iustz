#include "Assets/nlohmann/json.hpp"
// #include "classes.h"
#include "helperfunctions.cpp"
#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <fstream>
using namespace std;



int main()
{
    clearScreen();
    cout << iustzTitle << string(3, '\n') << "Enter your usename: ";
    string username;
    getline(cin, username);
    json users = loadData(usersFilePath);
    if (users[username].is_null())
    {
        // uncomment to see how pprint function works
        // this part of code will be removed later

        pprint("");
        pprint("Hello, friend.");
        pprint("This is the end of the world...");
        pprint("The quick brown fox jumps over the lazy dog.");
        pprint("In the midst of chaos, there is also opportunity.");
        pprint("Life is like riding a bicycle. To keep your balance, you must keep moving.");
        pprint("Success is not final, failure is not fatal: It is the courage to continue that counts.");
        pprint("Happiness depends upon ourselves.");
        pprint("The cat sat on the mat.");
        pprint("Tomorrow is another day.");
        pprint("Coding is fun and challenging.");
        pprint("Music soothes the soul.");
        pprint("The sun sets in the west.");

        // some story ...

        cout << "what should we call you?" << endl;
        string sinput, name; // sinput stands for string input, we take it as input everytime and if it was proper we convert it to other types
        getline(cin, name);
        cout << "nice " << name << "! now ";
        int age;
        getinput(sinput, "enter your age: ", 1, 200);
        age = stoi(sinput);
    }
    // Show Menu
}