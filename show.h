#ifndef BOOK_MANAGEMENT_GUARD_librarian
#define BOOK_MANAGEMENT_GUARD__librarian


#include <stdio.h>

#include"bookmanagement.h"
#include"lo_st.h"
#include"myutility.h"



void showhistory();

void listavailablebook();

void display();

int showborrowed(User* logeduser);

void showborrowing();



#endif