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


        //Allows administrator to add a new book to the library database
        //Input: N/A
        //Output/Return: newBook is added to the database's list of books
        Book addBook();

        //Allows administrator to add a new book to the library database
        //Input: N/A
        //Output/Return: oldBook is removed to the database's list of books
        Book removeBook(vector<Book> books);

};

#endif