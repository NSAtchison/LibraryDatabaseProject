#include <iostream>
#include "book.h"
#include "administrator.h"
#include "registereduser.h"
#include "checkedbook.h"
#include "database.h"
#include "administrator.h"
#include <vector>
#include <fstream>
using namespace std;

Database::Database() {
    findAdmins();
    findRegisteredUsers();
    findBooks();
    findcheckedOutBooks();
}

void Database::findAdmins() {
    fstream inputFile("admin_list.txt", ios::in);
    string str, adminID, adminPass;
    while(inputFile >> str) {
        adminID = str;
        inputFile >> str;
        adminPass = str;
        Administrator tempAdmin(adminID, adminPass);
        adminList.push_back(tempAdmin);
    }
    inputFile.close();
}

void Database::findRegisteredUsers() {
    fstream inputFile("registered_user_list.txt", ios::in);
    string str, userID, userPass;
    while(inputFile >> str) {
        userID = str;
        inputFile >> str;
        userPass = str;
        RegisteredUser tempRegUser(userID, userPass);
        RegisteredUserList.push_back(tempRegUser);
    }
    inputFile.close();
}

void Database::findBooks() {
    fstream inputFile("book_list.txt", ios::in);
    string str, title, author, genre, link;
    int pages, available, copies;
    while(inputFile >> str) {
        title = str;
        inputFile >> str;
        author = str;
        inputFile >> str;
        genre = str;
        inputFile >> str;
        link = str;
        inputFile >> str;
        pages = stoi(str);
        inputFile >> str;
        available = stoi(str);
        inputFile >> str;
        copies = stoi(str);
        Book tempBook(title, author, genre, link, pages, available, copies);
        books.push_back(tempBook);
    }
    inputFile.close();
}

void Database::findcheckedOutBooks() {
    fstream inputFile("checked_out_list.txt", ios::in);
    string str, user, title, author, genre, link;
    int pages, available, copies;
    while(inputFile >> str) {
        user = str;
        inputFile >> str;
        title = str;
        inputFile >> str;
        author = str;
        inputFile >> str;
        genre = str;
        inputFile >> str;
        link = str;
        inputFile >> str;
        pages = stoi(str);
        inputFile >> str;
        available = stoi(str);
        inputFile >> str;
        copies = stoi(str);
        Book tempBook(title, author, genre, link, pages, available, copies);
        CheckedBook finBook(user, tempBook);
        checkedOutBooks.push_back(finBook);
    }
    inputFile.close();
}

void Database::printAdmins() {
    for(int i = 0; i < adminList.size(); i++) {
        cout << adminList[i];
    }
    cout << endl;
}

void Database::printUsers() {
    for(int i = 0; i < RegisteredUserList.size(); i++) {
        cout << RegisteredUserList[i];
    }
    cout << endl;
}

void Database::printBooks() {
    for(int i = 0; i < books.size(); i++) {
        cout << books[i];
    }
    cout << endl;
}

void Database::printCheckedOut() {
    for(int i = 0; i < checkedOutBooks.size(); i++) {
        cout << checkedOutBooks[i];
    }
    cout << endl;
}

vector<Administrator> Database::getAdmins() { return adminList; }
vector<RegisteredUser> Database::getUsers() { return RegisteredUserList; }
vector<Book> Database::getBooks() { return books; }
vector<CheckedBook> Database::getCheckedBooks() { return checkedOutBooks; }

Administrator Database::searchAdminList(string id) {
    for(int i = 0; i < adminList.size(); i++) {
        if(adminList[i].getID() == id) {
            return adminList[i];
        }
    }
    Administrator holdVar("fill", "fill");
    return holdVar;
}

RegisteredUser Database::searchUserList(string id) {
    for(int i = 0; i < adminList.size(); i++) {
        if(RegisteredUserList[i].getID() == id) {
            return RegisteredUserList[i];
        }
    }
    RegisteredUser holdVar("fill", "fill");
    return holdVar;
}

void Database::addUser(RegisteredUser name) {
    RegisteredUserList.push_back(name);
}

void Database::addCheckedBook(CheckedBook name) {
    checkedOutBooks.push_back(name);
}

void Database::updateBookInfo(int num, Book name, User id) {
    if(num == 1) { //Book was checked out
        string bookName = name.getTitle();
        for(int i = 0; i < books.size(); i++) { //Runs through every book in library (Or until identical is found)
            if(books[i].getTitle() == bookName) { //Check if book input is the same as current book we are looking at in the library
                books[i].updateNumAvailable(1);
                break;
            }
        }
    } else if (num == 2) { //Book was Returned
        string bookName = name.getTitle();
        string userName = id.getID();
        for(int i = 0; i < books.size(); i++) { //Runs through every book in library (Or until identical is found)
            if(books[i].getTitle() == bookName) { //Check if book input is the same as current book we are looking at in the library
                books[i].updateNumAvailable(2);
                break;
            }
        }
        for(int i = 0; i < checkedOutBooks.size(); i++) {
            if((checkedOutBooks[i].getUserID() == userName) && (checkedOutBooks[i].getTitle() == bookName)) {
                checkedOutBooks.erase(checkedOutBooks.begin() + i);
                break;
            }
        }
    } else if (num == 3) { //Book was added to library
        string bookName = name.getTitle();
        bool isIdentical = false;
        for(int i = 0; i < books.size(); i++) { //Runs through every book in library (Or until identical is found)
            if(books[i].getTitle() == bookName) { //Check if book input is the same as current book we are looking at in the library
                books[i].updateNumCopies(1);
                isIdentical = true;
                break;
            }
        }
        if(isIdentical == false) { //Check if this is a brand new book to the library
            name.updateNumCopies(1);
            books.push_back(name);
        }
    } else if (num == 4) { //Book was removed from library
        string bookName = name.getTitle();
        for(int i = 0; i < books.size(); i++) { //Runs through every book in library until identical is found
            if(books[i].getTitle() == bookName) { //Check if current book is identical of the input book
                books[i].updateNumCopies(2);
                if(books[i].getNumCopies() < 1) {
                    books.erase(books.begin() + i);
                }
                break;
            }
        }
    }
}
