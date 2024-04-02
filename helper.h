#pragma once
#include "headers.h"
using json = nlohmann::json;

random_device rd;
mt19937 gen(rd());

const vector<string> genders = {"male", "female", "other"};

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
    ":     : :: :   :: : :  " + red + "    :   " + reset + "  : :: : :  \n";

void clearScreen();
void pprint(string text, int milliseconds = -1, bool goNextLine = 1);

bool isInteger(string s);
bool isZero(string s);

void cleanIntString(string &s);
int getInput(string options, int from, int to, bool cls = true, string errorMessage = "invalid input");

class Storage;
void transfer(Storage *adding, Storage *to);

template <typename element, typename list>
bool isIn(element x, list A);

json loadData(string fileName);

template <typename K>
void print_vector(vector<K> vec);