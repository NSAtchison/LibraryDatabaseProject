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


// Book Administrator::removeBook() {
    
// }

