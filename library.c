#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"login_register.h"
#include"bookmanagement.h"
#include"show.h"
#include"lo_st.h"
#include"myutility.h"

BookList* bgn;
Userlist *userbgn;





void librarycil(FILE* book,FILE* user,FILE* history,FILE* borrow){
int libraryopen=1;
int option;
int login=0;
User *logininguser;

   while(libraryopen){
   while(login==0){
       printf("\n Please choose an option\n 1)Register an account\n 2)Login\n 3)Exit\n Choice:");
         option = optionChoice();
          if( option == 1 ) {
            printf("\nRegister an account\n");
            int k=registerCLI();
            if(k==1){
                printf("\nSuccessfully registered\n");
            }
        }
        else if( option == 2 ) {
        printf("\n Login");
         printf("\n Please choose an option\n 1)librarian Login\n 2)User Login\n 3)Back to previous\n Choice:");
         option = optionChoice();
        if(option==1){
        int x=librarianlogin();
        if(x==0){
            login=0;
        }
        else{
            login=2;
        }
        }
        else if(option==2){
        logininguser= loginCLI();
         if(logininguser==NULL){
             login=0;
         }
         else{
            login=1;
         }
        }
         else if(option==3){
            login=0;
        }
        }
        else if(option==3){
            printf("Exit");
            closecil(book,user,history,borrow);
            libraryopen=0;
            login=1;
          
        }
        else{
              printf("\nUnknown option\n");
        }
       
       
   }
    while(libraryopen&&login==1){
       printf("\n Please choose an option\n 1)Search for books\n 2)Display all books\n 3)Borrow books\n 4)Return books\n 5)Back to previous\n 6)Exit\n Choice:");
       option = optionChoice();
      
        if( option == 1 ) {
            printf("\nSearch for books\n");
            searchbooks();
        }
        else if(option==2){
            printf("\nDisplay all books\n");
            display();
        }
        else if(option==3){
            printf("\nBorrow books\n");
             Borrowbooks(logininguser);
        }
        else if(option==4){
            printf("\nReturn books\n");
            return_book(logininguser);
        }

        else if(option==5){
            printf("\nBack\n");
            login=0;
        }
        else if(option==6){
            printf("\nClose\n");
            closecil(book,user,history,borrow);
            libraryopen=0;
        }
        else{
          printf("\nUnknown option\n");
        }
    }
    while(libraryopen&&login==2){
    printf("\n Please choose an option\n 1)Search for books\n 2)Display all books\n 3)Add book\n 4)Remove book\n 5)Show History\n 6)Show borrowing\n 7)Back to previous\n 8)Exit\n Choice:");
       option = optionChoice();
        if( option == 1 ) {
            printf("\nSearch for books\n");
            searchbooks();
        }
        else if(option==2){
            printf("\n Display all books\n");
            display();
        }
        else if(option==3){
            printf("\n Add book\n");
            
            int year;
            int copies;
            Book new;
            new.history=(User*)malloc(sizeof(User));
            new.history->next=NULL;
          int x;
            printf("\nPlease input book year\n");      
   x=optionChoice();
   if(x==-1){
       printf("\n You should input a digit \n");
            fflush(stdin);
            continue;
   }
   new.year=x;
            
        printf("\nPlease input book copies\n");
               
        x=optionChoice();
            if(x==-1){
       printf("\n You should input a digit \n");
            fflush(stdin);
            continue;            
   }
        new.copies=x;
              printf("\nPlease input book author\n");
              new.authors=(char*)malloc(100*sizeof(char));
              scanf("%[^\n]",new.authors);
              fflush(stdin);
               printf("\nPlease input book title\n");
              new.title=(char*)malloc(100*sizeof(char));
              scanf("%[^\n]",new.title);
              fflush(stdin);
              add_book(new);
            
        }
        else if(option==4){
            int id;
            Book temp;
            printf("\n Remove book\n");
             printf("\nPlease input book id\n");
           int x;
          x=optionChoice();
         if(x==-1){
       printf("\n You should input a digit \n");
            fflush(stdin);
            continue;
             }
             temp.id=x;
            remove_book(temp);
        }
          else if(option==5){
              printf("\nShow History\n");
            showhistory();
        }

          else if(option==6){
            printf("\nShow borrowing\n");
            showborrowing();
        
        }
        else if(option==7){
            printf("\nBack\n");
            login=0;
        
        }

         else if(option==8){
            printf("\nClose\n");
            closecil(book,user,history,borrow);
            libraryopen=0;
            
        }
         else{
          printf("\nUnknown option\n");
        }


    }

}
}




void closecil(FILE* book,FILE* user,FILE* history,FILE*borrow){
    
    store_books(book);
    
    store_user(user);
 
    store_history(history);
    
  store_borrowed(borrow);
    
    User* temp;
    Book* temp2;
    User * temp3;
    Book* temp4;
    while(userbgn->list->next!=NULL){
        while(userbgn->list->next->bookborrow->next!=NULL){
             temp4=userbgn->list->next->bookborrow->next;
             userbgn->list->next->bookborrow->next=userbgn->list->next->bookborrow->next->next;
             free(temp4);
        }
        temp=userbgn->list->next;
        userbgn->list->next=userbgn->list->next->next;
        free(temp);
    }
      
     while(bgn->list->next!=NULL){
          while(bgn->list->next->history->next!=NULL){
            temp3=bgn->list->next->history->next;
            bgn->list->next->history->next=bgn->list->next->history->next->next;
            free(temp3);
        }
         free(bgn->list->next->history);
        temp2=bgn->list->next;
        bgn->list->next=bgn->list->next->next;
        free(temp2);
        
    }
    
   
    free(userbgn->list);
    free(bgn->list);
    free(bgn);
    free(userbgn);
   
}

