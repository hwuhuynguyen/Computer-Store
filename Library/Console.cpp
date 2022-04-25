#pragma once
#include "Table.cpp"
#include "../Structure/LinkedList.cpp"
#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <set>
#include <fstream>
#include <algorithm>
#include <conio.h>
using namespace std;
string spaceLine = "\t\t         ";
string spaceLineChoice = "\t    ";
// Check if string s is a number
bool isNumber(string s)
{
    char *end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}

// Get current datetime
// real time
string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);

    return buf;
}

unsigned long long hassPassword(string password)
{
    hash<string> hash;
    return hash(password);
}

// Check if string email is valid email form
bool isEmail(string email)
{
    int dot = -1, at = -1;
    for (int i = email.length() - 1; i >= 0; --i)
    {
        if (email[i] == '@')
        {
            at = i;
        }
        if (email[i] == '.')
        {
            dot = i;
        }
    }
    if (dot != -1 && at != -1 && at < dot)
    {
        return true;
    }
    return false;
}

// Change text color in terminal
void printLineColor(string line, int color_code)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, color_code);
    cout << line;
    SetConsoleTextAttribute(color, 7);
}

// Print notification
void printError(string status)
{
    cout << spaceLineChoice;
    printLineColor(" ERROR ", 67);
    printLineColor(" " + status, 4);
    cout << endl;
}

// Print notification
void printSuccess(string status)
{
    cout << spaceLineChoice;
    printLineColor(" SUCCESS ", 37);
    printLineColor(" " + status, 2);
    cout << endl;
}

// Get input with int type
int getIntInput(string title)
{
    string value;
    printLineColor(spaceLineChoice + title + ": ", 6);
    getline(cin, value);

    while (!isNumber(value))
    {
        printError("Invalid value!");
        printLineColor(spaceLineChoice + title + ": ", 6);
        getline(cin, value);
    }

    return stoi(value);
}

// Get input with string type
string getStringInput(string title)
{
    string value;

    printLineColor(spaceLineChoice + title + ": ", 6);
    getline(cin, value);

    return value;
}

string getEmailInput()
{
    string email;
    printLineColor(spaceLineChoice + "Email: ", 6);
    getline(cin, email);

    while (!isEmail(email))
    {
        printError("Invalid email!");
        printLineColor(spaceLineChoice + "Email: ", 6);
        getline(cin, email);
    }

    return email;
}

string getPasswordInput(string title)
{
    printLineColor(spaceLineChoice + title + ": ", 6);
    string pwd = "";
    char a = getch();
    while (a != 10 && a != 13)
    {
        if (a != 8)
        {
            cout << '*';
            pwd += a;
            a = getch();
        }
        else if (pwd.length() > 0)
        {
            cout << "\b \b";
            pwd = pwd.erase(pwd.size() - 1);
            a = getch();
        }
        else
        {
            a = getch();
        }
    }

    cout << endl;
    return to_string(hassPassword((string)pwd));
}

// Get input with yes/no
string getYesNoInput(string title)
{
    string yn;

    printLineColor(title + ": ", 3);
    getline(cin, yn);

    while (yn != "y" && yn != "Y" && yn != "n" && yn != "N")
    {
        printError("You must enter a valid value (y/n)!");
        printLineColor(title + ": ", 3);
        getline(cin, yn);
    }

    return yn;
}
// Format int
string formatInt(int num)
{
    string s = to_string(num);
    string ans = "";
    for (int i = s.length() - 1; i >= 0; i -= 3)
    {
        if (i > 2)
        {
            string sub = s.substr(i - 3 + 1, 3);
            ans = sub + ans;
            ans = "," + ans;
        }
        else
        {
            string sub = s.substr(0, i + 1);
            ans = sub + ans;
        }
    }
    return ans;
}

// Format money in VND
string formatCurrency(int price)
{
    return formatInt(price) + " VND";
}

// Update component with y/n
string updateComponent(string key, string value)
{
    string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(value + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    string newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getStringInput("New " + key);
    }

    return newValue;
}

// Update int component with y/n
int updateIntComponent(string key, int value)
{
    string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(to_string(value) + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    int newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getIntInput("New " + key);
    }

    return newValue;
}

// Update price
// old_price: current price
int updatePrice(int old_price)
{
    printLineColor(spaceLineChoice + "Price: ", 6);
    printLineColor(to_string(old_price) + "\n", 7);
    int new_price = old_price;

    string yn = getYesNoInput(spaceLineChoice + "Update Price (y/n)");

    if (yn == "y" || yn == "Y")
    {
        new_price = getIntInput("Price");
    }

    return new_price;
}

// Update password
// old_pass: current password value
string updatePassword(string old_pass)
{
    string yn = getYesNoInput(spaceLineChoice + "Update Password (y/n)");

    if (yn == "n" || yn == "N")
    {
        return old_pass;
    }

    string old_pass_input = getPasswordInput("Enter old password");

    while (old_pass != old_pass_input)
    {
        printError("Wrong password!");
        old_pass_input = getPasswordInput("Enter old password");
    }

    string new_password = getPasswordInput("Enter new password");

    return new_password;
}
// Get key available
int getKey(int maxKey)
{
    cout << endl;
    int key = getIntInput("Your choice");

    while (key < 1 || key > maxKey)
    {
        printError("Invalid key!");
        key = getIntInput("Your choice");
    }

    cout << endl;
    return key;
}

// Find position of a piece of data in a string
// case insensitive
// data: string
// toSearch: string need to search
// pos: start position to search in data
size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    return data.find(toSearch, pos);
}

LinkedList<string> getAllEmail()
{
    LinkedList<string> list;
    set<string> emails;

    ifstream inFile("./Database/UserDB/user_ID.txt");
    string line;
    int first, last;

    while (getline(inFile, line))
    {
        first = line.find_first_of(" ");
        last = line.find_last_of(" ");

        string email = line.substr(first + 1, last - first - 1);
        emails.insert(email);
    }

    set<string>::iterator it;
    for (it = emails.begin(); it != emails.end(); ++it)
    {
        string mail = *it;
        list.addLast(mail);
    }

    inFile.close();
    return list;
}

bool isUniqueEmail(string emailToCheck)
{
    LinkedList<string> emails = getAllEmail();
    for (int i = 0; i < emails.length(); i++)
    {
        string email = emails.get(i);
        if (emailToCheck == email)
        {
            return false;
        }
    }
    return true;
}

int getLastCusId()
{
    ifstream inFile("./Database/lastID.txt");

    string x;
    getline(inFile, x);

    return stoi(x) + 1;
}

int getLastComId()
{
    ifstream inFile("./Database/lastID.txt");

    string x;
    getline(inFile, x);
    getline(inFile, x);

    return stoi(x) + 1;
}

string getReceiptDateTime(int cusID, string recID)
{
    ifstream inFile("./Database/ReceiptDB/" + to_string(cusID) + "_" + recID + ".txt") ;

    string x;
    getline(inFile,x);

    return x;
}

int getReceiptTotal(int cusID, string recID)
{
    ifstream inFile("./Database/ReceiptDB/" + to_string(cusID) + "_" + recID + ".txt");

    string x;
    getline(inFile, x);
    getline(inFile, x);

    return stoi(x);
}

// Update line input in file
// path: path to file in database, start from main.cpp file
// numLine: index of line, start from 0
// replaceValue: new line value
void updateLine(string path, int numLine, int replaceValue)
{
    string line;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");
    int count = 0;

    while (getline(fin, line))
    {
        if (count == numLine)
        {
            temp << replaceValue << endl;
            count++;
            continue;
        }
        temp << line << endl;
        count++;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Update line input in file
// path: path to file in database, start from main.cpp file
// inLine: line to update
// replaceValue: new line value
void updateLine(string path, string inLine, string replaceValue)
{
    string line;
    ifstream fin;

    fin.open(path);
    if (!fin.is_open())
    {
        printError("Eror open file" + path);
    }
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line == inLine)
        {
            temp << replaceValue << endl;
            continue;
        }
        temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line to delete
void eraseFileLine(string path, string eraseLine)
{
    string line;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line != eraseLine)
            temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line contain int item to delete
void eraseFileLine(string path, int eraseLine)
{
    string line;
    int firstIndex;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        firstIndex = line.find_first_of(" ");
        if (line.substr(0, firstIndex) != to_string(eraseLine))
            temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
