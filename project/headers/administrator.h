#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <iostream>
#include <vector>
#include "..\headers\book.h"
#include "..\headers\user.h"
using namespace std;



class Administrator : public User {
    private:
        vector<Book> checkedOut;

    public:
        //Constructor
        Administrator(string name, string pass);

        //Allows administrator to checkout a book from the database
        //Input: N/A
        //Output/Return: Book object is updated to indicate book is checked out, book added to registered user's checkedOut vector
        void checkOutBook();
        
        //Allows administrator to return a checked out book to the database
        //Input: N/A
        //Output/Return: Book object is updated to indicate book is returned, book removed from registered user's checkedOut vector
        void returnBook();

        //Allows administrator to view their profile
        //Input: N/A
        //Output/Return: Information about the registered user's profile will be output to console
        void viewProfile();

        //Allows administrator to add a new book to the library database
        //Input: Book newBook: The new book that is being added to the database
        //Output/Return: newBook is added to the database's list of books
        void addBook(Book newBook);

        //Allows administrator to add a new book to the library database
        //Input: Book oldBook: The book that is being removed from the database
        //Output/Return: oldBook is removed to the database's list of books
        void removeBook(Book oldBook);

        //Overload Stream Insertion
        friend ostream& operator<<(ostream& out, Administrator& otherAdmin);
};

#endif