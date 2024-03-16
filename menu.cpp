#include "headers.h"
using namespace std;

namespace menu
{
    void Zombies()
    {
        string menu = "\n1. Missin1 \n2. Missin2 \n3. Missin3 \n4. Missin4\n5. Missin5\n6. Missin6 \n7. Missin7 \n8. Missin8 \n9. Missin9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    void Humans()
    {
        string menu = "\n1. Missin1 \n2. Missin2 \n3. Missin3 \n4. Missin4\n5. Missin5\n6. Missin6 \n7. Missin7 \n8. Missin8 \n9. Missin9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Finale()
    {
        cout << "Finale" << endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Attack()
    {
        string menu = "\n1. Zombies \n2. Humans \n3. Final \n\nenter your choice: ";
        int intInput = getInput(iustzTitle + menu, 1, 3, true, "invalid input");
        switch (intInput)
        {
        case 1:
            Zombies();
            break;
        case 2:
            Humans();
            break;
        default:
            Finale();
        }
    }

    void Shop()
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
            Attack();
            break;
        case 2:
            Shop();
            break;
        case 3:
            Profile();
            break;
        default:
            Configurations();
        }
    }
}

