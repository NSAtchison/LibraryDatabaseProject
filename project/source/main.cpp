// Nathan Atchison
// May 20, 2022
// CS-172-1
// License: Copyright 2022 Nathan Atchison
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //Used for replace function src: https://www.cplusplus.com/reference/algorithm/replace/
#include "user.h"
#include "administrator.h"
#include "book.h"
#include "checkedbook.h"
#include "database.h"
#include "guest.h"
#include "registereduser.h"
using namespace std;

//This is the primary function of the system. Used to keep the system running until the user exits
//Input: N/A
//Output/Return: Any that is output to console through other functions.
void runSystem();

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

//Function that prints the Main Menu for the user
//Input: User name: The current user of the database. Mainly used to checked if they are an admin or not
//Output/Return: A menu is printed to console
void printMainMenu(User name);

//Function that checks if the user has any currently checked out books
//Input: Database libData: The library database, used to access the list of checked out books
//       User& name: The current user of the database. Passed by reference to add any books they have checked out
//                   to their personal list of checked out books
//Output/Return: Any checked out books are added to the current users vector containing all their checked out books
void checkForCheckedOutBooks(Database libData, User& name);

//Function that searches the database to see if a book exists in the database
//Input: Database libData: The library database, used to access list of library's books
//       string title: The book title of the book we are looking for
//Output/Return: If the book was found in the database, it returns that book
//               If the book was not found in the database, it returns a defaultly constructed Book object
Book searchForBook(Database libData, string title);

//Function that does the whole process of a book search
//Input: Database& libData: The library database, passed by reference just in case the user checks out the book they search for
//       User& currUser: The current user of the database, passed by reference just in case they check out a book
//Output/Return: Text is output to console going through the search for book process. Vectors in both the database
//               and for the user are updated if a book is checked out
void bookSearch(Database& libData, User& currUser);

//Function that does the whole process of a book return
//Input: Database& libData: The library database, passed by reference just in case the user checks out the book they search for
//       User& currUser: The current user of the database, passed by reference just in case they check out a book
//Output/Return: Text is output to console going through the search for book process. Vectors in both the database
//               and for the user are updated if a book is checked out
void bookReturn(Database& libData, User& currUser);

//Function that prints out text when a user logs out from the system
//Input: N/A
//Output: Some basic text thanking the user for using the system is printed to console
//        a boolean of value "true" is returned to indicate that the system has been exited
bool logoutScreen();




int main() {
    runSystem();
}

void runSystem() {
    Database libData;
    bool hasExited = false;
    int userSelection;
    User currUser = loginToDatabase(libData);
    if(currUser.getStatus() == "N/A") { //Checks if User chose to login or just immediately exit the system
        hasExited = true;
    }
    checkForCheckedOutBooks(libData, currUser);
    while(hasExited == false) { //Runs until the user decides to logout
        printMainMenu(currUser);
        cin >> userSelection;
        if(userSelection == 1) { //Search for Book
            bookSearch(libData, currUser);
        } else if (userSelection == 2) { //Search through Catalog

        } else if (userSelection == 3) { //Return a Book
            bookReturn(libData, currUser);
        } else if (userSelection == 4) { //View Profile
            currUser.viewProfile();
        } else if (userSelection == 5 && currUser.getStatus() == "Administrator") { //Add Book to Database (As Admin)
            Administrator tempAdmin(currUser.getID(), currUser.getPass());
            Book newBook = tempAdmin.addBook();
            libData.updateBookInfo(3, newBook, currUser);
        } else if (userSelection == 5 && currUser.getStatus() != "Administrator") { //Logout (if not an Admin)
            hasExited = logoutScreen();
        } else if (userSelection == 6 && currUser.getStatus() == "Administrator") { //Remove Book from Database (As Admin)
            Administrator tempAdmin(currUser.getID(), currUser.getPass());
            Book newBook = tempAdmin.removeBook(libData.getBooks());
            if(newBook.getTitle() != "None") {
                libData.updateBookInfo(4, newBook, currUser);
            }
        } else if (userSelection == 7 && currUser.getStatus() == "Administrator") { //Logout (if Admin)
            hasExited = logoutScreen();
        } else { //Invalid Input
            cout << "You have given an invalid input. Returning to Main Menu" << endl;
        }
    }
    //Write database information to files
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
    if(name.getStatus() == "Administrator") { //Prints a specific way if you are an admin
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
    for(int i = 0; i < books.size(); i++) { //Runs through all the books that are currently checked out
        if(books[i].getUserID() == name.getID()) { //If a userID attached to checked out books matches the user, adds it to their list of checked out books
            name.gatherBook(books[i]);
        }
    }
}

Book searchForBook(Database libData, string title) {
    vector<Book> bookList = libData.getBooks();
    for(int i = 0; i < bookList.size(); i++) { //Runs for every book in the library database
        string currBookTitle = bookList[i].getTitle(); //Grabs title of current book
        replace(currBookTitle.begin(), currBookTitle.end(), '_', ' '); //Replaces underlines in string with spaces
        transform(currBookTitle.begin(), currBookTitle.end(), currBookTitle.begin(), ::tolower); //Puts string into lowercase letters
        if(title == currBookTitle) { //Checks if the searched title matches the title of the current book
            return bookList[i];
        }
    }
    Book fin;
    return fin; //If book is not found in database, returns default constructed Book object
}

void bookSearch(Database& libData, User& currUser) {
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
            libData.updateBookInfo(1, currBook, currUser);
        }
    }
}

void bookReturn(Database& libData, User& currUser) {
    if(currUser.getStatus() == "Guest") { //Checks if the user is a guest
        cout << "As a Guest, you do not have access to checking out books." << endl;
        cout << "          Thus, you have not need to return any.         " << endl;
    } else {
        Book retBook = currUser.returnBook();
        if(retBook.getTitle() == "None") { //Checks if user decided either to not return a book or doesn't have any books to return
            cout << "You have decided not to return a book. Returning to Main Menu." << endl;
        } else { //They have a book they wanted to return
            libData.updateBookInfo(2, retBook, currUser);
        }
    }
}

bool logoutScreen() {
    cout << "____________________________________" << endl;
    cout << "|Thank you for coming to NSALibrary|" << endl;
    cout << "|    We hope you'll return soon!   |" << endl;
    cout << "|__________________________________|" << endl;
    return true;
}