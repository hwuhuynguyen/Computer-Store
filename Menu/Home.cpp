#pragma once
#include <fstream>
#include "Menu.h"
#include "./AdminMenu.cpp"
#include "./CustomerMenu.cpp"
// string spaceLine = "\t\t         ";
void Home::printTask()
{
    ifstream inFile("./Page/MainPage.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Admin\n";
    cout << spaceLine << "2. Customer\n";
    cout << spaceLine << "3. Exit\n";
}

void Home::menu()
{
    system("cls");
    Home::printTask();

    int key = getKey(3);
    switch (key)
    {
    case 1:
        AdminMenu::main();
        system("pause");
        break;

    case 2:
        CustomerMenu::main();
        system("pause");
        break;

    case 3:
        exit(0);
        break;
    }
}
