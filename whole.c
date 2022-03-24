
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
     int open=1;
      int option;
     while(open==1){
      printf("\n Please choose an option\n 1)search by title\n 2)search by author\n 3)search by year\n 4)return to previous menu\n5)Exit Search\nChoice:");
      option = optionChoice();
      char searching[1000];
     
     
       if( option == 1 ) {
            printf("\n search by title \n");
            scanf("%s",searching);
            getchar();
            find_book_by_title(searching);
            open=0;
        }
        else if( option == 2 ) {
            printf("\n search by author \n");
            scanf("%s",searching);
            getchar();
            find_book_by_author(searching);
            open=0;
        }
        else if( option == 3 ) {
            int x;
            printf("\n search by year \n");
            scanf("%d",x);
            getchar();
            find_book_by_year(x);
            open=0;
        }
        else if(option==4){
            printf("\n Return to previous \n");
            open=1;
        }
        else if(option==5){
            printf("\n Exit Search\n");
            open=0;
        }
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
        user1->bookborrow=(Book*)malloc(sizeof(Book));
        user1->bookborrow->next=NULL;
        
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

User* loginCLI(){
    
    int a=0;
    int b=0;
    int confirm=0;
    int confirm2=0;
    User *userstart=userbgn->list->next;
    User* final;
    while(confirm==0){
     printf("Please enter the user name\n");
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
         printf("Error, there is no that name\n");
         userbgn->list->next=userstart;
    }
    else{
        confirm+=1;
    }
    }
    while(confirm2==0){
    printf("Please enter the password\n");
    char password[1000];
    scanf("%s",password);
    getchar();
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





void closecil(FILE* book,FILE* user){
    store_books(book);
    store_user(user);
    User* temp;
    Book* temp2;
    while(userbgn->list->next!=NULL){
        temp=userbgn->list->next;
        userbgn->list->next=userbgn->list->next->next;
        free(temp);
    }
     while(bgn->list->next!=NULL){
        temp2=bgn->list->next;
        bgn->list->next=bgn->list->next->next;
        free(temp2);
    }
    free(userbgn->list);
    free(bgn->list);
    free(bgn);
    free(userbgn);
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

int Borrowbooks(User* logeduser){
   listavailablebook();
   printf("\nwhich do you want to borrow: ");
   int id;
   scanf("%d",&id);
   getchar();
   Book* bookstart=bgn->list->next;
  
   while(bgn->list->next->id!=id){
       
       bgn->list->next=bgn->list->next->next;
       
       if(bgn->list->next==NULL){
           bgn->list->next=bookstart;
           printf("Error,id out of range");
           return 0;
       }
   } 
   bgn->list->next->copies-=1;
    
  while(logeduser->bookborrow->next!=NULL){
      logeduser->bookborrow=logeduser->bookborrow->next;
  }
  
   logeduser->bookborrow->next=(Book*)malloc(sizeof(Book));
   logeduser->bookborrow->next->id=bgn->list->next->id;
   logeduser->bookborrow->next->year=bgn->list->next->year;
   logeduser->bookborrow->next->authors=bgn->list->next->authors;
   logeduser->bookborrow->next->title=bgn->list->next->title;
   logeduser->bookborrow->next->next=NULL;
   User *temp=bgn->list->next->history;
   while(bgn->list->next->history->next!=NULL){
        bgn->list->next->history=bgn->list->next->history->next;
   }
   bgn->list->next->history->next=(User*)malloc(sizeof(User));
 bgn->list->next->history->next->name=logeduser->name;
 bgn->list->next->history->next->next=NULL;
  bgn->list->next=bookstart;
  bgn->list->next->history=temp;
    
    return 1;
}

void showhistory(){
     User *temp=bgn->list->next->history->next;
     Book* bookstart=bgn->list->next;
    while(bgn->list->next!=NULL){
        while(bgn->list->next->history->next!=NULL){
            printf("%s->%s\t",bgn->list->next->title,bgn->list->next->history->next->name);
              bgn->list->next->history->next= bgn->list->next->history->next->next;
              
        }
        printf("\n");
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next=bookstart;
    bgn->list->next->history->next=temp;
    
}








void librarycil(FILE* book,FILE* user){
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
            registerCLI();
        }
        else if( option == 2 ) {
        printf("\n Login");
         printf("\n Please choose an option\n 1)librarian Login\n 2)User Login\n 3)Back to previous\n Choice:");
         option = optionChoice();
        if(option==1){
        logininguser=loginCLI();
            login=2;
        }
        else if(option==2){
        logininguser= loginCLI( );
            login=1;
        }
         else if(option==3){
            login=0;
        }
        }
        else if(option==3){
            printf("Exit");
              closecil(book,user);
            libraryopen=0;
          
        }
       
       
   }
    while(libraryopen&&login==1){
       printf("\n Please choose an option\n 1) Search for books\n 2)Display all books\n 3)Borrow books\n 4)Return books\n 5)Back to previous\n 6)Exit\n Choice:");
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
             //Returnbooks();
        }

        else if(option==5){
            printf("\nBack\n");
            login=0;
        }
        else if(option==6){
            printf("\nClose\n");
            closecil(book,user);
            libraryopen=0;
        }

    }
    while(libraryopen&&login==2){
    printf("\n Please choose an option\n 1) Search for books\n 2)Display all books\n 3)Add book\n 4)Remove book\n 5)Show History\n 6)Back to previous\n 7)Exit\n Choice:");
       option = optionChoice();
        if( option == 1 ) {
            printf("\n Search for books\n");
            searchbooks();
        }
        else if(option==2){
            printf("\n Display all books\n");
            display();
        }
        else if(option==3){
            printf("\n Add book\n");
            
        }
        else if(option==4){
            printf("\n Remove book\n");
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
            closecil(book,user);
            libraryopen=0;
            
        }


    }

}
}

int main( int argc, char **argv )
{
  
  
   FILE *user=fopen("user.txt","r+");
   FILE *fp =fopen("books.txt","r+");
   
   load_books(fp);
    
   load_user(user);
  

   librarycil(fp,user);
    
   

    return 0;
}
