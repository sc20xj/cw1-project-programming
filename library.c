#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"login_register.h"
#include"structure.h"
#include"show.h"
#include"lo_st.h"
#include"myutility.h"

BookList* bgn;//the pointer to the booklist
Userlist *userbgn;//the pointer to the user list



//The function to close the library, including free the allocated address
void closecil(FILE* book,FILE* user,FILE* history,FILE*borrow){
    
    store_books(book);
    
    store_user(user);
 
    store_history(history);
    
    store_borrowed(borrow);
    
    User* temp;
    Book* temp2;
    User * temp3;
    Book* temp4;

    //running through the userlist to free the allocated address of users' book borrow list and userlist
    while(userbgn->list->next!=NULL){
        while(userbgn->list->next->bookborrow->next!=NULL){
             temp4=userbgn->list->next->bookborrow->next;
             userbgn->list->next->bookborrow->next=userbgn->list->next->bookborrow->next->next;
             //free each book borrow node
             free(temp4);
        }
        temp=userbgn->list->next;
        userbgn->list->next=userbgn->list->next->next;
        //free each user node
        free(temp);
    }
      
       //running through the booklist to free the allocated address of book's history list and booklist
     while(bgn->list->next!=NULL){
          while(bgn->list->next->history->next!=NULL){
            temp3=bgn->list->next->history->next;
            bgn->list->next->history->next=bgn->list->next->history->next->next;
            //free each history node
            free(temp3);
        }
         free(bgn->list->next->history);
        temp2=bgn->list->next;
        bgn->list->next=bgn->list->next->next;
        //free each book node
        free(temp2);
        
    }
    
   
    free(userbgn->list);
    free(bgn->list);
    free(bgn);
    free(userbgn);
   
}


//The search books system.
void searchbooks(){
     int open=1;
      int option;
     while(open==1){
      printf("\n Please choose an option\n 1)search by title\n 2)search by author\n 3)search by year\n 4)Exit Search\nChoice:");
      option = optionChoice();
      char searching[1000];
     
     
       if( option == 1 ) {
            printf("\nSearch by title\n");
            scanf("%[^\n]",searching);
            getchar();
            BookList search;
            search=find_book_by_title(searching);
            if(search.list==NULL){
                open = 0;
            }
            //show the search result
            else{
            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
            for(int i=0;i<search.length;i++){
                printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",search.list->id,search.list->authors,search.list->title,search.list->year,search.list->copies);
                search.list=search.list->next;
            }
            open=0;
            }
        }
        else if( option == 2 ) {
            printf("\nSearch by author\n");
            scanf("%[^\n]",searching);
            getchar();
             BookList search;
            search=find_book_by_author(searching);
            if(search.list==NULL){
                open = 0;
            }
             //show the search result
            else{
            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
             for(int i=0;i<search.length;i++){
                printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",search.list->id,search.list->authors,search.list->title,search.list->year,search.list->copies);
                search.list=search.list->next;
            }
            open=0;
            }
        }
        else if( option == 3 ) {
            int x;
            printf("\nSearch by year\n");
            x=optionChoice();
            if(x==-1){
                printf("\n You should input a year \n");
                getchar();
            }
            else{
             BookList search;
                getchar();
            search=find_book_by_year(x);
            if(search.list==NULL){
                open = 0;
            }
             //show the search result
            else{
             printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
             for(int i=0;i<search.length;i++){
                printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",search.list->id,search.list->authors,search.list->title,search.list->year,search.list->copies);
                search.list=search.list->next;
            }
            }
            
            open=0;
            }
        }
       
        else if(option==4){
            printf("\n Exit Search\n");
            open=0;
        }
         else{
          printf("\nUnknown option\n");
        }
      }
}


// The whole system of this app, which connected each part together
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
            
           //create the book entity to store and pass information
            Book new;
            new.history=(User*)malloc(sizeof(User));
            new.history->next=NULL;
          int x;
            printf("\nPlease input book year\n");      
   x=optionChoice();
   if(x==-1){
       printf("\n You should input a digit \n");
       getchar();
            continue;
   }
   new.year=x;
            
        printf("\nPlease input book copies\n");
               
        x=optionChoice();
            if(x==-1){
       printf("\n You should input a digit \n");
                getchar();
            continue;            
   }
        new.copies=x;
              printf("\nPlease input book author\n");
              new.authors=(char*)malloc(100*sizeof(char));
              scanf("%[^\n]",new.authors);
               getchar();
               printf("\nPlease input book title\n");
              new.title=(char*)malloc(100*sizeof(char));
              scanf("%[^\n]",new.title);
             getchar();
              add_book(new);
            
        }
        else if(option==4){
            
            Book temp;
            printf("\n Remove book\n");
             printf("\nPlease input book id\n");
           int x;
          x=optionChoice();
         if(x==-1){
       printf("\n You should input a digit \n");
             getchar();
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



