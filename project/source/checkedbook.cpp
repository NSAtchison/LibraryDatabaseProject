#include "..\headers\book.h"
#include "..\headers\checkedbook.h"
#include <iostream>
using namespace std;


//Constructor
CheckedBook::CheckedBook(string name, Book bk) : Book(bk) {
    userID = name;
}

ostream& operator<<(ostream& out, CheckedBook& otherBook) {
    out << otherBook.userID << " " << otherBook.getTitle()
                            << " " << otherBook.getAuthor()
                            << " " << otherBook.getGenre()
                            << " " << otherBook.getLink()
                            << " " << otherBook.getNumPages()
                            << " " << otherBook.getNumAvailabe()
                            << " " << otherBook.getNumCopies() << endl;                          
    return out;
}


