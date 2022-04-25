#pragma once
#include <iostream>
#include <string>
using namespace std;
class User
{
    private:
        int _ID;
        string _Name;
        string _Email;
        string _Password;
    public:
        // Constructor
        User();
        User(int, string);
        User(int, string, string);
        User(int, string, string, string);

        // Destructor
        ~User();

        // Get User _Id
        int ID();

        // Set User _Id
        void setID(int);

        // Get User _Name
        string Name();

        // Set User _Name
        void setName(string);

        // Get User _Email
        string Email();

        // Set User _Email
        void setEmail(string);

        // Get User _Password
        string Password();

        // Set User _Password
        void setPassword(string);

        void searchByCompID();
        void searchByCompName();
        void printAllComputer();
};

