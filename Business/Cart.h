#pragma once
#include "../Structure/LinkedList.cpp"
#include "./Computer.h"
#include "./Computer.cpp"

class Cart
{
    private:
        LinkedList<int> _ComputerId;
        LinkedList<int> _ComputerQuantity;
        int _Total;
    public:
        // Constructor
        Cart();
        
        // Destructor
        ~Cart();

        // Get list of computer ID
        LinkedList<int> ComputerID();

        // Get list of computer Quantity
        LinkedList<int> ComputerQuantity();

        // Add computer to cart
        void addComputertoCart(int, int = 1);

        // Set cart to Null for next purchase
        void emptyCart();
        
        // Set Total //Calculate total amount (money) in cart
        int Total();
};