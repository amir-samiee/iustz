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
#include<algorithm>
#include<random>

// the order of the following lines matters. make changes wisely!
#include "Assets/nlohmann/json.hpp"
#include "item.h"
#include "storage.h"
#include "character.h"
#include "mission.h"

#include "helper.cpp"
#include "item.cpp"
#include "storage.cpp"
#include "character.cpp"
#include "menu.cpp"
#include "mission.cpp"

#endif
