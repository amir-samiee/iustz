#pragma once
#include "headers.h"
using json = nlohmann::json;

void clearScreen()
{
    system("cls");
}

void pprint(string text, int milliseconds, bool storyMode)
{
    if (storyMode)
        for (auto i : text)
        {
            cout << i;
            Sleep(5);
        }
    else
        cout << text;
    if (milliseconds == -1)
        milliseconds = text.size() * 60;
    Sleep(milliseconds);
    cout << endl;
}

bool isInteger(string s)
{
    for (int i = 1; i < s.size(); i++)
        if (!isdigit(s[i]))
            return 0;
    if (!(isdigit(s[0]) || s[0] == '-' || s[0] == '+'))
        return 0;
    if (s == "-" || s == "+")
        return 0;
    return 1;
}

bool isZero(string s)
{
    for (int i = 1; i < s.size(); i++)
        if (s[i] != '0')
            return 0;
    if (!(s[0] == '0' || s.find("-0") == 0 || s.find("+0") == 0))
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
        char start = s[0];
        switch (start)
        {
        case '0':
        case '+':
            s = s.substr(1, size);
            break;
        case '-':
            if (size > 2 && s[1] == '0')
            {
                s = start + s.substr(2, size);
                break;
            }
        default:
            return;
        }
    }
}

int getInt(string options, int from, int to, bool cls, string errorMessage)
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

string getString(string message, bool cls)
{
    string input;
    bool error = 0;
    while (1)
    {
        if (cls)
            clearScreen();
        if (error)
            cout << red << "invalid input" << reset;
        cout << endl
             << message;
        getline(cin, input);
        if (input != "")
            return input;
        else
            error = 1;
    }
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

// handles arrow keys so they don't pre-waste the next getch()
void getch2()
{
    int ch = getch();
    if (ch == 0 || ch == 224)
        getch();
}

template <typename K>
void dumpData(string fileName, K data, ios_base::openmode mode)
{
    ofstream file(fileName, mode);
    if (is_same<K, json>::value)
        file << setw(2);
    file << data << endl;
    file.close();
}

template <typename K>
void print_vector(vector<K> vec)
{
    cout << '{';
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << string(1 - (i == vec.size() - 1), ',') + string(1 - (i == vec.size() - 1), ' ');
    cout << '}' << endl;
}

void transfer(Storage *adding, Storage *to)
{
    to->addItem(adding->getItems());
    adding->clearStorage();
}

void save()
{
    json data = loadData(usersFilePath);
    data[player1->getUsername()] = player1->dumpPlayer();
    dumpData(usersFilePath, data);
}

void cleanUp()
{
    cout << cyan << "exiting cleanly..." << endl;
    delete player1;
    cout << "player cleared..." << endl;
    for (auto i : zombieMissions)
        delete i;
    cout << "zombie missions cleared..." << endl;
    for (auto i : humanMissions)
        delete i;
    cout << "human missions cleared..." << endl;
    cout << green << "done!" << reset << endl;
}

void removeUsername(string username)
{
    json data = loadData(usersFilePath);
    data.erase(username);
    dumpData(usersFilePath, data);
}

bool changeUsername(string oldUsername, string newUsername)
{
    json data = loadData(usersFilePath);
    if (!data[newUsername].is_null())
        return 0;
    data[newUsername] = data[oldUsername];
    data.erase(oldUsername);
    dumpData(usersFilePath, data);
    return 1;
}

void getchPress()
{
    cout << yellow << "\nPlease press any key to continue... " << reset << endl;
    getch2();
}

string currentTime()
{
    time_t now = time(0);
    string dateTime = ctime(&now);
    dateTime.pop_back();
    return dateTime;
}

string removeColors(string input)
{
    regex colorRegex("\033\\[[0-9;]+m");
    return regex_replace(input, colorRegex, "");
}

int mapSize(map<string, int> items)
{
    int newSize = 0;
    for (auto i : items)
        newSize += i.second;
    return newSize;
}