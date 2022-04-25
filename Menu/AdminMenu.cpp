#pragma once
#include "Menu.h"
#include "../Management/CustomerManagement.cpp"
#include "../Management/ComputerManagement.cpp"
#include "../Business/Admin.cpp"
#include <iostream>
#include <fstream>
void AdminMenu::printTask()
{
    ifstream inFile("./Page/AdminMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Computer Management\n";
    cout << spaceLine << "2. Customer Management\n";
    cout << spaceLine << "3. Sale Management\n";
    cout << spaceLine << "4. Log out\n";
}

void AdminMenu::searchComputer(Admin& admin)
{
    system("cls");
    ifstream inFile("./Page/AdminSearchComputer.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Search by ID\n";
    cout << spaceLine << "2. Search by Name\n";
    cout << spaceLine << "3. Back\n";
    int key = getKey(3);
    switch (key)
    {
    case 1:
    {
        admin.searchByCompID();
        system("pause");
        AdminMenu::searchComputer(admin);
    }
    break;

    case 2:
    {
        admin.searchByCompName();
        system("pause");
        AdminMenu::searchComputer(admin);
    }
    break;

    case 3:
        AdminMenu::computerManagement(admin);
        break;
    }
}

void AdminMenu::computerManagement(Admin& admin)
{
    system("cls");
    ifstream inFile("./Page/AdminComputerManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. View all computers available\n";
    cout << spaceLine << "2. Add new computer\n";
    cout << spaceLine << "3. Update computer information\n";
    cout << spaceLine << "4. Search computer information\n";
    cout << spaceLine << "5. Delete computer\n";
    cout << spaceLine << "6. Back\n";
    int key = getKey(6);
    switch (key)
    {
    case 1:
    {
        admin.printAllComputer();
        system("pause");
        AdminMenu::computerManagement(admin);
    }
    break;

    case 2:
    {
        admin.addNewComputer();
        system("pause");
        AdminMenu::computerManagement(admin);
    }
    break;

    case 3:
    {
        int comID = getIntInput("Enter the Computer ID you want to update");
        while (!isValidCompId(comID))
        {
            printError("Invalid computer ID, please enter again!");
            comID = getIntInput("Enter the Computer ID you want to update");
        }
        admin.updateComputerById(comID);
        system("pause");
        AdminMenu::computerManagement(admin);
    }
    break;

    case 4:
    {
        AdminMenu::searchComputer(admin);
        system("pause");
        AdminMenu::computerManagement(admin);
    }
    break;

    case 5:
    {
        int comID = getIntInput("Enter the Computer ID you want to delete");
        while (!isValidCompId(comID))
        {
            printError("Invalid computer ID, please enter again!");
            comID = getIntInput("Enter the Computer ID you want to update");
        }
        admin.deleteComputerById(comID);
        system("pause");
        AdminMenu::computerManagement(admin);
    }
    break;

    case 6:
        AdminMenu::menu(admin);
        break;
    }
}

void AdminMenu::searchCustomer(Admin& admin)
{
    system("cls");
    ifstream inFile("./Page/AdminSearchCustomer.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Search by ID\n";
    cout << spaceLine << "2. Search by Name\n";
    cout << spaceLine << "3. Back\n";
    int key = getKey(3);
    switch (key)
    {
    case 1:
    {
        admin.searchByCusID();
        system("pause");
        AdminMenu::searchCustomer(admin);
    }
    break;

    case 2:
    {
        admin.searchByCusName();
        system("pause");
        AdminMenu::searchCustomer(admin);
    }
    break;

    case 3:
        AdminMenu::customerManagement(admin);
        break;
    }
}

void AdminMenu::customerManagement(Admin& admin)
{
    system("cls");
    ifstream inFile("./Page/AdminCustomerManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. View all customers\n";
    cout << spaceLine << "2. Search customer information\n";
    cout << spaceLine << "3. Update customer information\n";
    cout << spaceLine << "4. Delete customer\n";
    cout << spaceLine << "5. Back\n";
    int key = getKey(5);
    switch (key)
    {
    case 1:
    {
        LinkedList<Customer> customers = getAllCustomer();
        printAllCustomer(customers);
        system("pause");
        AdminMenu::customerManagement(admin);
    }
    break;

    case 2:
    {
        searchCustomer(admin);
        system("pause");
        AdminMenu::customerManagement(admin);
    }
    break;

    case 3:
    {
        int cusID = getIntInput("Enter the Customer ID you want to update");
        while (!isValidCusId(cusID))
        {
            printError("Invalid Customer ID, please enter again!");
            cusID = getIntInput("Enter the Customer ID you want to update");
        }
        admin.updateCustomerById(cusID);
        system("pause");
        AdminMenu::customerManagement(admin);
    }
    break;

    case 4:
    {
        int cusID = getIntInput("Enter the Customer ID you want to delete");
        while (!isValidCusId(cusID))
        {
            printError("Invalid Customer ID, please enter again!");
            cusID = getIntInput("Enter the Customer ID you want to delete");
        }
        admin.deleteCustomerById(cusID);
        system("pause");
        AdminMenu::customerManagement(admin);
    }
    break;

    case 5:
        AdminMenu::menu(admin);
        break;
    }
}

void AdminMenu::saleManagement(Admin& admin)
{
    system("cls");
    ifstream inFile("./Page/AdminSaleManagement.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. View computer sales\n";
    cout << spaceLine << "2. Back\n";
    int key = getKey(2);
    switch (key)
    {
    case 1:
    {
        LinkedList<Computer> computers = getSaleManagement();
        printSaleTable(computers);
        system("pause");
        AdminMenu::saleManagement(admin);
    }
    break;

    case 2:
    {
        AdminMenu::menu(admin);
        break;
    }
    }
}

void AdminMenu::menu(Admin& admin)
{
    system("cls");
    AdminMenu::printTask();

    while (true)
    {
        int key = getKey(4);
        switch (key)
        {
        case 1:
        {
            AdminMenu::computerManagement(admin);
            system("pause");
            AdminMenu::menu(admin);
        }
        break;

        case 2:
        {
            AdminMenu::customerManagement(admin);
            system("pause");
            AdminMenu::menu(admin);
        }
        break;

        case 3:
        {
            AdminMenu::saleManagement(admin);
            system("pause");
            AdminMenu::menu(admin);
        }
        break;

        case 4:
            Home::menu();
            break;
        }
    }
}

void AdminMenu::login()
{
    system("cls");

    int id = -1;
    int time = 3;

    do
    {
        ifstream inFile("./Page/AdminLogin.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();

        string email = getEmailInput();
        string password = getPasswordInput("Password");
        if (email == "admin123@gmail.com" && password == to_string(hassPassword(to_string(123456789))))
        { 
            Admin admin;
            AdminMenu::menu(admin);
        }
        else
        {
            time--;
            if (time != 0)
            {
                printError("Wrong admin account, please enter again!");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                AdminMenu::main();
            }
        }
    } while (id = -1);
}

void AdminMenu::main()
{
    system("cls");
    ifstream inFile("./Page/Admin.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Login\n";
    cout << spaceLine << "2. Back \n";
    int key = getKey(2);
    switch (key)
    {
    case 1:
    {
        AdminMenu::login();
        system("pause");
        break;
    }

    case 2:
        Home::menu();
        break;
    }
}