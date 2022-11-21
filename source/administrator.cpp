#include <iostream>
#include <vector>
#include <algorithm>
#include "book.h"
#include "user.h"
#include "administrator.h"
using namespace std;


//Constructor
Administrator::Administrator(string name, string pass) : User(name, pass, "Administrator") {}




Book Administrator::addBook() {
    string bookTitle, bookAuthor, bookGenre, grLink;
    int pages;
    cout << "__________________________________________" << endl;
    cout << "| Please Input the Following Information |" << endl;
    cout << "|________________________________________|" << endl;
    cout << " Title of the Book: "; cin.ignore(); getline(cin, bookTitle); //Input title of new book
    cout << " Author of the Book: "; getline(cin, bookAuthor); //Input author of new book
    cout << " Genre of the Book: "; getline(cin, bookGenre); //Input genre of new book (main genre)
    cout << " Link to Book's GoodReads Page: "; getline(cin, grLink); //Input Good Reads page link for new book
    cout << " Number of Pages in Book: "; cin >> pages; //Input number of pages in the book
    replace(bookTitle.begin(), bookTitle.end(), ' ', '_'); //Next 3 lines replace all spaces with underscores (used for File I/O Storage)
    replace(bookAuthor.begin(), bookAuthor.end(), ' ', '_');
    replace(bookGenre.begin(), bookGenre.end(), ' ', '_');
    Book newBook(bookTitle, bookAuthor, bookGenre, grLink, pages);
    return newBook;
}


Book Administrator::removeBook(vector<Book> books) {
    string bookTitle, bookAuthor;
    int pages, userResponse;
    cout << "__________________________________________" << endl;
    cout << "| Please Input the Following Information |" << endl;
    cout << "|________________________________________|" << endl;
    cout << " Title of the Book: "; cin.ignore(); getline(cin, bookTitle); //Input title of book to be removed
    cout << " Author of the Book: "; getline(cin, bookAuthor); //Input author of book to be removed
    cout << " Are you sure that you want to remove" << endl;
    cout << " " << bookTitle << endl;
    cout << " By " << bookAuthor << "?" << endl;
    cout << " [1] Yes " << endl;
    cout << " [2] No " << endl;
    cout << "Response: "; cin >> userResponse; //Asking for confirmation on if they want to remove the book
    replace(bookTitle.begin(), bookTitle.end(), ' ', '_');
    replace(bookAuthor.begin(), bookAuthor.end(), ' ', '_');
    while(userResponse != 1 && userResponse != 2) { //Checks for Invalid input, and continually asks until valid input is given
        cout << "Invalid Selection please reenter selection" << endl;
        cout << "Selection: "; cin >> userResponse;
    }
    if(userResponse == 1) { //They confirm to remove the book
        for(int i = 0; i < books.size(); i++) {
            if(books[i].getTitle() == bookTitle && books[i].getAuthor() == bookAuthor) {
                return books[i];
            }
        }
        cout << "The book you are trying to remove does not exist in our library." << endl;
        cout << "                      Returning to Main Menu                    " << endl;
    }
    Book finBook;
    return finBook; //If you reach this point, the book either doesn't exist in the database or they decided not to remove the book
}

