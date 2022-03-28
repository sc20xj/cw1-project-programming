
#ifndef BOOK_MANAGEMENT_GUARD_lo 
#define BOOK_MANAGEMENT_GUARD__lo

#include <stdio.h>
#include"projectheader.h"

extern Book* bgn;
extern Userlist *userbgn;

int store_books(FILE *file);

int load_books(FILE *file);

int load_user(FILE *file);


int store_user(FILE *file);

int store_history(FILE *file);


int load_borrow(FILE* file);


int store_borrowed(FILE *file);


void closecil(FILE* book,FILE* user,FILE* history,FILE*borrow);

#endif
