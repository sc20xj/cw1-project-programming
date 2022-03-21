#include "projectheader.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"myutility.h"
load_books();
BookList *bgn=0;
Userlist *userbgn=0;
FILE *user=0;
FILE *userstore=0;
FILE *fp=0;
FILE *fp2=0;
User *userfinal=0;
void librarycil(){
   int libraryopen=1;
   int option;
   while(libraryopen){
       printf("\n Please choose an option\n 1) Register an account\n 2) Login\n 3) Search for books\n 4)Display all books\n 5)Quit\n Choice:");
       option = optionChoice();
       if( option == 1 ) {
            printf("\nRegister an account\n");
            registerCLI(  );
        }
        else if( option == 2 ) {
            printf("\nLogin\n");
            loginCLI( );
        }
        else if( option == 3 ) {
            printf("\n Search for books\n");
            searchbooks();
        }
        else if(option==4){
            printf("\n Display all books\n");
            display();
        }
        else if (option==5){
            libraryopen=0;
             printf("\n See you\n");
             closelibrary();
        }
        
    }
   }

void display(){
    Book* liststart=bgn->list->next;
    while(bgn->list->next!=NULL){
        printf("%d %s %s %d %d\n",bgn->list->next->id,bgn->list->next->title,bgn->list->next->authors,bgn->list->next->year,bgn->list->next->copies);
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next=liststart;
}

void searchbooks(){
      printf("\n Please choose an option\n 1)search by title\n 2)search by author\n 3)search by year\n 4)return to previous menu");
      int option = optionChoice();
      char searching[1000];
       if( option == 1 ) {
            printf("\n search by title \n");
            scanf("%s",searching);
            getchar();
            find_book_by_title(searching);
        }
        else if( option == 2 ) {
            printf("\n search by author \n");
            scanf("%s",searching);
            getchar();
            find_book_by_author(searching);
        }
        else if( option == 3 ) {
            int x;
            printf("\n search by year \n");
            scanf("%d",x);
            getchar();
            find_book_by_year(x);
        }
        else if(option==4){
            printf("\n return to previous \n");
        }
}


int load_books(FILE *file){
     if (file == NULL ){
    printf("Error\nUser file does not exist: %s\n");
	return 1;
	
     }
	userfinal=(User*)malloc(sizeof(User));
	
	userbgn=(User*)malloc(sizeof(User));
    userbgn->list=userfinal;
    userbgn->length=0;
    while (!feof(file))
	{		
		User* user1=(User*)malloc(sizeof(User));
		userfinal->next=user1;
        
        user1->name=(char *)malloc(100*sizeof(char));
        user1->password=(char *)malloc(100*sizeof(char));
		
        fscanf(file,"%s %s\n",user1->name,user1->password);
        userbgn->length+=1;
        
         
        userfinal=user1;
		
		
	}
	userfinal->next=NULL;
	return 0;
    
}

int store_user(FILE *file){
    User* userstart=userbgn->list->next;
   if (file == NULL ){
    printf("Error\nUser file does not exist: %s\n");
    exit(0);
}
while(userbgn->list->next!=NULL){
    fprintf(file," %s %s \n",userbgn->list->next->name,userbgn->list->next->password);
    userbgn->list->next=userbgn->list->next->next;
}
  userbgn->list->next=userstart;
  return 0;
}

void registerCLI(){
    User *userstart=userbgn->list->next;
    printf("\n Please enter the user name\n");
    char name[1000];
    scanf("%s",name);
    getchar();
    printf("\n Please enter the password\n");
    char password[1000];
    scanf("%s",password);
    getchar();
    while(userbgn->list->next!=NULL){
        userbgn->list->next=userbgn->list->next->next;
    }
    User *new=(User*)malloc(sizeof(User));
    new->name=name;
    new->password=password;
    userbgn->list->next=new;
    new->next=NULL;
    userbgn->list->next=userstart;
}

void loginCLI(){
    char* ajkdlaj;
}