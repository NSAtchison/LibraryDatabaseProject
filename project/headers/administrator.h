#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <iostream>
#include <vector>
#include "book.h"
#include "user.h"
using namespace std;



class Administrator : public User {
    public:
        //Constructor
        Administrator(string name, string pass);



        // //Allows administrator to view their profile
        // //Input: N/A
        // //Output/Return: Information about the registered user's profile will be output to console
        // void viewProfile();

        // //Allows administrator to add a new book to the library database
        // //Input: Book newBook: The new book that is being added to the database
        // //Output/Return: newBook is added to the database's list of books
        // void addBook(Book newBook);

        // //Allows administrator to add a new book to the library database
        // //Input: Book oldBook: The book that is being removed from the database
        // //Output/Return: oldBook is removed to the database's list of books
        // void removeBook(Book oldBook);

};

#endif