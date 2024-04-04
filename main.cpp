#include "headers.h"

int main()
{
    initializeMissions();
    // string starterMessage = "Switch to " + red + "full-screen mode" + reset + " for a better game experience " + cyan + "(>_*)!" + reset;
    // clearScreen();
    // Sleep(2000);
    // cout << starterMessage;
    // getch();
    // int t = 500;
    // while (t)
    // {
    //     cout << endl
    //          << starterMessage;
    //     Sleep(t);
    //     t /= 1.5;
    // }
    while (1)
    {
        *player1 = defaultPlayer;
        clearScreen();
        // Sleep(2000);
        cout << iustzTitle << string(2, '\n') << "Enter your usename (q to quit): ";
        string username;
        getline(cin, username);
        if (username == "q")
        {
            cleanUp();
            exit(0);
        }

        // set username
        player1->setUsername(username);

        json users = loadData(usersFilePath);

        if (users[username].is_null() == true)
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

            // set gender
            int genderChoice = getInput(genderOptions, 1, 3, 0);
            string gender = genders[genderChoice - 1];
            player1->setGender(gender);

            // set name
            cout << "what should we call you? ";
            string name;
            getline(cin, name);
            player1->setName(name);

            // set age
            cout << "nice " << name << "! now";
            int age = getInput("enter your age: ", 1, 200, 0);
            player1->setAge(age);
        }
        else
        {
            player1->loadPlayer(users[username]);
            clearScreen();
            cout << "Welcome back, " << cyan << player1->getName() << reset << "!" << endl;
            getchpress();
        }
        menu::mainMenu();
    }
}