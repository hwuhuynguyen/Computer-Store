#pragma once
#include <iostream>
#include "User.h"
#include "Customer.h"
#include "Computer.h"
#include "../Structure/LinkedList.cpp"

using namespace std;

class Admin: public User
{
    public:
        // Constructor
        Admin();
        Admin(int, string, string, string);

        // Destructor
        ~Admin();

        // Method
        // User getUserLoginInfo(string);
        // LinkedList<User> getAllUserLoginInfo();

        // Manage Customer
        void searchByCusID();
        void searchByCusName();
        void printAllCustomer();
        void updateCustomerById(int);
        void deleteCustomerById(int);

        // Manage Computer
        void addNewComputer();
        void updateComputerById(int);
        void deleteComputerById(int);

};
    
