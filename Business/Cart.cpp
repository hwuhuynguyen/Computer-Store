#pragma once
#include "Cart.h"
#include "../Management/ComputerManagement.cpp"
#include "../Library/Table.cpp"
#include "../Library/Console.cpp"

Cart::Cart()
{
    this->_Total = 0;
}

Cart::~Cart()
{

}

LinkedList<int> Cart::ComputerID()
{
    return this->_ComputerId;
}

LinkedList<int> Cart::ComputerQuantity()
{
    return this->_ComputerQuantity;
}

int Cart::Total()
{
    int total = 0;
    for (int i = 0; i < this->_ComputerId.length(); i++)
    {
        Computer computer = getComputerFromDatabase(this->_ComputerId.get(i));
        total += computer.Price() * this->_ComputerQuantity.get(i);
    }
    return total;
}

void Cart::addComputertoCart(int id, int quantity)
{
    this->_ComputerId.addLast(id);
    this->_ComputerQuantity.addLast(quantity);
}

void Cart::emptyCart()
{
    this->_ComputerId = LinkedList<int>();
    this->_ComputerQuantity = LinkedList<int>();
    this->_Total = 0;
}






