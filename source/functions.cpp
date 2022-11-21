#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //Used for replace function src: https://www.cplusplus.com/reference/algorithm/replace/
#include <fstream>
#include "user.h"
#include "administrator.h"
#include "book.h"
#include "checkedbook.h"
#include "database.h"
#include "guest.h"
#include "registereduser.h"
#include "functions.h"
using namespace std;

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
            viewCatalog(libData, currUser);
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
    updateLists(libData);
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
    while(userSelection != 1 && userSelection != 2) {
        cout << "Invalid input. Please reinput selection." << endl;
        cout << "Selection: "; cin >> userSelection;
    }
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

void viewCatalog(Database& libData, User& currUser) {
    vector<Book> books = libData.getBooks();
    int numPages = ((books.size()) / 10) + 1; //Maximum number of pages in the catalog
    int currPage = 1, minIndex = 0, booksPerPage, userSelection;
    bool hasExited = false;
    while(hasExited == false) { //Runs until the user returns to the main menu
        books = libData.getBooks(); //Grabs an updated list of the books in the library at the beginning of each run
        cout << "____________________________" << endl;
        cout << "|  NSA2000 Library Catalog |" << endl;
        cout << "|--------------------------|" << endl;
        if(currPage < numPages) { //Checks if this is the last page
            booksPerPage = 10;
        } else { //This is the last page
            booksPerPage = (books.size() % 10);
        }
        for(int i = 0; i < booksPerPage; i++) { //Prints all the books on the current page
            string currBook = books[minIndex + i].getTitle();
            replace(currBook.begin(), currBook.end(), '_', ' ');
            cout << "| [" << (i+1) << "] " << currBook << endl;
        }
        //Next 3 lines print the options that don't include books
        cout << "| [" << (booksPerPage+1) << "] Next Page" << endl;
        cout << "| [" << (booksPerPage+2) << "] Previous Page" << endl;
        cout << "| [" << (booksPerPage+3) << "] Return to Main Menu" << endl;
        cout << "| Please select one of the options above" << endl;
        cout << "| Selection: "; cin >> userSelection; //Ask for user input
        if(userSelection > 0 && userSelection <= booksPerPage) { //User Selected one of the 10 books listed
            Book currBook = books[minIndex + (userSelection - 1)];
            int choice = currBook.printInfo();
            if(choice == 1 && currUser.getStatus() == "Guest") { //User does not have access to checking out due to being a Guest
                cout << "As a guest, you do not have access to checking out material." << endl;
                cout << "Please reopen the system and create an account if you wish" << endl;
                cout << "            Check out material in the library.            " << endl;
            } else if (choice == 1) { //Checking out the book
                currUser.checkOutBook(currBook);
                CheckedBook newBook(currUser.getID(), currBook);
                libData.addCheckedBook(newBook);
                libData.updateBookInfo(1, currBook, currUser);
            }
        } else if(userSelection == booksPerPage + 1) { //User Decided to go to next page
            if(currPage == numPages) { //Check if user is on last page
                cout << "This is the last page. As such you can not go to the next page" << endl;
            } else { 
                minIndex += 10; //Finds first book of next page
                currPage++;
            }
        } else if(userSelection == booksPerPage + 2) {  //User decided to go to previous page
            if(currPage == 1) { //Check if user is on first page
                cout << "This is the first page. As such you can not go to the previous page" << endl;
            } else {
                minIndex -= 10; //Finds first book of previous page
                currPage--;
            }
        } else if(userSelection == booksPerPage + 3) { //User decided to return to main menu
            cout << "Returning to Main Menu" << endl;
            hasExited = true;
        } else { //Invalid input
            cout << "You have given an invalid input" << endl;
        }
    }
}

void updateLists(Database libData) {
    fstream bookOutput("book_list.txt", ios::out);
    fstream userOutput("registered_user_list.txt", ios::out);
    fstream adminOutput("admin_list.txt", ios::out);
    fstream checkedBookOutput("checked_out_list.txt", ios::out);
    vector<Book> finBooks = libData.getBooks();
    vector<RegisteredUser> finUsers = libData.getUsers();
    vector<Administrator> finAdmins = libData.getAdmins();
    vector<CheckedBook> finCheckedBooks = libData.getCheckedBooks();
    for(int i = 0; i < finBooks.size(); i++) {
        Book currBook = finBooks[i];
        bookOutput << currBook.getTitle() << " " 
                   << currBook.getAuthor() << " " 
                   << currBook.getGenre() << " "
                   << currBook.getLink() << " "
                   << currBook.getNumPages() << " "
                   << currBook.getNumAvailabe() << " "
                   << currBook.getNumCopies() << endl;
    }

    for(int i = 0; i < finUsers.size(); i++) {
        RegisteredUser currUser = finUsers[i];
        userOutput << currUser.getID() << " " << currUser.getPass() << endl;
    }

    for(int i = 0; i < finAdmins.size(); i++) {
        Administrator currAdmin = finAdmins[i];
        adminOutput << currAdmin.getID() << " " << currAdmin.getPass() << endl;
    }

    for(int i = 0; i < finCheckedBooks.size(); i++) {
        CheckedBook currBook = finCheckedBooks[i];
        checkedBookOutput << currBook.getUserID() << " "
                   << currBook.getTitle() << " " 
                   << currBook.getAuthor() << " " 
                   << currBook.getGenre() << " "
                   << currBook.getLink() << " "
                   << currBook.getNumPages() << " "
                   << currBook.getNumAvailabe() << " "
                   << currBook.getNumCopies() << endl;
    }

}