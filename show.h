#ifndef BOOK_MANAGEMENT_GUARD_librarian
#define BOOK_MANAGEMENT_GUARD__librarian


#include <stdio.h>

#include"bookmanagement.h"
#include"lo_st.h"
#include"myutility.h"


//To show the history of the books that be borrowed by different users.
void showhistory();

//To show the books that currently available to be borrowed, return 1 if there are available books
// or the error code otherwise.
int listavailablebook();

//To display all the books in the library system.
void display();


//To show the book that is borrowing for the speific user
//return 1 if there are borrowed books of the user
// or the error code otherwise.
int showborrowed(User* logeduser);


//To show the books that currently be borrowed.
void showborrowing();



#endif
