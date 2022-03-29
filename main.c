#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bookmanagement.h"
#include"lo_st.h"
#include"login_register.h"


int main( int argc, char **argv )
{
    char history[50];
    char user[50];
    char userborrowed[50];
    char books[50];
   if(strcmp( argv[1],"books.txt")!=0){
    printf("Error\nExpected use:books.txt\n"); 
    return 0;
    }
    if(strcmp( argv[2],"user.txt")!=0){
    printf("Error\nExpected use:user.txt\n"); 
    return 0;
    }

    if(strcmp( argv[3],"history.txt")!=0){
    printf("Error\nExpected use:history.txt\n"); 
    return 0;
    }

    if(strcmp( argv[4],"userborrow.txt")!=0){
    printf("Error\nExpected use:userborrow.txt\n"); 
    return 0;
    }
     strcpy(books,argv[1]);
     strcpy(user,argv[2]);
     strcpy(history,argv[3]);
     strcpy(userborrowed,argv[4]);

   FILE *user=fopen(user,"r+");
   FILE *fp =fopen(books,"r+");
   FILE *history=fopen(history,"r+");
   FILE *borrow=fopen(userborrowed,"r+");
   load_books(fp);
   load_user(user);
   load_history(history);
   load_borrow(borrow);
   fclose(borrow);
   fclose(history);
   fclose(user);
   fclose(fp);
   FILE *fp1 =fopen(books,"w");
   FILE *user1=fopen(user,"w");
   FILE *history1=fopen(history,"w");
   FILE *borrow1=fopen(userborrowed,"w");
  
   librarycil(fp1,user1,history1,borrow1);
    fclose(fp1);
    fclose(user1);
    fclose(history);
    fclose(borrow1);
    return 0;
}

