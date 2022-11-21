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
        vector<Book> books;
        vector<Administrator> adminList;
        vector<RegisteredUser> RegisteredUserList;
        vector<CheckedBook> checkedOutBooks;
    
    public:
        //Default Constructor
        Database();

        //Function for printing all aspects of the databases
        void printAdmins();
        void printUsers();
        void printBooks();
        void printCheckedOut();

        //Getter Functions
        vector<Administrator> getAdmins();
        vector<RegisteredUser> getUsers();
        vector<Book> getBooks();
        vector<CheckedBook> getCheckedBooks();

        //Function that searches through all the admins for a specific admin
        //Input: string id: The userID of the desired admin
        //Output/Return: The desired admin is returned. If the admin was not found, a placeholder admin is created
        Administrator searchAdminList(string id);

        //Function that searches through all the registered users for a specific user
        //Input: string id: The userID of the desired user
        //Output/Return: The desired user is returned. If the user was not found, a placeholder user is created
        RegisteredUser searchUserList(string id);

        //Function that adds a new registered user to the database
        //Input: RegisteredUser name: The newly created user
        //Output/Return: The newly created user is added to the RegisteredUserList vector
        void addUser(RegisteredUser name);

        //Function that adds a new checked out book to the database
        //Input: CheckedBook name: The book that was just checked out
        //Output/Return: The book that was just checked out is added to the checkedOutBooks vector
        void addCheckedBook(CheckedBook name);

        //Function that updates the information of a book in the database
        //Input: int num: a integer value that indicates what action caused a need for a book to update (checkout, return, added, removed)
        //       Book name: The book that had something changed about it
        //       User id: The current user of the database who did something with the Book
        //Output/Return: The books information is updated based on the action that was taken
        void updateBookInfo(int num, Book name, User id);

    private:
        //Functions used by the system to create all of the vectors the database holds upon the database's creation
        void findAdmins();
        void findRegisteredUsers();
        void findBooks();
        void findcheckedOutBooks();
};

#endif