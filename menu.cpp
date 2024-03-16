#include "headers.h"
using namespace std;

namespace menu
{
    void zombies()
    {
        string menu = "\n1. Missin1 \n2. Missin2 \n3. Missin3 \n4. Missin4\n5. Missin5\n6. Missin6 \n7. Missin7 \n8. Missin8 \n9. Missin9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    void humans()
    {
        string menu = "\n1. Missin1 \n2. Missin2 \n3. Missin3 \n4. Missin4\n5. Missin5\n6. Missin6 \n7. Missin7 \n8. Missin8 \n9. Missin9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void finale()
    {
        cout << "finale" << endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void attack()
    {
        string menu = "\n1. Zombies \n2. Humans \n3. Final \n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 3, true, "invalid input");
        switch (intInput)
        {
        case 1:
            zombies();
            break;
        case 2:
            humans();
            break;
        default:
            finale();
        }
    }

    void shop()
    {
        cout << "Shop" << endl;
    }

    void Profile()
    {
        cout << "Profile" << endl;
    }
    void Configurations()
    {
        cout << "Configurations" << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void mainMenu()
    {
        string menu = "\n1. Attack \n2. Shop \n3. Profile \n4. Configurations\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 4, true, "invalid input");

        switch (intInput)
        {
        case 1:
            attack();
            break;
        case 2:
            shop();
            break;
        case 3:
            profile();
            break;
        default:
            configurations();
        }
    }
}

