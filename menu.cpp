#include "headers.h"
using namespace std;

namespace menu
{
    void zombies()
    {
        string zombieMissions= "\n1. Mission1 \n2. Mission2 \n3. Mission3 \n4. Mission4\n5. Mission5\n6. Mission6 \n7. Mission7 \n8. Mission8 \n9. Mission9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + zombieMissions, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    void humans()
    {
        string humanMissions = "\n1. Mission1 \n2. Mission2 \n3. Mission3 \n4. Mission4\n5. Mission5\n6. Mission6 \n7. Mission7 \n8. Mission8 \n9. Mission9\n\nenter your choice: ";
        int intInput = getInput(iustzTitle + humanMissions, 1, 9, true, "invalid input");

        switch (intInput)
        {
        }
    }

    void finale()
    {
        cout << "finale" << endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void attack()
    {   
        int intInput;
        do{
        string attacksMenu = "\n1. Zombies \n2. Humans \n3. Finale \n4. Back\nenter your choice: ";
        intInput = getInput(iustzTitle + attacksMenu, 1, 4, true, "invalid input");
        switch (intInput)
        {
        case 1:
            zombies();
            break;
        case 2:
            humans();
            break;
        case 3:
            finale();
            break;
        default:
            return;
            
        }
        }while(intInput!=4);
    }

    void shop()
    {
        cout << "Shop" << endl;
    }

    void profile()
    {
        cout << "Profile" << endl;
    }
    void configurations()
    {
        cout << "Configurations" << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void mainMenu()
    {
        int intInput;
        do
        {
        string menu = "\n1. Attack \n2. Shop \n3. Profile \n4. Configurations\n5. Exit\nenter your choice: ";
        intInput = getInput(iustzTitle + menu, 1, 5, true, "invalid input");

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
        case 4:
            configurations();
            break;
        default:
            return;
        }
        }while (intInput!=5);

    }
}
