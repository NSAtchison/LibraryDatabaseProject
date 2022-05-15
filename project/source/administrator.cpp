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
    cout << " Title of the Book: "; cin.ignore(); getline(cin, bookTitle);
    cout << " Author of the Book: "; getline(cin, bookAuthor);
    cout << " Genre of the Book: "; getline(cin, bookGenre);
    cout << " Link to Book's GoodReads Page: "; getline(cin, grLink);
    cout << " Number of Pages in Book: "; cin >> pages;
    replace(bookTitle.begin(), bookTitle.end(), ' ', '_');
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
    cout << " Title of the Book: "; cin.ignore(); getline(cin, bookTitle);
    cout << " Author of the Book: "; getline(cin, bookAuthor);
    cout << " Are you sure that you want to remove" << endl;
    cout << " " << bookTitle << endl;
    cout << " By " << bookAuthor << "?" << endl;
    cout << " [1] Yes " << endl;
    cout << " [2] No " << endl;
    cout << "Response: "; cin >> userResponse;
    replace(bookTitle.begin(), bookTitle.end(), ' ', '_');
    replace(bookAuthor.begin(), bookAuthor.end(), ' ', '_');
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
    return finBook;
}

