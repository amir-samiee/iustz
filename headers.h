#pragma once
#ifndef HEADERS_H
#define HEADERS_H

using namespace std;
#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <sstream>
#include<conio.h>


const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");

// the order of the following lines matters. make changes wisely!
#include "Assets/nlohmann/json.hpp"
#include "item.h"
#include "storage.h"
#include "character.h"
#include "mission.h"

#include "item.cpp"
#include "storage.cpp"
#include "helper.cpp"
#include "character.cpp"
#include "menu.cpp"
#include "mission.cpp"

#endif
