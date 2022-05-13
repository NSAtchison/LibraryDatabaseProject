#include <iostream>
#include <vector>
#include "book.h"
#include "user.h"
#include "registereduser.h"
using namespace std;

//Constructor
RegisteredUser::RegisteredUser(string id, string pass) : User(id, pass, "Registered User") {}

// //Allows registered user to view their profile
// //Input: N/A
// //Output/Return: Information about the registered user's profile will be output to console
// void RegisteredUser::viewProfile();