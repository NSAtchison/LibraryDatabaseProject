#ifndef BOOK_H
#define BOOK_H
#include <iostream>
using namespace std;



class Book {
    private:
        string title;
        string author;
        string genre;
        string pageLink;
        int numPages;
        int numCopies; //Number of copies of this book registered in the database
        int numAvailable; //Number of copies of this book available in the database

    public:
        //Default Constructor
        Book();

        //Variable Constructor
        Book(string name, string writer, string type, string link, int pages);

        //Variable Constructor 2
        Book(string name, string writer, string type, string link, int pages, int numAvail, int numCop);

        //Copy Constructor
        Book(const Book& copy);
        
        //Function for increasing the number of total copies of a book in the database
        //Input: N/A
        //Output/Return: numCopies and numAvailable increase by 1
        void updateNumCopies(int num);

        //Function that updates the number of available copies of a book in the database
        //Input: N/A
        //Output/Return: numAvailable increase by 1
        void updateNumAvailable(int num);

        //Function that prints all of the books information
        //Input: N/A
        //Output/Return: The books information is printed to console
        //               An int with value of either 1 or 2 is returned to indicate whether the book is to be checked out
        int printInfo();

        //Getters
        string getTitle();
        string getAuthor();
        string getGenre();
        string getLink();
        int getNumPages();
        int getNumAvailabe();
        int getNumCopies();

        //Setters
        void setTitle(string name);
        void setAuthor(string name);
        void setGenre(string name);
        void setNumPages(int num);

        //Operator Overload
        friend ostream& operator<<(ostream& out, Book& otherBook);
};

#endif