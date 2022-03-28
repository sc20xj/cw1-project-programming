
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"library.h"
#include"projectheader.h"

#include"lo_st.h"
#include"myutility.h"

BookList* bgn;
Userlist *userbgn;




int registerCLI(){
    User *userstart=userbgn->list->next;
    
    User * userstart2=userbgn->list;
   

   start:
    printf("\n Please enter the user name(input quit to return)\n");
    char name[1000];
    scanf("%[^\n]",name);
    fflush(stdin);
   if(strcmp(name,"quit")==0){
         fflush(stdin);
        return 0;
    }
    while(userbgn->list->next!=NULL){      
        if(strcmp(userbgn->list->next->name,name)==0){
            printf("Error,this name has already been used.");
            userbgn->list->next=userstart;
            goto start;
        }
        userbgn->list->next=userbgn->list->next->next;
       
    }
    printf("\n Please enter the password\n");
    char password[1000];
    scanf("%[^\n]",password);
     fflush(stdin);
    userbgn->list->next=userstart;
    while(userbgn->list->next!=NULL){     
        userbgn->list=userbgn->list->next;
    }
    
    User* new=(User*)malloc(sizeof(User));
    new->name=(char *)malloc(1000*sizeof(char));
    new->password=(char *)malloc(1000*sizeof(char));
    new->bookborrow=(Book*)malloc(sizeof(Book));
    new->bookborrow->next=NULL;
    new->number=0;
    userbgn->length+=1;
    strcpy(new->name,name);
    strcpy(new->password,password); 
     
    userbgn->list->next=new;
    
  
    new->next=NULL;
    userbgn->list=userstart2;
    if(userstart!=NULL){
    userbgn->list->next=userstart;
    }
    
    return 1;
}




User* loginCLI(){
    
    int a=0;
    int b=0;
    int confirm=0;
    int confirm2=0;
    User *userstart=userbgn->list->next;
    User* final;
    User* temp=NULL;
    while(confirm==0){
     printf("Please enter the user name(input quit to return)\n");
    char name[1000];
    scanf("%[^\n]",name);
    if(strcmp(name,"quit")==0){
         fflush(stdin);
        return temp;
    }
    fflush(stdin);
    while(userbgn->list->next!=NULL){
        if(strcmp(userbgn->list->next->name,name)==0){
           a+=1;
           break;  
        }
        userbgn->list->next=userbgn->list->next->next;
    }
    if(a==0){
         printf("Error, there is no that name\n");
         userbgn->list->next=userstart;
    }
    else{
        confirm+=1;
    }
    }
    while(confirm2==0){
    printf("Please enter the password(input quit to return)\n");
    char password[1000];
    scanf("%[^\n]",password);
     if(strcmp(password,"quit")==0){
          fflush(stdin);
        return temp;
    }
     fflush(stdin);
     while(userbgn->list->next!=NULL){
        if(strcmp(userbgn->list->next->password,password)==0){
           b+=1;
           final=userbgn->list->next;
           userbgn->list->next=userstart;
           break;  
        }
        userbgn->list->next=userbgn->list->next->next;
    }
    if(b==0){
        printf("Error, the password is wrong\n");
        userbgn->list->next=userstart;
        
    }
    else{ printf("Successfully Logined\n");
            confirm2=1;}
   

}
return final;
}





int librarianlogin(){
     int a=0;
    int b=0;
    int confirm=0;
    int confirm2=0;
    
    while(confirm==0){
     printf("Please enter the user name(input quit to return)\n");
    char name[1000];
    scanf("%[^\n]",name);
    if(strcmp(name,"quit")==0){
         fflush(stdin);
        return 0;
    }
    fflush(stdin);
        if(strcmp("librarian",name)==0){
           a+=1;
           break;  
        }
    if(a==0){
         printf("Error, the name is wrong\n");
    }
    else{
        confirm+=1;
    }
    }
    while(confirm2==0){
    printf("Please enter the password(input quit to return)\n");
    char password[1000];
    scanf("%[^\n]",password);
     if(strcmp(password,"quit")==0){
          fflush(stdin);
          return 0;
    }
     fflush(stdin);
   
        if(strcmp("librarian",password)==0){
           b+=1;
          
           break;  
        }
   
    if(b==0){
        printf("Error, the password is wrong\n");
        
    }
    else{ printf("Successfully Logined\n");
            confirm2=1;
            }
}
   return 1;
}




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
    printf("\n Please choose an option\n 1)Search for books\n 2)Display all books\n 3)Add book\n 4)Remove book\n 5)Show History\n 6)Back to previous\n 7)Exit\n Choice:");
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
            printf("\nPlease input book id\n");
           int x;
          x=optionChoice();
         if(x==-1){
       printf("\n You should input a digit \n");
            fflush(stdin);
            continue;
             }
             new.id=x;
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
              printf("Show History\n");
            showhistory();
        }
        else if(option==6){
            printf("\nBack\n");
            login=0;
            
        }
         else if(option==7){
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