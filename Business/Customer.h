#pragma once
#include "User.cpp"
#include "Cart.cpp"
#include "../Structure/LinkedList.cpp"
class Customer: public User
{
    private:
        Cart _Cart;
        LinkedList<string> _Rec;
    public: 
        // Constructor
        Customer();
        Customer(int, string, string, string, LinkedList<string> = LinkedList<string>());

        // Destructor
        ~Customer();

        //Info
        void displayInfo();
        void updateInfo();

        // Get customer item in Cart
        Cart& getCart();

        // Get list of receipt ID
        LinkedList<string> Rec();

        // Set list of receipt ID
        void setRec(LinkedList<string>);

        void newCustomer();

        // Function to purchase computers for each customer
        void purchase();
        
        // void printALLCusReceipts();

        // Cart (CRUD)

        // Receipt (CRUD)

        // Computer (List, Search, Buy)

        // Receipt (CRUD)
        void searchByReceiptID(int);
        // void searchByCompName(string);
        void printALLCusReceipts();
        // void printReceipt(int);
        void addNewReceipt();
        void deleteReceiptById(string);
};