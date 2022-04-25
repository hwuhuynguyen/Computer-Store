#pragma once
#include "Admin.h"
#include "../Management/CustomerManagement.cpp"
#include "../Management/ComputerManagement.cpp"

Admin::Admin() : User()
{
}

Admin::Admin(int id, string name, string email, string password) : User(id, name, email, password)
{
}

Admin::~Admin()
{
}

void Admin::searchByCusID()
{
    int id = getIntInput("Enter ID");
    if (!isValidCusId(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        cout << endl;

        Customer customer = getCustomerFromDatabase(id);

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
}

void Admin::searchByCusName()
{
    string name = getStringInput("Enter name");
    LinkedList<Customer> customers = getCustomerNameFromDatabase(name);
    if (customers.length() > 0)
    {
        cout << endl;

        TextTable table;

        for (int i = 0; i < customers.length(); i++)
        {
            table.add("ID");
            table.add("Name");
            table.add("Email");
            table.endOfRow();

            Customer customer = customers.get(i);

            cout << customer.ID();
            table.add(to_string(customer.ID()));
            table.add(customer.Name());
            table.add(customer.Email());
            table.endOfRow();
        }
        
        cout << table << endl;
    }
    else
    {
        printError("Invalid name!");
    }
}

void Admin::printAllCustomer()
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Email");
    table.endOfRow();
    LinkedList<Customer> customers = getAllCustomer();
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

void Admin::updateCustomerById(int id)
{
    if (!isValidCusId(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        updateCustomerInDatabase(id);
    }
}

void Admin::deleteCustomerById(int id)
{
    if (!isValidCusId(id))
    {
        printError("Invalid ID!");
    }
    else
    {
        deleteCustomerFromDatabase(id);
    }
}

void Admin::addNewComputer()
{
    addNewComputerToDataBase();
}

void Admin::updateComputerById(int id)
{
    if (!isValidCompId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        updateComputerInDatabase(id);
    }
}

void Admin::deleteComputerById(int id)
{
    if (!isValidCompId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        deleteComputerFromDatabase(id);
    }
}