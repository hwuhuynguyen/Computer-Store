#pragma once
#include "../Library/Console.cpp"
#include "../Business/Computer.cpp"
#include "./CustomerManagement.cpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

string lineReceiptFormat(string key, string info)
{
    string s = key;
    int n = 57 - key.length() - info.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + info;
    s = "|   " + s + "   |";
    return s;
}

string lineReceiptFormat(string qty, string item, string amount)
{
    string s = qty;
    int n = 6 - qty.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + item;
    int m = 57 - s.length() - amount.length();
    for (int i = 0; i < m; i++)
    {
        s += " ";
    }
    s = s + amount;
    s = "|   " + s + "   |";
    return s;
}

void printReceipt(int cusID, string recID)
{
    ifstream inFile("./Page/Receipt.txt");
    ifstream inFileRec("./Database/ReceiptDB/" + to_string(cusID) + "_" + recID + ".txt");
    
    string line;
    string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("No.", recID) << endl;
    
    getline(inFileRec, lineRec);
    cout << lineReceiptFormat("Terminal.", lineRec) << endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    int quantity, comID, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex)); 
        comID = stoi(lineRec.substr(firstIndex + 1));
        Computer computer = getComputerFromDatabase(comID);
        amount = quantity * computer.Price();
        cout << lineReceiptFormat(to_string(quantity), computer.Name(), formatCurrency(amount)) << endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << endl;

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFileRec.close();
    inFile.close();
}

bool isValidReceiptID(string recID, Customer& customer)
{
    LinkedList<string> recs = customer.Rec();

    for (int i = 0; i < recs.length(); i++)
    {
        if (recs.get(i) == recID)
        {
            return true;
        }
    }
    return false;
}

void getReceiptFromDatabase(int cusID, int recID)
{
    ifstream inFile("./Page/Receipt.txt");
    ifstream inFileRec("./Database/ReceiptDB/" + to_string(cusID) + "_" + to_string(recID) + ".txt");
    
    string line;
    string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("No.", to_string(recID)) << endl;
    
    getline(inFileRec, lineRec);
    cout << lineReceiptFormat("Terminal.", lineRec) << endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    int quantity, comID, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex)); 
        comID = stoi(lineRec.substr(firstIndex + 1));
        Computer computer = getComputerFromDatabase(comID);
        amount = quantity * computer.Price();
        cout << lineReceiptFormat(to_string(quantity), computer.Name(), formatCurrency(amount)) << endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        cout << line << endl;
    }

    cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << endl;

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFileRec.close();
    inFile.close();
}

void getAllCusReceipts(Customer& customer)
{
    TextTable table;
    int n = customer.Rec().length();

    table.add("ID");
    table.add("Name");
    table.add("Receipt ID");
    table.add("Total");
    table.add("Datetime");
    table.endOfRow();

    table.add(to_string(customer.ID()));
    table.add(customer.Name());
    table.add(customer.Rec().get(n - 1));
    table.add(formatCurrency(getReceiptTotal(customer.ID(), customer.Rec().get(n - 1))));
    table.add(getReceiptDateTime(customer.ID(), customer.Rec().get(n - 1)));
    table.endOfRow();

    int total = 0;
    total += getReceiptTotal(customer.ID(), customer.Rec().get(n - 1));

    for (int i = n - 2; i >= 0; i--)
    {
        table.add(" ");
        table.add(" ");
        table.add(customer.Rec().get(i));
        table.add(formatCurrency(getReceiptTotal(customer.ID(), customer.Rec().get(i))));
        table.add(getReceiptDateTime(customer.ID(), customer.Rec().get(i)));
        table.endOfRow();
        total += getReceiptTotal(customer.ID(), customer.Rec().get(i));
    }

    
    table.add("");
    table.add("");
    table.add("Total amount");
    table.add(formatCurrency(total));
    table.add("");
    table.endOfRow();

    cout << table << endl;
}

void addReceiptToDatabase(int cusID, Cart _Cart, LinkedList<string> Rec)
{
    string recID = "REC#" + to_string(Rec.length() + 1);
    Rec.addLast(recID);

    string fileName = to_string(cusID) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;
    ofstream outFileCus("./Database/UserDB/CustomerDB/CUS_" + to_string(cusID) + ".txt", ios::app);
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
    printReceipt(cusID, recID);

    // _Cart.emptyCart();
}

void deleteReceiptFromDatabase(int cusID, string recID)
{
    string fileName = to_string(cusID) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Succesfully delete this Receipt!");
    }
    else
    {
        printError("Delete failed!");
    }
}
