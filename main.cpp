#include "headers.h"

int main()
{
    string starterMessage = "Switch to " + red + "full-screen mode" + reset + " for a better game experience " + cyan + "(>_*)!" + reset;
    clearScreen();
    Sleep(2000);
    cout << starterMessage;
    getch();
    int t = 700;
    while (t)
    {
        cout << endl
             << starterMessage;
        Sleep(t);
        t /= 1.5;
    }
    clearScreen();
    Sleep(2000);
    cout << iustzTitle << string(2, '\n') << "Enter your usename: ";
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
        // pprint("The quick brown fox jumps over the lazy dog.");
        // pprint("In the midst of chaos, there is also opportunity.");
        // pprint("Life is like riding a bicycle. To keep your balance, you must keep moving.");
        // pprint("Success is not final, failure is not fatal: It is the courage to continue that counts.");
        // pprint("Happiness depends upon ourselves.");
        // pprint("The cat sat on the mat.");
        // pprint("Tomorrow is another day.");
        // pprint("Coding is fun and challenging.");
        // pprint("Music soothes the soul.");
        // pprint("The sun sets in the west.");

        // some story ...

        cout << "what should we call you? ";
        string sinput, name; // sinput stands for string input, we take it as input everytime and if it was proper we convert it to other types
        getline(cin, name);
        cout << "nice " << name << "! now";
        int age = getInput("enter your age: ", 1, 200, 0);
    }
    menu::mainMenu();
    delete player1;
}
