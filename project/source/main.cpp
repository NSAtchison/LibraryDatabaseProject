// Nathan Atchison
// May 20, 2022
// CS-172-1
// License: Copyright 2022 Nathan Atchison
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "user.h"
#include "administrator.h"
#include "book.h"
#include "checkedbook.h"
#include "database.h"
#include "guest.h"
#include "registereduser.h"
using namespace std;

void runSystem(Database& libData);


//This function will bring up a login screen in console that will give three options: Continue as Guest, Login or Register
//Input: Database& libData: The library database, brought in so that it can be updated and accessed as necessary
//Output/return: If the user continues as a guest, Guest object is created but nothing changed
//               If user logs in, either a Admin object is created or RegisteredUser object is created
//               If user registers, a new RegisteredUser object is created and then added to the database
User loginToDatabase(Database& libData);

//Function that prints the main login screen
//Input: N/A
//Output/Return: Main login screen printed to console
void loginScreenOne();

//Function that runs the entire login process
//Input: Database& libData: The library database, used for searching through users in the database as well as changing the database if necessary
//Output/Return: Several lines of text will print to console depending on input of user
//               A user will be returned depending on their choice (either a user with a status of RegisteredUser, Administrator, or Guest)
User loginScreenTwo(Database& libData);

//Function that verifies if a user has been registered in the system
//Input: Database& libData: the library database, used to check the user lists
//       string userID: The User ID that was input by the user that we are checking if it exists
//Output/Return: if the user was found in the database, the function will return true if not it will return false
bool verifyUserID(Database libData, string userID);

void printMainMenu(User name);

void checkForCheckedOutBooks(Database libData, User& name);

Book searchForBook(Database libData, string title);




int main() {
    Database libDatabase;
    runSystem(libDatabase);
}

void runSystem(Database& libData) {
    bool hasExited = false;
    int userSelection;
    User currUser = loginToDatabase(libData);
    if(currUser.getStatus() == "N/A") {
        hasExited = true;
    }
    checkForCheckedOutBooks(libData, currUser);
    while(hasExited == false) {
        printMainMenu(currUser);
        cin >> userSelection;
        if(userSelection == 1) { //Search for Book
            string bookTitle;
            cout << "________________________________" << endl;
            cout << "|        Book Search           |" << endl;
            cout << "|------------------------------|" << endl;
            cout << "|What is the title of the book?|" << endl; 
            cout << "| "; cin.ignore(); getline(cin, bookTitle); //Grab title of desired book
            transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower); //Make title lowercase for comparison
            Book currBook = searchForBook(libData, bookTitle); //Check for book in the library
            if(currBook.getAuthor() == "None") { //Check if book was not in the library
                cout << "Book does not exist in our library. We are sorry for the inconvenience" << endl;
                cout << "               We will now return you to the Main Menu.               " << endl;
            } else { //Book was in the library and found
                int userChoice = currBook.printInfo(); 
                if(userChoice == 1 && currUser.getStatus() == "Guest") { //User does not have access to checking out due to being a Guest
                    cout << "As a guest, you do not have access to checking out material." << endl;
                    cout << "Please reopen the system and create an account if you wish" << endl;
                    cout << "            Check out material in the library.            " << endl;
                } else if (userChoice == 1) { //Checking out the book
                    currUser.checkOutBook(currBook);
                    CheckedBook newBook(currUser.getID(), currBook);
                    libData.addCheckedBook(newBook);
                    //NOTE NOTE NOTE
                    //NOTE NOTE NOTE
                    //NOTE NOTE NOTE
                    //NOTE NOTE NOTE
                    //NOTE NOTE NOTE
                    //finish update book info function so that we can update that a book has 1 less available copy
                }
            }
        } else if (userSelection == 2) { //Search through Catalog

        } else if (userSelection == 3) { //Return a Book
            
        } else if (userSelection == 4) { //View Profile
            
        } else if (userSelection == 5 && currUser.getStatus() == "Administrator") { //Add Book to Database
            
        } else if (userSelection == 5 && currUser.getStatus() != "Administrator") { //Logout (if not an Admin)
            hasExited = true;
        } else if (userSelection == 6 && currUser.getStatus() == "Administrator") { //Remove Book from Database
            
        } else if (userSelection == 7 && currUser.getStatus() == "Administrator") { //Logout (if Admin)
            hasExited = true;
        } else { //Invalid Input

        }
    }
}



User loginToDatabase(Database& libData) {
    int userSelection; bool loginFin = false; User finUser;
    while(loginFin == false) { //Run until the login process is finished
        loginScreenOne();
        cin >> userSelection;
        while(userSelection < 1 or userSelection > 4) { //Must enter a valid selection before moving on
            cout << "Invalid selection please choose again" << endl;
            loginScreenOne();
            cin >> userSelection;
        }
        if(userSelection == 1) { //Continue as Guest
            Guest midUser;
            finUser = midUser;
            loginFin = true;
        } else if(userSelection == 2) { //Login to account
            User midUser = loginScreenTwo(libData);
            finUser = midUser;
            if(finUser.getStatus() != "N/A") { //If the user has a status of "N/A", they exited the login as user process
                loginFin = true;
            }
        } else if (userSelection == 3) { //Register Account
            Guest tempUser;
            RegisteredUser midUser = tempUser.registerAccount(); //Create the account as a guest
            libData.addUser(midUser); //Add new RegisteredUser to the database's list of users
            finUser = midUser;
            loginFin = true;
        } else { //Exit System, will return base user class
            loginFin = true;
        }
    }
    return finUser;
}

void loginScreenOne() {
    cout << "____________________________________" << endl;
    cout << "| Welcome to the NSALibrary Please |" << endl;
    cout << "| Select from the Following Options|" << endl;
    cout << "|----------------------------------|" << endl;
    cout << "| [1] Continue as Guest            |" << endl;
    cout << "| [2] Login to Account             |" << endl;
    cout << "| [3] Create an Account            |" << endl;
    cout << "| [4] Exit System                  |" << endl;
    cout << "|__________________________________|" << endl;
    cout << "Selection: ";
}


User loginScreenTwo(Database& libData) {
    string tempID, tempPass; int userSelection;
    bool foundUser;
    User finUser;

    cout << "__________________________________" << endl;
    cout << "|Are you logging in as an admin? |" << endl;
    cout << "|--------------------------------|" << endl;
    cout << "| [1] Yes                        |" << endl;
    cout << "| [2] No                         |" << endl;
    cout << "|________________________________|" << endl;
    cout << "Selection: "; cin >> userSelection; //Must tell if they are an admin or not

    cout << "Please enter your userID: "; cin >> tempID;
    foundUser = verifyUserID(libData, tempID);
    while(foundUser == false && tempID != "exit") { //Run until they decide to exit the login process or enter in a valid userID
        cout << "User not found. Please reenter userID or type \"exit\": "; cin >> tempID;
        foundUser = verifyUserID(libData, tempID);
    }

    if(tempID != "exit") { //Runs if the user entered a valid userID rather than exiting
        cout << "Please enter your password: "; cin >> tempPass;
        if(userSelection == 1) { //Admin
            Administrator midUser = libData.searchAdminList(tempID); //Finds the admin in the database
            while(midUser.getPass() != tempPass) { //Runs until the entered password and the password in the database match
                cout << "Incorrect Password. Please reenter password: "; cin >> tempPass;
            }
            finUser = midUser;
        } else { //Registered User
            RegisteredUser midUser = libData.searchUserList(tempID); //Finds Registered User in Database
            while(midUser.getPass() != tempPass) { //Runs until the entered password and the password in the database match
                cout << "Incorrect Password. Please reenter password: "; cin >> tempPass;
            }
            finUser = midUser;
        }
    }
    return finUser;
}

bool verifyUserID(Database libData, string userID) {
    vector<Administrator> tempAdmins = libData.getAdmins();
    vector<RegisteredUser> tempUsers = libData.getUsers();
    for(int i = 0; i < tempAdmins.size(); i++) { //Checks name with all admins
        if(tempAdmins[i].getID() == userID) {
            return true;
        }
    }
    for(int i = 0; i < tempUsers.size(); i++) { //Checks name with all registered users
        if(tempUsers[i].getID() == userID) {
            return true;
        }
    }
    return false; //userID is not in the database
}

void printMainMenu(User name) {
    cout << "____________________________________" << endl;
    cout << "| Welcome to the NSALibrary Please |" << endl;
    cout << "| Select from the Following Options|" << endl;
    cout << "|----------------------------------|" << endl;
    cout << "| [1] Search for Book              |" << endl;
    cout << "| [2] Search through Catalog       |" << endl;
    cout << "| [3] Return a Book                |" << endl;
    cout << "| [4] View Profile                 |" << endl;
    if(name.getStatus() == "Administrator") {
    cout << "| [5] Add Book to Database         |" << endl;
    cout << "| [6] Remove Book from Database    |" << endl;
    cout << "| [7] Logout from System           |" << endl;
    } else {
    cout << "| [5] Logout from System           |" << endl;
    }
    cout << "|__________________________________|" << endl;
    cout << "Selection: ";
}

void checkForCheckedOutBooks(Database libData, User& name) {
    vector<CheckedBook> books = libData.getCheckedBooks();
    for(int i = 0; i < books.size(); i++) {
        if(books[i].getUserID() == name.getID()) {
            name.gatherBook(books[i]);
        }
    }
}

Book searchForBook(Database libData, string title) {
    vector<Book> bookList = libData.getBooks();
    for(int i = 0; i < bookList.size(); i++) {
        string currBookTitle = bookList[i].getTitle();
        replace(currBookTitle.begin(), currBookTitle.end(), '_', ' ');
        transform(currBookTitle.begin(), currBookTitle.end(), currBookTitle.begin(), ::tolower);
        if(title == currBookTitle) {
            return bookList[i];
        }
    }
    Book fin;
    return fin;
}