#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "..\headers\book.h"
#include "..\headers\administrator.h"
#include "..\headers\registereduser.h"
#include "..\headers\checkedbook.h"
#include <vector>
using namespace std;


class Database {
    private:
        vector<Book> books; //Vector of books currently in database
        vector<Administrator> adminList;
        vector<RegisteredUser> RegisteredUserList;
        vector<CheckedBook> checkedOutBooks;
    
    public:
        //Default Constructor
        Database();

        void printAdmins();
        void printUsers();
        void printBooks();
        void printCheckedOut();

    private:
        void findAdmins();
        void findRegisteredUsers();
        void findBooks();
        void findcheckedOutBooks();
};

#endif