#include "Assets/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
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

json loadData(string filename)
{
    json j;
    ifstream file(filename);
    file >> j;
    file.close();
    return j;
}

int main()
{
    system("cls");
    cout << iustzTitle << string(3, '\n') << "Enter your usename: ";
    string username;
    getline(cin, username);
    json users = loadData(usersFilePath);
    if (users[username].is_null())
        cout << "Hello for the first time";
    else
        cout << "Hello old frined";
}