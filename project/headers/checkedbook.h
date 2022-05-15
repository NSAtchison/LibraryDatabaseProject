#ifndef CHECKEDBOOK_H
#define CHECKEDBOOK_H
#include "book.h"
#include <iostream>
using namespace std;



class CheckedBook : public Book {
    private:
        string userID;
    
    public:
        //Constructor
        CheckedBook(string name, Book bk);

        //Getter Function
        string getUserID();

        //Operator Overload
        friend ostream& operator<<(ostream& out, CheckedBook& otherBook);
};

#endif