
#ifndef BOOK_MANAGEMENT_GUARD__2
#define BOOK_MANAGEMENT_GUARD__2


typedef struct _user User;//pre-define of User

typedef struct _Book {
	    unsigned int id; //Book ID
		int titlesize;//the size of title
		char *title; //book title
		int authorsize;//the size of author
		char *authors; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
		struct _Book *next; //pointer to the next book element
		User *history;//pointer to the userlist of this books borrowed history
		int borrowed;//the number that the book have been borrowed from the beginning
		int borrowing;//the state if someone is borrowing this book
		
}Book;

typedef struct _BookList {
	 Book* list; // pointer to a list of struct Book.
	 unsigned int length; // number of elements in the (Book*) List 
}BookList;

typedef struct _user{
     char* name;//user name
	 char* password;//user password
	 struct _user *next;//pointer to the next user element
	 Book* bookborrow;//pointer the booklist that the user is borrowing
	 int number;//the number of the book that the user is borrowing
	 int namesize;//size of user name
	 int passwordsize;//size of password
	 
}User;
typedef struct _Userlist {
	 User* list; // pointer to a list of struct user.
	 unsigned int length; // number of elements in the (User*) List 
}Userlist;

#endif