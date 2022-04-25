#pragma once
#include "Computer.h"
#include <fstream>
#include <iostream>
using namespace std;

Computer::Computer()
{
    this->_ID = 0;
    this->_Name = "";
    this->_Cpu = "";
    this->_Ram = "";
    this->_Quantity = 0;
    this->_Price = 0;
    this->_Sale = 0;
}

Computer::Computer(int id, string name, string cpu, string ram, int quantity, int price, int sale)
{
    this->_ID = id;
    this->_Name = name;
    this->_Cpu = cpu;
    this->_Ram = ram;
    this->_Quantity = quantity;
    this->_Price = price;
    this->_Sale = sale;
}

Computer::Computer(const Computer& computer)
{
    this->_ID = computer._ID;
    this->_Name = computer._Name;
    this->_Cpu = computer._Cpu;
    this->_Ram = computer._Ram;
    this->_Quantity = computer._Quantity;
    this->_Price = computer._Price;
    this->_Sale = computer._Sale;
}

Computer& Computer::operator=(const Computer& computer)
{
    this->_ID = computer._ID;
    this->_Name = computer._Name;
    this->_Cpu = computer._Cpu;
    this->_Ram = computer._Ram;
    this->_Quantity = computer._Quantity;
    this->_Price = computer._Price;
    this->_Sale = computer._Sale;
    return *this;
}

Computer::~Computer()
{

}

int Computer::ID()
{
    return this->_ID;
}

void Computer::setID(int id)
{
    this->_ID = id;
}

string Computer::Name()
{
    return this->_Name;
}

void Computer::setName(string name)
{
    this->_Name = name;
}

string Computer::Cpu()
{
    return this->_Cpu;
}

void Computer::setCpu(string cpu)
{
    this->_Cpu = cpu;
}

string Computer::Ram()
{
    return this->_Ram;
}

void Computer::setRam(string ram)
{
    this->_Ram = ram;
}

int Computer::Quantity()
{
    return this->_Quantity;
}

void Computer::setQuantity(int quantity)
{
    this->_Quantity = quantity;
}

int Computer::Price()
{
    return this->_Price;
}

void Computer::setPrice(int price)
{
    this->_Price = price;
}

int Computer::Sale()
{
    return this->_Sale;
}

void Computer::setSale(int sale)
{
    this->_Sale = sale;
}
