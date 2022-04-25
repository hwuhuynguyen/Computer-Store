#pragma once
#include "Menu.h"
#include "../Management/CustomerManagement.cpp"
#include "../Management/ComputerManagement.cpp"
#include "../Management/UserManagement.cpp"
#include "../Library/Console.cpp"
#include <iostream>
using namespace std;

void CustomerMenu::printTask()
{
    ifstream inFile("./Page/CustomerMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Account information\n";
    cout << spaceLine << "2. Update account information\n";
    cout << spaceLine << "3. View your order history\n";
    cout << spaceLine << "4. View all computers\n";
    cout << spaceLine << "5. Search computer information\n";
    cout << spaceLine << "6. Purchase computer\n";
    cout << spaceLine << "7. Log out\n";
}

void CustomerMenu::purchaseComputer(Customer &customer)
{
    system("cls");

    customer.printAllComputer();

    int comID, comQuantity, newComQuantity;
    string request;

    do
    {
        comID = getIntInput("Please enter the computer ID that you want to purchase");
        while (!isValidCompId(comID))
        {
            printError("Invalid computer ID, please enter again!");
            comID = getIntInput("Please enter the computer ID that you want to purchase");
        }
        Computer computer = getComputerFromDatabase(comID);
        comQuantity = getIntInput("Please enter the quantity you want to purchase");
        while (comQuantity > computer.Quantity() || comQuantity < 1)
        {
            printError("Invalid computer quantity, please enter again!");
            comQuantity = getIntInput("Please enter the quantity you want to purchase");
        }
        newComQuantity = computer.Quantity() - comQuantity;
        updateComputerQuantityInDatabase(comID, newComQuantity);
        updateSale(computer.ID(), computer.Price() * comQuantity);
        customer.getCart().addComputertoCart(comID, comQuantity);
        request = getYesNoInput(spaceLineChoice + "Do you want to purchase another computer (y/n)");
    } while (request == "y" || request == "Y");

    customer.purchase();
}

void CustomerMenu::search(Customer &customer)
{
    system("cls");
    ifstream inFile("./Page/CustomerSearch.txt");
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
        customer.searchByCompID();
        system("pause");
        CustomerMenu::search(customer);
    }
    break;

    case 2:
    {
        customer.searchByCompName();
        system("pause");
        CustomerMenu::search(customer);
    }
    break;

    case 3:
        CustomerMenu::menu(customer);
        break;
    }
}

void CustomerMenu::orderHistory(Customer &customer)
{
    system("cls");
    if (customer.Rec().length() == 0)
    {
        printError("You haven't purchased anything!");
        system("pause");
        CustomerMenu::menu(customer);
    }
    else
    {
        system("cls");
        customer.printALLCusReceipts();
        cout << spaceLine << "1. View receipt details by ID\n";
        cout << spaceLine << "2. Back\n";
        int key = getKey(2);
        switch (key)
        {
        case 1:
        {
            string recID = getStringInput("Enter the receipt ID you want to view details");
            while (!isValidReceiptID(recID, customer))
            {
                printError("Invalid receipt ID, please enter again!");
                recID = getStringInput("Enter the receipt ID you want to view details");
            }
            cout << endl;
            printReceipt(customer.ID(), recID);
            system("pause");
            orderHistory(customer);
        }
        break;

        case 2:
            CustomerMenu::menu(customer);
            break;
        }
    }
}

void CustomerMenu::menu(Customer &customer)
{
    system("cls");
    CustomerMenu::printTask();

    while (true)
    {
        int key = getKey(7);
        switch (key)
        {
        case 1:
        {
            customer = getCustomerFromDatabase(customer.ID());
            printCustomer(customer);
            system("pause");
            CustomerMenu::menu(customer);
        }
        break;

        case 2:
        {
            updateCustomerInDatabase(customer.ID());
            system("pause");
            CustomerMenu::menu(customer);
        }
        break;

        case 3:
            orderHistory(customer);
            break;

        case 4:
        {
            customer.printAllComputer();
            system("pause");
            CustomerMenu::menu(customer);
        }
        break;

        case 5:
        {
            search(customer);
            system("pause");
            CustomerMenu::menu(customer);
        }
        break;

        case 6:
        {
            purchaseComputer(customer);
            system("pause");
            CustomerMenu::menu(customer);
        }
        break;

        case 7:
            Home::menu();
            break;
        }
    }
}

void CustomerMenu::login()
{
    system("cls");

    int time = 3;
    int id = -1;
    do
    {
        ifstream inFile("./Page/CustomerLogin.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
        string email = getEmailInput();
        string password = getPasswordInput("Password");

        id = findUser(email, password);
        if (id == -1)
        {
            time--;
            if (time != 0)
            {
                printError("Invalid email/password, please enter again!");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                CustomerMenu::main();
            }
        }
        else
        {
            Customer customer = getCustomerFromDatabase(id);
            CustomerMenu::menu(customer);
        }
    } while (id = -1);
}

void CustomerMenu::signUp()
{
    system("cls");
    ifstream inFile("./Page/CustomerSignUp.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    Customer customer = addNewCustomer();
    CustomerMenu::menu(customer);
}

void CustomerMenu::main()
{
    system("cls");
    ifstream inFile("./Page/Customer.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    cout << spaceLine << "1. Login\n";
    cout << spaceLine << "2. Sign Up\n";
    cout << spaceLine << "3. Back\n";
    int key = getKey(3);
    switch (key)
    {
    case 1:
    {
        CustomerMenu::login();
        system("pause");
        break;
    }

    case 2:
    {
        CustomerMenu::signUp();
        system("pause");
        break;
    }

    case 3:
        Home::menu();
        break;
    }
}
