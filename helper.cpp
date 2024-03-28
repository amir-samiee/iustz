#pragma once
#include "headers.h"
using json = nlohmann::json;

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
    ":     : :: :   :: : :  " + red + "    :   " + reset + "  : :: : :  \n";

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

void cleanIntString(string &s)
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

int getInput(string options, int from, int to, bool cls = true, string errorMessage = "invalid input")
{
    string input;
    bool indexError = 0, typeError = 0, emptyString = 0;
    do
    {
        if (cls)
            clearScreen();
        if (indexError || typeError || emptyString)
            cout << red << errorMessage << reset;
        cout << endl
             << options;
        indexError = typeError = 0;
        getline(cin, input);
        if (input == "")
            emptyString = 1;
        else
        {
            emptyString = 0;
            if (isInteger(input))
            {
                cleanIntString(input);
                if (input.size() > max(to_string(to).size(), to_string(from).size()) || stoi(input) > to || stoi(input) < from)
                {
                    indexError = 1;
                    continue;
                }
                if (stoll(input) > to || stoll(input) < from)
                    indexError = 1;
            }
            else
                typeError = 1;
        }
    } while (indexError || typeError || emptyString);
    return stoi(input);
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

json loadData(string fileName)
{
    json j;
    ifstream file(fileName);
    file >> j;
    file.close();
    return j;
}

template <typename K>
void print_vector(vector<K> vec)
{
    cout << '{';
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << string(1 - (i == vec.size() - 1), ',') + string(1 - (i == vec.size() - 1), ' ');
    cout << '}' << endl;
}

void transfer(Storage *adding , Storage *to)
{
    for (auto item : adding->getItems())
        for(int i=0; i<item.second; i++)
            to->addItem(item.first);
}