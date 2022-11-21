#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H
#include <iostream>
#include <vector>
#include "book.h"
#include "user.h"
using namespace std;



class RegisteredUser : public User {
    public:
        //Constructor
        RegisteredUser(string id, string pass);

        //Allows registered user to view their profile
        //Input: N/A
        //Output/Return: Information about the registered user's profile will be output to console
        void viewProfile();        
};

#endif