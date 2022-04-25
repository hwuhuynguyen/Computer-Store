#pragma once
#include "../Business/Customer.h"
#include "../Business/Customer.cpp"
#include "../Structure/LinkedList.cpp"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

bool isValidCusId(int cusID)
{
    ifstream inFile("./Database/UserDB/CustomerDB/customer_ID.txt");
    string x;
    string line;
    while (getline(inFile, x))
    {
        line = x;
        if (stoi(line) == cusID)
        {
            return true;
        }
    }
    inFile.close();
    return false;
}

void addCustomerToDatabase(Customer& customer)
{
    // generate file path
    // start from main.cpp
    string fileName = "CUS_" + to_string(customer.ID()) + ".txt";
    string filePath = "./Database/UserDB/CustomerDB/" + fileName;

    // write customer to database
    ofstream outFile(filePath);
    outFile << customer.Name() << endl;
    outFile << customer.Email() << endl;
    outFile << customer.Password() << endl;
    for (int i = 0; i < customer.Rec().length(); i++)
    {
        outFile << customer.Rec().get(i) << endl;
    }

    // write customerid to Customer_id.txt
    if (!isValidCusId(customer.ID()))
    {
        ofstream outFileCustomerId("./Database/UserDB/CustomerDB/customer_ID.txt", ios::app);
        outFileCustomerId << customer.ID() << endl;
        outFileCustomerId.close();
    }

    // close ofstream
    outFile.close();
}

Customer addNewCustomer()
{
    cout << spaceLineChoice << "New customer:\n";

    string name = getStringInput("Name");
    string email = getEmailInput();
    while (!isUniqueEmail(email))
    {
        printError("Email already exists, please login instead!");
        system("pause");
        CustomerMenu::main();
    }
    string pwd = getPasswordInput("Password");

    // create new customer object
    Customer customer = Customer(getLastCusId(), name, email, pwd);

    // save to database
    addCustomerToDatabase(customer);

    ofstream outFile("./Database/UserDB/user_ID.txt", ios::app);
    outFile << customer.ID() << " ";
    outFile << customer.Email() << " ";
    outFile << customer.Password() << endl;
    outFile.close();

    // update new customer id range
    updateLine("./Database/lastID.txt", 0, getLastCusId());

    return customer;
}

Customer getCustomerFromDatabase(int cusID)
{
    // take file path
    // start from main.cpp
    string filePath = "./Database/UserDB/CustomerDB/";
    string fileName = "CUS_" + to_string(cusID) + ".txt";

    ifstream inFile(filePath + fileName);
    string line;

    string name;
    string email;
    string password;

    getline(inFile, line);
    name = line;

    getline(inFile, line);
    email = line;

    getline(inFile, line);
    password = line;

    LinkedList<string> recs;
    while (getline(inFile, line))
    {
        recs.addLast(line);
    }

    return Customer(cusID, name, email, password, recs);
}

void deleteCustomerFromDatabase(int cusID)
{
    Customer customer = getCustomerFromDatabase(cusID);
    
    string filePath = "./Database/UserDB/CustomerDB/";
    string fileName = "CUS_" + to_string(cusID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Successfully delete this Customer!");
        eraseFileLine(filePath + "customer_ID.txt", to_string(cusID));
        eraseFileLine("./Database/UserDB/user_ID.txt", to_string(cusID) + " " + customer.Email() + " " + customer.Password());
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateCustomerInDatabase(int cusID)
{
    Customer oldCus = getCustomerFromDatabase(cusID);
    Customer customer = getCustomerFromDatabase(cusID);

    string filePath = "./Database/UserDB/CustomerDB/";
    string fileName = "CUS_" + to_string(cusID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    string name = updateComponent("Name", customer.Name());
    string email = updateComponent("Email", customer.Email());
    string password = updatePassword(customer.Password());

    customer.setID(cusID);
    customer.setName(name);
    customer.setEmail(email);
    customer.setPassword(password);
    customer.setRec(oldCus.Rec());

    addCustomerToDatabase(customer);
    updateLine("./Database/UserDB/user_ID.txt", to_string(oldCus.ID()) + " " + oldCus.Email() + " " + oldCus.Password(), to_string(customer.ID()) + " " + customer.Email() + " " + customer.Password());
}

LinkedList<Customer> getAllCustomer()
{
    LinkedList<Customer> customers;

    ifstream inFile("./Database/UserDB/CustomerDB/customer_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error open file customer_ID.txt!");
    }
    string x;
    while (getline(inFile, x))
    {
        customers.addLast(getCustomerFromDatabase(stoi(x)));
    }

    inFile.close();
    return customers;
}

void printCustomer(Customer& customer)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Email");
    table.endOfRow();

    table.add(to_string(customer.ID()));
    table.add(customer.Name());
    table.add(customer.Email());
    table.endOfRow();

    cout << table << endl;
}

void printAllCustomer(LinkedList<Customer> customers)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Email");
    table.endOfRow();

    for (int i = 0; i < customers.length(); i++)
    {
        Customer customer = customers.get(i);
        table.add(to_string(customer.ID()));
        table.add(customer.Name());
        table.add(customer.Email());
        table.endOfRow();
    }

    cout << table << endl;
}

LinkedList<Customer> searchByCusCase(string toSearch)
{
    LinkedList<Customer> res;
    LinkedList<Customer> customers = getAllCustomer();

    for (int i = 0; i < customers.length(); i++)
    {
        Customer customer = customers.get(i);
        if (findCaseInsensitive(customer.Name(), toSearch) != string::npos)
        {
            res.addLast(customer);
        }
    }
    return res;
}

LinkedList<Customer> getCustomerNameFromDatabase(string toSearch)
{
    LinkedList<Customer> res;
    LinkedList<Customer> customers = getAllCustomer();

    for (int i = 0; i < customers.length(); i++)
    {
        Customer customer = customers.get(i);
        if (findCaseInsensitive(customer.Name(), toSearch) != string::npos)
        {
            res.addLast(customer);
        }
    }
    return res;
}

void searchByCusID()
{
    int id = getIntInput("Enter ID");
    if (!isValidCusId(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        Customer customer = getCustomerFromDatabase(id);
        printCustomer(customer);
    }
}

void searchByCusName()
{
    string name = getStringInput("Enter name");
    LinkedList<Customer> customers = searchByCusCase(name);
    if (customers.length() > 0)
    {
        printAllCustomer(customers);
    }
    else
    {
        printError("Invalid name!");
    }
}
