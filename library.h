
#ifndef BOOK_MANAGEMENT_GUARD__library
#define BOOK_MANAGEMENT_GUARD__library


#include <stdio.h>
#include"projectheader.h"
#include"lo_st.h"
#include"myutility.h"


void librarycil(FILE* book,FILE* user,FILE* history,FILE* borrow);


int registerCLI();

int librarianlogin();

User* loginCLI();

#endif
