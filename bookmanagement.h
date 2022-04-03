
#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H


#include <stdio.h>
#include"show.h"
#include"lo_st.h"
#include"structure.h"


//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title);





//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author);



//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year);



//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int return_book(User* logeduser);



//For users to borrow books from the library
//return 1 if the book is borrowed successfully, or the error codes otherwise.
int Borrowbooks(User* logeduser);



//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book);



//For users to return books to the library
//return 1 if the book is returned successfully, or the error codes otherwise.
int remove_book(Book book);

#endif

