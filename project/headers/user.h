#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;



class User {
    protected:
        string userID;
        string password;
        string userStatus;

    public:
        //Default Constructor
        User();

        //Variable Constructor 1
        User(string status);

        //Variable Constructor
        User(string id, string pass, string status);

        // //Allows user to checkout a book from the database
        // //Input: N/A
        // //Output/Return: Book object is updated to indicate book is checked out, book added to subclass checkout vector
        // virtual void checkOutBook();
        
        // //Allows user to return a checked out book to the database
        // //Input: N/A
        // //Output/Return: Book object is updated to indicate book is returned, book removed from subclass checkout vector
        // virtual void returnBook();

        // //Allows user to view their profile
        // //Input: N/A
        // //Output/Return: Information about the user's profile will be output to console
        // virtual void viewProfile();

        string getID();
        string getPass();
        string getStatus();
        friend ostream& operator<<(ostream& out, User& otherUser);
};

#endif