#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include "../Management/ComputerManagement.cpp"
using namespace std;

User::User()
{
    this->_ID = 0;
    this->_Name = "";
    this->_Email = "";
    this->_Password = "";
}

User::User(int _ID, string _Password)
{
    this->_ID = _ID;
    this->_Password = _Password;
}

User::User(int _ID, string _Email, string _Password)
{
    this->_ID = _ID;
    this->_Email = _Email;
    this->_Password = _Password;
}

User::User(int _ID, string _Name, string _Email, string _Password)
{
    this->_ID = _ID;
    this->_Name = _Name;
    this->_Email = _Email;
    this->_Password = _Password;
}

User::~User()
{

}

int User::ID()
{
    return this->_ID;
}

void User::setID(int _ID)
{
    this->_ID = _ID;
}

string User::Name()
{
    return this->_Name;
}

void User::setName(string _Name)
{
    this->_Name = _Name;
}

string User::Email()
{
    return this->_Email;
}

void User::setEmail(string _Email)
{
    this->_Email = _Email;
}

string User::Password()
{
    return this->_Password;
}

void User::setPassword(string _Password)
{
    this->_Password = _Password;
}


void User::searchByCompID()
{
  int id = getIntInput("Enter ID");
  if (!isValidCompId(id))
  {
    printError("Invalid ID, please enter again!");
  }
  else
  {
    Computer computer = getComputerFromDatabase(id);
    cout << endl;
    printComputer(computer);
  }
}

void User::searchByCompName()
{
  string name = getStringInput("Enter name");
  LinkedList<Computer> computers = searchByCompCase(name);
  cout << endl;
  if (computers.length() > 0)
  {
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("CPU");
    table.add("RAM");
    table.add("Quantity");
    table.add("Price");
    table.endOfRow();
    for (int i = 0; i < computers.length(); i++)
    {
        Computer computer = computers.get(i);
        table.add(to_string(computer.ID()));
        table.add(computer.Name());
        table.add(computer.Cpu());
        table.add(computer.Ram());
        table.add(to_string(computer.Quantity()));
        table.add(formatCurrency(computer.Price()));
        table.endOfRow();
    }

    cout << table << endl;
  }
  else
  {
    printError("Invalid Name, please enter again!");
  }
}

void User::printAllComputer()
{
  LinkedList<Computer> computers = getAllComputer();
  TextTable table;

  table.add("ID");
  table.add("Name");
  table.add("CPU");
  table.add("RAM");
  table.add("Quantity");
  table.add("Price");
  table.endOfRow();
  for (int i = 0; i < computers.length(); i++)
  {
    Computer computer = computers.get(i);
    table.add(to_string(computer.ID()));
    table.add(computer.Name());
    table.add(computer.Cpu());
    table.add(computer.Ram());
    table.add(to_string(computer.Quantity()));
    table.add(formatCurrency(computer.Price()));
    table.endOfRow();
  }

  cout << table << endl;
}