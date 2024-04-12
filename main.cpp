#include "headers.h"

int main()
{
    srand(time(0));
    initializeMissions();
    string starterMessage = "Switch to " + red + "full-screen mode" + reset + " for a better game experience " + cyan + "(>_*)!" + reset;
    clearScreen();
    Sleep(2000);
    cout << starterMessage;
    getch2();
    int t = 500;
    while (t)
    {
        cout << endl
             << starterMessage;
        Sleep(t);
        t /= 1.5;
    }
    while (1)
    {
        *player1 = defaultPlayer;
        // Sleep(2000);
        string username = getString(iustzTitle + "\n\nenter your usename (0 to quit): ");
        if (username == "0")
        {
            cleanUp();
            exit(0);
        }

        // set username
        player1->setUsername(username);

        ifstream data(usersFilePath);
        if (!data.is_open())
        {
            ofstream newFile(usersFilePath);
            newFile << "{}";
            newFile.close();
        }
        data.close();

        json users = loadData(usersFilePath);

        if (users[username].is_null())
        {
            clearScreen();
            cout << cyan;
            ifstream file("Stories/intro.txt");
            string line;
            while (getline(file, line))
                pprint(line);
            file.close();
            getchPress();

            // set gender
            int genderChoice = getInt(genderOptions, 1, 3);
            string gender = genders[genderChoice - 1];
            player1->setGender(gender);

            // set name
            string name = getString("what should we call you?: ", 0);
            player1->setName(name);

            // set age
            cout << "nice " << name << "! now";
            int age = getInt("enter your age: ", 1, 200, 0);
            player1->setAge(age);
        }
        else
        {
            clearScreen();
            player1->loadPlayer(users[username]);
            cout << "Welcome back, " << cyan << player1->getName() << reset << "!" << endl;
            getchPress();
        }
        menu::mainMenu();
    }
}