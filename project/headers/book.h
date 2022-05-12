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
        
        //Function for increasing the number of copies available in the database
        //Input: N/A
        //Output/Return: numCopies and numAvailable increase by 1
        void increaseNumCopies();

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

        friend ostream& operator<<(ostream& out, Book& otherBook);
};

#endif