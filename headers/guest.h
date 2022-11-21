#ifndef GUEST_H
#define GUEST_H
#include "user.h"
#include <iostream>
using namespace std;



class Guest : public User {
    public:
        //Constructor
        Guest();
        
        //Method that allows a guest user to create a registered account
        //Input: N/A
        //Output: A registered user is created and added to list of registered users in database
        RegisteredUser registerAccount();
};

#endif