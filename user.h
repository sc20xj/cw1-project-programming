#ifndef BOOK_MANAGEMENT_GUARD_user
#define BOOK_MANAGEMENT_GUARD__user

#include <stdio.h>
#include"projectheader.h"
#include"lo_st.h"
#include"myutility.h"

BookList find_book_by_title (const char *title);

BookList find_book_by_author (const char *author);

BookList find_book_by_year (unsigned int year);

void searchbooks();


int showborrowed(User* logeduser);


int return_book(User* logeduser);



void listavailablebook();

int Borrowbooks(User* logeduser);

#endif
