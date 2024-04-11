#pragma once
#ifndef HEADERS_H
#define HEADERS_H

using namespace std;
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctype.h>
#include <conio.h>
#include <vector>
#include <random>
#include <regex>
#include <ctime>
#include <map>

#include "Assets/nlohmann/json.hpp"

// the order of the following lines matters. make changes wisely!
#include "helper.h"
#include "item.h"
#include "storage.h"
#include "character.h"
#include "mission.h"
#include "shop.h"
#include "fsm.h"

#include "helper.cpp"
#include "item.cpp"
#include "storage.cpp"
#include "character.cpp"
#include "mission.cpp"
#include "menu.cpp"
#include "shop.cpp"
#include "fsm.cpp"

#endif
