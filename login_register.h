
#ifndef BOOK_MANAGEMENT_GUARD__library1
#define BOOK_MANAGEMENT_GUARD__library1


#include <stdio.h>
#include"structure.h"
#include"lo_st.h"
#include"myutility.h"




//The function to register for users, return 1 if register successfully
//or the error codes otherwise.
int registerCLI();

//The function for librarian to login, return 1  if it successfully logined
//or the error codes otherwise.
int librarianlogin();

//The function to Login for users, return the user struct address if it successfully logined
//or the error codes otherwise.
User* loginCLI();


#endif
