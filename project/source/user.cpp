#include "user.h"
#include "book.h"
#include "checkedbook.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //Used for replace function src: https://www.cplusplus.com/reference/algorithm/replace/
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



Book User::returnBook() {
    int userSelection;
    if(checkedOut.empty() == true) { //See if they currently have any checked out books
        cout << "You do not currently have any checked out books to return." << endl;
    } else { //They have checked out books
        cout << "________________________________" << endl;
        cout << "| Which of the following books |" << endl;
        cout << "|   Would you like to return   |" << endl;
        cout << "|------------------------------|" << endl;
        for(int i = 0; i < checkedOut.size(); i++) { //Prints all the titles of the books they have checked out
            string currBookTitle = checkedOut[i].getTitle();
            replace(currBookTitle.begin(), currBookTitle.end(), '_', ' ');
            cout << "[" << (i+1) << "] " << currBookTitle << endl;
        }
        cout << "[" << (checkedOut.size() + 1) << "] Return to Main Menu" << endl;
        cout << "Selection: "; cin >> userSelection;
        while((userSelection < 1) || (userSelection > (checkedOut.size() + 1))) { //Checks if they gave a valid input
            cout << "Invalid Selection. Please enter again: "; cin >> userSelection;
        }
        if(userSelection != (checkedOut.size() + 1)) { //Check if the decided to return a book
            Book retBook(checkedOut[userSelection - 1].getTitle(), checkedOut[userSelection - 1].getAuthor(), checkedOut[userSelection - 1].getGenre(), checkedOut[userSelection - 1].getLink(), checkedOut[userSelection - 1].getNumPages());
            checkedOut.erase(checkedOut.begin() + (userSelection - 1));
            return retBook;
        }
    }
    Book retBook;
    return retBook;
}

void User::viewProfile() {
    if(userStatus == "Guest") {
        cout << "You do not have a profile to view, please register an account to view a profile" << endl;
    } else {
        string userInput;
        cout << "________________" << endl;
        cout << "| User Profile |" << endl;
        cout << "|--------------|" << endl;
        cout << " Username: " << userID << endl;
        cout << " Password: " << password << endl;
        cout << " Profile Type: " << userStatus << endl;
        cout << " Currently Checked Out Books" << endl;
        cout << " ---------------------------" << endl;
        for(int i = 0; i < checkedOut.size(); i++) {
            string currTitle = checkedOut[i].getTitle();
            replace(currTitle.begin(), currTitle.end(), '_', ' ');
            cout << "[" << (i+1) << "] " << currTitle << endl;
        }
        cout << endl << "Please Enter \"1\" to return to the Main Menu "; cin >> userInput;
    }
}

string User::getID() { return userID; }
string User::getPass() { return password; }
string User::getStatus() { return userStatus; }

ostream& operator<<(ostream& out, User& otherAdmin) {
    out << otherAdmin.getID() << " " << otherAdmin.getPass() << " " << otherAdmin.getStatus() << endl;
    return out;
}