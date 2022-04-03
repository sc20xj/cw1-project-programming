
#ifndef BOOK_MANAGEMENT_GUARD__library
#define BOOK_MANAGEMENT_GUARD__library

#include <stdio.h>
#include"structure.h"
#include"lo_st.h"
#include"myutility.h"
#include"show.h"

//The search books system.
void searchbooks();

// The whole system of this app, which connected each part together
void librarycil(FILE* book,FILE* user,FILE* history,FILE* borrow);

//The function to close the library, including free the allocated address
void closecil(FILE* book,FILE* user,FILE* history,FILE*borrow);





#endif