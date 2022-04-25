#pragma once
#include "../Business/Computer.h"
#include "../Business/Computer.cpp"
#include "../Structure/LinkedList.cpp"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

bool isValidCompId(int comID)
{
    ifstream inFile("./Database/ComputerDB/computer_ID.txt");
    string x;
    while (getline(inFile, x))
    {
        if (stoi(x) == comID)
        {
            return true;
        }
    }
    inFile.close();
    return false;
}

void addComputerToDatabase(Computer& computer)
{
    // generate file path
    // start from main.cpp
    string fileName = to_string(computer.ID()) + ".txt";
    string filePath = "./Database/ComputerDB/" + fileName;

    // create file in database
    ofstream outFile(filePath);
    // outFile << computer.ID() << endl;
    outFile << computer.Name() << endl;
    outFile << computer.Cpu() << endl;
    outFile << computer.Ram() << endl;
    outFile << computer.Quantity() << endl;
    outFile << computer.Price() << endl;
    outFile << computer.Sale() << endl;

    // write computerid to computer_ID.txt
    if (!isValidCompId(computer.ID()))
    {
        ofstream outFileComputerId("./Database/ComputerDB/computer_ID.txt", ios::app);
        outFileComputerId << computer.ID() << endl;
        outFileComputerId.close();
    }

    // close ofstream
    outFile.close();
}

void addNewComputerToDataBase()
{
    cout << spaceLineChoice + "New computer:\n";
    string name = getStringInput("Name");
    string cpu = getStringInput("CPU");
    string ram = getStringInput("RAM");
    int quantity = getIntInput("Quantity");
    int price = getIntInput("Price");

    // create new customer object
    Computer computer = Computer(getLastComId(), name, cpu, ram, quantity, price);

    // save to database
    addComputerToDatabase(computer);

    // update new customer id range
    updateLine("./Database/lastID.txt", 1, getLastComId());

    // generate sale and write to sale file
    ofstream outFileSale("./Database/saleSummary.txt", ios::app);
    outFileSale << computer.ID() << " " << computer.Sale() << endl;
    outFileSale.close();
}

Computer getComputerFromDatabase(int comID)
{
    // take file path
    // start from main.cpp
    string filePath = "./Database/ComputerDB/";
    string fileName = to_string(comID) + ".txt";

    ifstream inFile(filePath + fileName);
    string line;

    string name;
    string cpu;
    string ram;
    int quantity;
    int price;
    int sale;

    getline(inFile, line);
    name = line;

    getline(inFile, line);
    cpu = line;

    getline(inFile, line);
    ram = line;

    getline(inFile, line);
    quantity = stoi(line);

    getline(inFile, line);
    price = stoi(line);

    getline(inFile, line);
    sale = stoi(line);

    return Computer(comID, name, cpu, ram, quantity, price, sale);
}

void deleteComputerFromDatabase(int comID)
{
    string filePath = "./Database/ComputerDB/";
    string fileName = to_string(comID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Succesfully delete this Computer!");
        eraseFileLine(filePath + "computer_ID.txt", to_string(comID));
        eraseFileLine("./Database/saleSummary.txt", comID);
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateComputerInDatabase(int comID)
{
    Computer oldCom = getComputerFromDatabase(comID);
    Computer computer = getComputerFromDatabase(comID);
    string filePath = "./Database/ComputerDB/";
    string fileName = to_string(comID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    string name = updateComponent("Name", computer.Name());
    string cpu = updateComponent("CPU", computer.Cpu());
    string ram = updateComponent("RAM", computer.Ram());
    int quantity = updateIntComponent("Quantity", computer.Quantity());
    int price = updatePrice(computer.Price());

    computer.setID(comID);
    computer.setName(name);
    computer.setCpu(cpu);
    computer.setRam(ram);
    computer.setQuantity(quantity);
    computer.setPrice(price);
    computer.setSale(oldCom.Sale());
    
    addComputerToDatabase(computer);
}

LinkedList<Computer> getAllComputer()
{
    LinkedList<Computer> computers;

    ifstream inFile("./Database/ComputerDB/computer_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error open file computer_ID.txt!");
    }
    string x;
    while (getline(inFile, x))
    {
        Computer computer = getComputerFromDatabase(stoi(x));
        computers.addLast(computer);
    }

    inFile.close();
    return computers;
}

void printComputer(Computer computer)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("CPU");
    table.add("RAM");
    table.add("Quantity");
    table.add("Price");
    table.endOfRow();

    table.add(to_string(computer.ID()));
    table.add(computer.Name());
    table.add(computer.Cpu());
    table.add(computer.Ram());
    table.add(to_string(computer.Quantity()));
    table.add(formatCurrency(computer.Price()));
    table.endOfRow();

    cout << table << endl;
}

void printAllComputer(LinkedList<Computer> computers)
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

LinkedList<Computer> searchByCompCase(string toSearch)
{
    LinkedList<Computer> res;
    LinkedList<Computer> computers = getAllComputer();

    for (int i = 0; i < computers.length(); i++)
    {
        if (findCaseInsensitive(computers.get(i).Name(), toSearch) != string::npos)
        {
            res.addLast(computers.get(i));
        }
    }
    return res;
}

void searchByCompID()
{
    int id = getIntInput("Enter ID");
    if (!isValidCompId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        Computer computer = getComputerFromDatabase(id);
        printComputer(computer);
    }
}

void searchByCompName()
{
    string name = getStringInput("Enter name");
    LinkedList<Computer> computers = searchByCompCase(name);
    if (computers.length() > 0)
    {
        printAllComputer(computers);
    }
    else
    {
        printError("Invalid Name, please enter again!");
    }
}

void updateComputerQuantityInDatabase(int comID, int quantity)
{
    updateLine("./Database/ComputerDB/" + to_string(comID) + ".txt", 3, quantity);
}

void updateSale(int comID, int amount)
{
    ifstream inFile("./Database/saleSummary.txt");

    string sale, line;
    int firstIndex;
    while (getline(inFile, line))
    {
        firstIndex = line.find_first_of(" ");
        if (stoi(line.substr(0, firstIndex)) == comID)
        {
            break;
        }
    }

    inFile.close();

    Computer computer = getComputerFromDatabase(comID);

    int new_sale = computer.Sale() + amount;
    updateLine("./Database/saleSummary.txt", line, line.substr(0, firstIndex + 1) + to_string(new_sale));
    updateLine("./Database/ComputerDB/" + to_string(comID) + ".txt", 5, new_sale);
}

LinkedList<Computer> getSaleManagement()
{
    ifstream inFile("./Database/saleSummary.txt");
    LinkedList<Computer> computers;

    string line;
    int firstIndex;
    while (getline(inFile, line))
    {
        firstIndex = line.find_first_of(" ");
        int comID = stoi(line.substr(0, firstIndex));
        int sale = stoi(line.substr(firstIndex + 1));
        Computer computer = getComputerFromDatabase(comID);
        computers.addLast(Computer(computer.ID(), computer.Name(), computer.Cpu(), computer.Ram(), computer.Quantity(), computer.Price(), sale));
    }

    inFile.close();

    return computers;
}

void printSaleTable(LinkedList<Computer> computers)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Price");
    table.add("Total sale");
    table.endOfRow();

    double total = 0;

    for (int i = 0; i < computers.length(); i++)
    {
        Computer computer = computers.get(i);
        table.add(to_string(computer.ID()));
        table.add(computer.Name());
        table.add(formatCurrency(computer.Price()));
        table.add(formatCurrency(computer.Sale()));
        table.endOfRow();
        total += computer.Sale();
    }

    table.add("");
    table.add("");
    table.add("Total");
    table.add(formatCurrency(total));
    table.endOfRow();

    cout << table << "\n";
}