#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H
#include <iostream>
#include <vector>
#include "..\headers\book.h"
#include "..\headers\user.h"
using namespace std;



class RegisteredUser : public User {
    public:
        //Constructor
        RegisteredUser(string id, string pass);

        //Allows registered user to checkout a book from the database
        //Input: N/A
        //Output/Return: Book object is updated to indicate book is checked out, book added to registered user's checkedOut vector
        void checkOutBook();
        
        //Allows registered user to return a checked out book to the database
        //Input: N/A
        //Output/Return: Book object is updated to indicate book is returned, book removed from registered user's checkedOut vector
        void returnBook();

        //Allows registered user to view their profile
        //Input: N/A
        //Output/Return: Information about the registered user's profile will be output to console
        void viewProfile();        
};

#endif