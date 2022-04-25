#pragma once
#include <iostream>
#include <string>
using namespace std;

class Computer
{
    private:
        int _ID;
        string _Name;
        string _Cpu;
        string _Ram;
        int _Quantity;
        int _Price;
        int _Sale;
    public: 
        // Constructor
        Computer();
        Computer(int, string, string, string, int , int, int = 0);
        Computer(const Computer&);

        // Overloading the assignment operator
        Computer& operator=(const Computer&);

        // Destructor
        ~Computer();

        // Get, Set Computer _ID
        int ID();
        void setID(int);

        // Get, Set Computer _Spec
        string Name();
        void setName(string);

        // Get, Set Computer _Cpu
        string Cpu();
        void setCpu(string);

        // Get, Set Computer _Ram
        string Ram();
        void setRam(string);

        // Get, Set Computer Quantity
        int Quantity();
        void setQuantity(int);

        // Get, SetComputer Price
        int Price();
        void setPrice(int);

        // Get, Set Computer Sale
        int Sale();
        void setSale(int);
};