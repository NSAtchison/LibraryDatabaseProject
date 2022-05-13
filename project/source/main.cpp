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

//This function will bring up a login screen in console that will give three options: Continue as Guest, Login or Register
//Input: Database& libData: The library database, brought in so that it can be updated and accessed as necessary
//Output/return: If the user continues as a guest, Guest object is created but nothing changed
//               If user logs in, either a Admin object is created or RegisteredUser object is created
//               If user registers, a new RegisteredUser object is created and then added to the database

User loginToDatabase(Database& libData);

void loginScreenOne();
User loginScreenTwo(Database& libData);

bool verifyUserID(Database& libData, string userID);



int main() {
    Database libDatabase;
    User test = loginToDatabase(libDatabase);
    cout << test;
}


User loginToDatabase(Database& libData) {
    int userSelection;
    loginScreenOne();
    cin >> userSelection;
    User finUser;
    while(userSelection < 1 or userSelection > 3) {
        cout << "Invalid selection please choose again" << endl;
        loginScreenOne();
        cin >> userSelection;
    }
    if(userSelection == 1) { //Continue as Guest
        Guest midUser;
        finUser = midUser;
    } else if(userSelection == 2) { //Login to account
        User midUser = loginScreenTwo(libData);
        finUser = midUser;
    } else { //Register Account
        Guest tempUser;
        RegisteredUser midUser = tempUser.registerAccount();
        finUser = midUser;
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
    cout << "Selection: "; cin >> userSelection;

    cout << "Please enter your userID: "; cin >> tempID;
    foundUser = verifyUserID(libData, tempID);
    while(foundUser == false && tempID != "exit") {
        cout << "User not found. Please reenter userID or type \"exit\": "; cin >> tempID;
        foundUser = verifyUserID(libData, tempID);
    }

    if(tempID != "exit") {
        cout << "Please enter your password: "; cin >> tempPass;
        if(userSelection == 1) {
            Administrator midUser = libData.searchAdminList(tempID);
            while(midUser.getPass() != tempPass) {
                cout << "Incorrect Password. Please reenter password: "; cin >> tempPass;
            }
            finUser = midUser;
        } else {
            RegisteredUser midUser = libData.searchUserList(tempID);
            while(midUser.getPass() != tempPass) {
                cout << "Incorrect Password. Please reenter password: "; cin >> tempPass;
            }
            finUser = midUser;
        }
    }
    return finUser;
}

bool verifyUserID(Database& libData, string userID) {
    vector<Administrator> tempAdmins = libData.getAdmins();
    vector<RegisteredUser> tempUsers = libData.getUsers();
    for(int i = 0; i < tempAdmins.size(); i++) {
        if(tempAdmins[i].getID() == userID) {
            return true;
        }
    }
    for(int i = 0; i < tempUsers.size(); i++) {
        if(tempUsers[i].getID() == userID) {
            return true;
        }
    }
    return false;
}



