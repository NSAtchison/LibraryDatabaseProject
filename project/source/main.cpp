// Nathan Atchison
// May 20, 2022
// CS-172-1
// License: Copyright 2022 Nathan Atchison
#include <iostream>
#include <string>
#include <vector>
#include "..\headers\administrator.h"
#include "..\headers\book.h"
#include "..\headers\checkedbook.h"
#include "..\headers\database.h"
#include "..\headers\guest.h"
#include "..\headers\registereduser.h"
#include "..\headers\user.h"
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




int main() {
    Database libDatabase;
}

void runSystem(Database& libData) {
    bool hasExited = false;
    User currUser = loginToDatabase(libData);
    if(currUser.getStatus() == "N/A") {
        hasExited = true;
    }
    checkForCheckedOutBooks(libData, currUser);
    while(hasExited == false) {
        printMainMenu(currUser);
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