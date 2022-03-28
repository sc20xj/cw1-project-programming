
#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H


#include <stdio.h>

/*You can extend the structs (Book and BookList) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/
typedef struct _user User;

typedef struct _Book {
	    unsigned int id; //Book ID
		char *title; //book title
		char *authors; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
		struct _Book *next; //pointer to the next book element
		User *history;
		int borrowed;
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
	 
}User;
typedef struct _Userlist {
	 User* list; // pointer to a list of struct Book.
	 unsigned int length; // number of elements in the (Book*) List 
}Userlist;


#endif

