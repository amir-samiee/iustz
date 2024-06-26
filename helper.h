#pragma once
#include "headers.h"
using json = nlohmann::json;

random_device rd;
mt19937 gen(rd());

const vector<string> genders = {"male", "female", "other"};
string genderOptions = "Please choose your gender... "
                       "\n1. Male"
                       "\n2. Female"
                       "\n3. Other"
                       "\n\nenter your choice: ";

const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string gray("\033[90m");
const string reset("\033[0m");
const string white("\033[97m");
const string blink("\033[5m");
const string strikethrough("\033[9m");

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

void clearScreen();
void pprint(string text, int milliseconds = -1, bool storyMode = 1);

bool isInteger(string s);
bool isZero(string s);

void cleanIntString(string &s);

int getInt(string options, int from, int to, bool cls = true, string errorMessage = "invalid input");
string getString(string message, bool cls = 1);

class Storage;
void transfer(Storage *adding, Storage *to);

template <typename element, typename list>
bool isIn(element x, list A);

template <typename K>
void dumpData(string fileName, K data, ios_base::openmode mode = ios::out);

json loadData(string fileName);
void getch2();

template <typename K>
void print_vector(vector<K> vec);

void save();
void cleanUp();

void removeUsername(string username);
bool changeUsername(string oldUsername, string newUsername);

void getchPress();
string currentTime();

string removeColors(string input);
inline int mapSize(map<string, int> items);