#pragma once
#include "Customer.h"
#include "Computer.cpp"
#include "../Management/ComputerManagement.cpp"
#include "../Management/ReceiptManagement.cpp"
#include <iostream>
using namespace std;

Customer::Customer() : User(0, "", "", "")
{
    this->_Rec = LinkedList<string>();
    this->_Cart = Cart();
}

Customer::Customer(int id, string name, string email, string password, LinkedList<string> recs) : User(id, name, email, password)
{
    this->_Rec = recs;
    this->_Cart = Cart();
}

Customer::~Customer()
{
}

Cart &Customer::getCart()
{
    return this->_Cart;
}

LinkedList<string> Customer::Rec()
{
    return this->_Rec;
}

void Customer::setRec(LinkedList<string> recs)
{
    this->_Rec = recs;
}

void Customer::purchase()
{
    string recID = "REC#" + to_string(this->_Rec.length() + 1);
    this->_Rec.addLast(recID);

    string fileName = to_string(this->ID()) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;
    ofstream outFileCus("./Database/UserDB/CustomerDB/CUS_" + to_string(this->ID()) + ".txt", ios::app);
    outFileCus << recID << endl;
    outFileCus.close();

    ofstream outFile(filePath);

    string date = currentDateTime();
    outFile << date << endl;
    outFile << _Cart.Total() << endl;

    for (int i = 0; i < _Cart.ComputerID().length(); i++)
    {
        outFile << _Cart.ComputerQuantity().get(i) << " ";
        outFile << _Cart.ComputerID().get(i) << endl;
    }

    outFile.close();
    system("cls");
    printReceipt(this->ID(), recID);

    _Cart.emptyCart();
}


void Customer::searchByReceiptID(int id)
{
    getReceiptFromDatabase(this->ID(), id);
}

void Customer::printALLCusReceipts()
{
    getAllCusReceipts(*this);
}

void Customer::addNewReceipt()
{
    addReceiptToDatabase(this->ID(), this->_Cart, this->_Rec);
}

void Customer::deleteReceiptById(string id)
{
    deleteReceiptFromDatabase(this->ID(), id);
}
