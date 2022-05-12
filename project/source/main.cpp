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
template <typename Type>
Type loginToDatabase(Database& libData);

void loginScreenOne();
void loginScreenTwo();




int main() {
    Database libDatabase;
}

template <typename Type>
Type loginToDatabase(Database& libData) {
    int userSelection;
    loginScreenOne();
    cin >> userSelection;
    while(userSelection < 1 or userSelection > 3) {
        cout << "Invalid selection please choose again" << endl
        loginScreenOne();
        cin >> userSelection;
    }
    if(userSelection == 1 || userSelection == 3) { //Continue as Guest or Register Account
        Guest finUser;
        return finUser;
    } else if(userSelection == 2) { //Login to account
        
    } else { //Register Account
        Guest tempUser;
        RegisteredUser finUser;
        finUser = tempUser.registerAccount();
        return finUser;
    }

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

template <typename Type>
Type loginScreenTwo() {
    string tempID, tempPass;
    cout << "Please enter your userID: "; cin >> tempID;

}



