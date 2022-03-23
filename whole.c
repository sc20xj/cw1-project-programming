
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"myutility.h"
#include"projectheader.h"
#include"projectheader.c"
#include"myutility.c"

extern BookList* bgn;
Userlist *userbgn=0;




void display(){
    Book* liststart=bgn->list->next;
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
    while(bgn->list->next!=NULL){
        printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",bgn->list->next->id,bgn->list->next->title,bgn->list->next->authors,bgn->list->next->year,bgn->list->next->copies);
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


int load_user(FILE *file){
    
     if (file == NULL ){
    printf("Error\nUser file does not exist: %s\n");
	exit(0);
	
     }
	User* userfinal=(User*)malloc(sizeof(User));
	
	userbgn=(Userlist*)malloc(sizeof(Userlist));
    userbgn->list=userfinal;
    userbgn->length=0;
    char c=fgetc(file);
    if(c!=EOF){
        rewind(file);
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
    else{
        userbgn->list->next=NULL;        
        return 0;
    }
    
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
   start:
    printf("\n Please enter the user name\n");
    char name[1000];
    scanf("%s",name);
    getchar();
   
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
    scanf("%s",password);
    getchar();
    userbgn->list->next=userstart;
    while(userbgn->list->next->next!=NULL){     
        userbgn->list->next=userbgn->list->next->next;
    }
    User* new=(User*)malloc(sizeof(User));
    new->name=(char *)malloc(1000*sizeof(char));
    new->password=(char *)malloc(1000*sizeof(char));
    userbgn->length+=1;
    strcpy(new->name,name);
    strcpy(new->password,password); 
    userbgn->list->next->next=new;
    new->next=NULL;
    userbgn->list->next=userstart;
    
     
}

void loginCLI(){
    
    int a=0;
    int b=0;
    int confirm=0;
    int confirm2=0;
    User *userstart=userbgn->list->next;
    while(confirm==0){
     printf("\n Please enter the user name\n");
    char name[1000];
    scanf("%s",name);
   getchar();
   
    while(userbgn->list->next!=NULL){
        if(strcmp(userbgn->list->next->name,name)==0){
           a+=1;
           userbgn->list->next=userstart;
           break;  
        }
        userbgn->list->next=userbgn->list->next->next;
    }
    if(a==0){
         printf("\n Error, there is no that name\n");
         userbgn->list->next=userstart;
    }
    else{
        confirm+=1;
    }
    }
    while(confirm2==0){
    printf("\n Please enter the password\n");
    char password[1000];
    scanf("%s",password);
    getchar();
     while(userbgn->list->next!=NULL){
        if(strcmp(userbgn->list->next->password,password)==0){
           b+=1;
           userbgn->list->next=userstart;
           break;  
        }
        userbgn->list->next=userbgn->list->next->next;
    }
    if(b==0){
        printf("\n Error, the password is wrong\n");
        userbgn->list->next=userstart;
        
    }
    else{ printf("\n Successfully Logined\n");
            confirm2=1;}
   

}
}

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
        else if(option==5){
            printf("%s",userbgn->list->next->name);
            printf("%s",userbgn->list->next->next->name);
        }
        // else if(option==5){
        //     libraryopen=0;
        //     closelibrary();
        // }
       
        
    }
   }
void listavailablebook(){
     Book* liststart=bgn->list->next;
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
     while(bgn->list->next!=NULL){
         if(bgn->list->next->copies>0){
          printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",bgn->list->next->id,bgn->list->next->title,bgn->list->next->authors,bgn->list->next->year,bgn->list->next->copies);
         }
        bgn->list->next=bgn->list->next->next;
     }
     bgn->list->next=liststart;
}
void Borrowbooks(){
    
}

int main( int argc, char **argv )
{
  
    
   FILE *user=fopen("user.txt","r+");
   FILE *fp =fopen("books.txt","r+");
   
   load_books(fp);
   load_user(user);

   
   

   librarycil();
    
    

    return 0;
}
