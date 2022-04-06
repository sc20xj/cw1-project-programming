#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"structure.h"
#include "bookmanagement.h"
#include"lo_st.h"
#include"login_register.h"
#include"library.h"

int main( int argc, char **argv )
{
    char history111[50];
    char user111[50];
    char userborrowed111[50];
    char books111[50];
   
     strcpy(books111,argv[1]);
     strcpy(user111,argv[2]);
     strcpy(history111,argv[3]);
     strcpy(userborrowed111,argv[4]);

   FILE *user=fopen(user111,"r+");
   FILE *fp =fopen(books111,"r+");
   FILE *history=fopen(history111,"r+");
   FILE *borrow=fopen(userborrowed111,"r+");
   load_books(fp);
   load_user(user);
   load_history(history);
   load_borrow(borrow);
   fclose(borrow);
   fclose(history);
   fclose(user);
   fclose(fp);
   FILE *fp1 =fopen(books111,"w");
   FILE *user1=fopen(user111,"w");
   FILE *history1=fopen(history111,"w");
   FILE *borrow1=fopen(userborrowed111,"w");
  
   librarycil(fp1,user1,history1,borrow1);
    fclose(fp1);
    fclose(user1);
    fclose(history);
    fclose(borrow1);
    return 0;
}

