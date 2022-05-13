#include <iostream>
#include <vector>
#include "..\headers\book.h"
#include "..\headers\user.h"
#include "..\headers\registereduser.h"
using namespace std;

//Constructor
RegisteredUser::RegisteredUser(string id, string pass) : User(id, pass, "Registered User") {}

// //Allows registered user to checkout a book from the database
// //Input: N/A
// //Output/Return: Book object is updated to indicate book is checked out, book added to registered user's checkedOut vector
// void RegisteredUser::checkOutBook() {
    
// }

// //Allows registered user to return a checked out book to the database
// //Input: N/A
// //Output/Return: Book object is updated to indicate book is returned, book removed from registered user's checkedOut vector
// void RegisteredUser::returnBook();

// //Allows registered user to view their profile
// //Input: N/A
// //Output/Return: Information about the registered user's profile will be output to console
// void RegisteredUser::viewProfile();