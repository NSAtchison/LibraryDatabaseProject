#include "user.h"
#include "registereduser.h"
#include "guest.h"
#include <iostream>
using namespace std;


//Constructor
Guest::Guest() : User("Guest") {}

//Method that allows a guest user to create a registered account
//Input: N/A
//Output: A registered user is created and added to list of registered users in database
RegisteredUser Guest::registerAccount() {
    string tempID, tempPass, confPass;
    cout << "_______________________________________________" << endl;
    cout << "| Thank you for deciding to Register with us! |" << endl;
    cout << "|   Please follow the following instruction.  |" << endl;
    cout << "|---------------------------------------------|" << endl;
    cout << " What would you like as your UserID: "; cin >> tempID;
    cout << " What would you like as your password: "; cin >> tempPass;
    cout << " Please confirm your password: "; cin >> confPass;
    while(tempPass != confPass) { //Runs until the user successfully confirms their password
        cout << " Incorrect password please try again: "; cin >> confPass;
    }
    cout << " UserID and Password have been confirmed." << endl;
    cout << "    We will now register your account!   " << endl;
    RegisteredUser finUser(tempID, tempPass); //Creates a user with the user inputted information
    return finUser;
}
