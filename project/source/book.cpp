#include <iostream>
#include "book.h"
using namespace std;

//Default Constructor
Book::Book() {
    title = "None";
    author = "None";
    genre = "None";
    pageLink = "None";
    numPages = 0;
    numAvailable = 0;
    numCopies = 0;
}

//Variable Constructor
Book::Book(string name, string writer, string type, string link, int pages) {
    title = name;
    author = writer;
    genre = type;
    pageLink = link;
    numPages = pages;
    numAvailable = 0;
    numCopies = 0;
}

Book::Book(string name, string writer, string type, string link, int pages, int numAvail, int numCop) {
    title = name;
    author = writer;
    genre = type;
    pageLink = link;
    numPages = pages;
    numAvailable = numAvail;
    numCopies = numCop;
}

Book::Book(const Book& copy) {
    title = copy.title;
    author = copy.author;
    genre = copy.genre;
    pageLink = copy.pageLink;
    numPages = copy.numPages;
    numAvailable = copy.numAvailable;
    numCopies = copy.numCopies;
}

//Function for increasing the number of copies available in the database
//Input: N/A
//Output/Return: numCopies and numAvailable increase by 1
void Book::increaseNumCopies() {
    numCopies++;
    numAvailable++;
}

//Getters
string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
string Book::getGenre() { return genre; }
string Book::getLink() { return pageLink; }
int Book::getNumPages() { return numPages; }
int Book::getNumAvailabe() { return numAvailable; }
int Book::getNumCopies() { return numCopies; }

//Setters
void Book::setTitle(string name) { title = name; }
void Book::setAuthor(string name) { author = name; }
void Book::setGenre(string name) { genre = name; }
void Book::setNumPages(int num) { numPages = num; }

int Book::printInfo() {
    int userSelection;
    cout << "______________________" << endl;
    cout << "|  Book Information  |" << endl;
    cout << "|--------------------|" << endl;
    cout << " Book Title: " << title << endl;
    cout << " Author: " << author << endl;
    cout << " Genre: " << genre << endl;
    cout << " Number of Pages: " << numPages << endl;
    cout << " Number of Available Copies: " << numAvailable << "/" << numCopies << endl;
    cout << " If you want to read more about this book, you can find additional information at:" << endl;
    cout << " " << pageLink << endl << endl;
    cout << "______________________________" << endl;
    cout << "| What would you like to do? |" << endl;
    cout << "|----------------------------|" << endl;
    cout << "| [1] Checkout the Book      |" << endl;
    cout << "| [2] Return to Main Menu    |" << endl;
    cout << "|____________________________|" << endl;
    cout << "Selection: "; cin >> userSelection;
    while(userSelection != 1 && userSelection != 2) {
        cout << "Invalid Selection please reenter selection" << endl;
        cout << "Selection: "; cin >> userSelection;
    }
    if(userSelection == 1 && numAvailable == 0) {
        cout << "Sorry, this book has no available copies. Please return at a later date." << endl;
        cout << "               We will now return you to the main menu.                 " << endl;
        return 2;
    }
    return userSelection;
}

ostream& operator<<(ostream& out, Book& otherBook) {
    out << otherBook.getTitle()
        << " " << otherBook.getAuthor()
        << " " << otherBook.getGenre()
        << " " << otherBook.getLink()
        << " " << otherBook.getNumPages()
        << " " << otherBook.getNumAvailabe()
        << " " << otherBook.getNumCopies() << endl;
    return out;   
}