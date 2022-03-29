
#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H


#include <stdio.h>
#include"show.h"
/*You can extend the structs (Book and BookList) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/
typedef struct _user User;

typedef struct _Book {
	    unsigned int id; //Book ID
		int titlesize;
		char *title; //book title
		int authorsize;
		char *authors; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
		struct _Book *next; //pointer to the next book element
		User *history;
		int borrowed;
		int borrowing;
}Book;

typedef struct _BookList {
	 Book* list; // pointer to a list of struct Book.
	 unsigned int length; // number of elements in the (Book*) List 
}BookList;

typedef struct _user{
     char* name;
	 char* password;
	 char* email;
	 char* gender;
	 struct _user *next;
	 Book* bookborrow;
	 int number;
	 int namesize;
	 int passwordsize;
	 
}User;
typedef struct _Userlist {
	 User* list; // pointer to a list of struct Book.
	 unsigned int length; // number of elements in the (Book*) List 
}Userlist;


BookList find_book_by_title (const char *title);

BookList find_book_by_author (const char *author);

BookList find_book_by_year (unsigned int year);

void searchbooks();





int return_book(User* logeduser);





int Borrowbooks(User* logeduser);


int add_book(Book book);

int remove_book(Book book);

#endif

