#include "user.h"
#include "book.h"
#include "checkedbook.h"
#include <iostream>
#include <vector>
using namespace std;

User::User() {
    userID = "N/A";
    password = "N/A";
    userStatus = "N/A";
}

User::User(string status) {
    userID = "N/A";
    password = "N/A";
    userStatus = status;
}

User::User(string id, string pass, string status) {
    userID = id;
    password = pass;
    userStatus = status;
}

void User::gatherBook(CheckedBook tempBook) {
    checkedOut.push_back(tempBook);
}

void User::checkOutBook(Book currBook) {
    CheckedBook newBook(userID, currBook);
    checkedOut.push_back(newBook);
}

// void User::returnBook() {
//     cout << "You can not return a book, please register in order to do so" << endl;
// }

// void User::viewProfile() {
//     cout << "You do not have a profile to view, please register an account to view a profile";
// }

string User::getID() { return userID; }
string User::getPass() { return password; }
string User::getStatus() { return userStatus; }

ostream& operator<<(ostream& out, User& otherAdmin) {
    out << otherAdmin.getID() << " " << otherAdmin.getPass() << " " << otherAdmin.getStatus() << endl;
    return out;
}