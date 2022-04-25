#pragma once
#include "../Business/Customer.h"
#include "../Business/Admin.h"

class Home
{
    public:
        static void printTask();
        static void login();
        static void signUp();
        static void menu();
};

class CustomerMenu
{
    public: 
        static void printTask();
        static void search(Customer&);
        static void purchaseComputer(Customer&);
        static void orderHistory(Customer&);
        static void menu(Customer&);
        static void login();
        static void signUp();
        static void main();
};

class AdminMenu
{
    public:
        static void printTask();
        static void searchComputer(Admin&);
        static void computerManagement(Admin&);
        static void searchCustomer(Admin&);
        static void customerManagement(Admin&);
        static void saleManagement(Admin&);
        static void menu(Admin&);
        static void login();
        static void main();
};

