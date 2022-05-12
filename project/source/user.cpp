#include "..\headers\user.h"
#include <iostream>
using namespace std;

User::User(string status) {
    userID = "N/A";
    password = "N/A";
    userStatus = status;
}

User::User(string id, string pass, string status) {
    userID = id;
    password = pass;
    status = userStatus;
}

// void User::checkOutBook() {
//     cout << "You do not have access to checking out a book, please register in order to do so" << endl;
// }

// void User::returnBook() {
//     cout << "You can not return a book, please register in order to do so" << endl;
// }

// void User::viewProfile() {
//     cout << "You do not have a profile to view, please register an account to view a profile";
// }