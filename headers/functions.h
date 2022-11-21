#ifndef FUNCTIONS_H
#define FUNCTIONS_H
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

//Function that allows the user to view the entire libraries catalog
//Input: Database& libData: The library database, passed by reference just in case the user checks out the book they search for
//       User& currUser: The current user of the database, passed by reference just in case they check out a book
//Output/Return: Text is output to console going through the catalog process. Vectors in both the database
//               and for the user are updated if a book is checked out
void viewCatalog(Database& libData, User& currUser);

//Function that updates the database with all newly input information once the system is close
//Input: Database libData: The library database. Used to access the vectors whose data is being output
//Output/Return: Four output files are written to hold all the information that the database holds
void updateLists(Database libData);



#endif