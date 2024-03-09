#include "Assets/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctype.h>
using namespace std;
using json = nlohmann::json;

const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");

const string usersFilePath = "Data/users.json";
const string iustzTitle =
    "@@@  @@@  @@@   @@@@@@ " + red + " @@@@@@#" + reset + "  @@@@@@@@  \n" +
    "@@@  @@@  @@@  @@@@@@@ " + red + " @@@@@@@" + reset + "  @@@@@@@@  \n" +
    "@@!  @@!  @@@  !@@     " + red + "   @#!  " + reset + "       @@!  \n" +
    "!@!  !@!  @!@  !@!     " + red + "   @@!  " + reset + "      !@!   \n" +
    "!!@  @!@  !@!  !!@@!!  " + red + "   @!!  " + reset + "     @!!    \n" +
    "!!!  !@!  !!!   !!@!!! " + red + "   !!!  " + reset + "    !!!     \n" +
    "!!:  !!:  !!!       !:!" + red + "   !!:  " + reset + "   !!:      \n" +
    ":!:  :!:  !:!      !:! " + red + "   :!:  " + reset + "  :!:       \n" +
    "::  ::::::::  :::: ::  " + red + "   ::   " + reset + "  :: ::::   \n" +
    ":     : :: :   :: : :  " + red + "    :   " + reset + "  : :: : :  ";

void clearScreen()
{
    system("cls");
}

void pprint(string text, int milliseconds = -1, bool goNextLine = 1)
{
    cout << text << ((goNextLine) ? "\n" : "");
    if (milliseconds == -1)
        milliseconds = text.size() * 80;
    Sleep(milliseconds);
}

bool isInteger(string s)
{
    for (int i = 1; i < s.size(); i++)
        if (!isdigit(s[i]))
            return 0;
    if (!(isdigit(s[0]) || s[0] == '-'))
        return 0;
    if (s == "-")
        return 0;
    return 1;
}

bool isZero(string s)
{
    for (int i = 1; i < s.size(); i++)
        if (s[i] != '0')
            return 0;
    if (!(s[0] == '0' || s[0] == '-'))
        return 0;
    return 1;
}

void cleanintstring(string &s)
{
    if (isZero(s))
    {
        s = "0";
        return;
    }
    while (1)
    {
        int size = s.size();
        if (s[0] == '0')
            s = s.substr(1, size);
        else if (s[0] == '-' && size >= 2 && s[1] == '0')
            s = '-' + s.substr(2, size);
        else
            break;
    }
}

void getinput(string &input, string options, int from, int to, bool cls = 0, string indexerrormessage = "index error", bool exceptzero = 0)
{
    bool indexerror = 0, typeerror = 0, emptystring = 0;
    do
    {
        if (cls)
            clearScreen();
        if (indexerror || typeerror || emptystring)
            cout << red << "invalid input" << reset << endl;
        cout << options;
        indexerror = typeerror = 0;
        getline(cin, input);
        if (input == "")
            emptystring = 1;
        else
        {
            emptystring = 0;
            if (isInteger(input))
            {
                cleanintstring(input);
                if (input.size() > max(to_string(to).size(), to_string(from).size()) || stoi(input) > to || stoi(input) < from)
                    indexerror = 1;
                if (exceptzero && input == "0")
                    indexerror = 0;
            }
            else
                typeerror = 1;
        }
    } while (indexerror || typeerror || emptystring);
}

template <typename element, typename list>
bool isIn(element x, list A)
{
    for (auto i : A)
    {
        if (i == x)
            return 1;
    }
    return 0;
}

json loadData(string filename)
{
    json j;
    ifstream file(filename);
    file >> j;
    file.close();
    return j;
}
