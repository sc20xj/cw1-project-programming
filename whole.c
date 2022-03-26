
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
      printf("\n Please choose an option\n 1)search by title\n 2)search by author\n 3)search by year\n 4)Exit Search\nChoice:");
      option = optionChoice();
      char searching[1000];
     
     
       if( option == 1 ) {
            printf("\nSearch by title");
            scanf("%s",searching);
            getchar();
            BookList search;
            search=find_book_by_title(searching);
            if(search.list==NULL){
                open = 0;
            }
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
            printf("\nSearch by author");
            scanf("%s",searching);
            getchar();
             BookList search;
            search=find_book_by_author(searching);
            if(search.list==NULL){
                open = 0;
            }
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
            printf("\nSearch by year");
            x=optionChoice();
            if(x==-1){
                printf("\n You should input a year \n");
                fflush(stdin);
            }
            else{
             BookList search;
             fflush(stdin);
            search=find_book_by_year(x);
            if(search.list==NULL){
                open = 0;
            }
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
        user1->number=0;
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


int load_history(FILE* file){
    Book* bookstart=bgn->list->next;
    
    while(bgn->list->next!=NULL){
        User* temp=bgn->list->next->history;
        fscanf(file,"%d", &bgn->list->next->borrowed);
       
    
        for(int i=0;i<bgn->list->next->borrowed;i++){
        
            User* new=(User*)malloc(sizeof(User));
               
             bgn->list->next->history->next=new;
            bgn->list->next->history->next->name=(char*)malloc(100*sizeof(char));
             fscanf(file,"%s", bgn->list->next->history->next->name);
             
             new->next=NULL;
             
             bgn->list->next->history=new;
             
        }
        bgn->list->next->history=temp;
        bgn->list->next=bgn->list->next->next;
        
        
    }
    
    bgn->list->next=bookstart;
    return 0;
     
}



int store_history(FILE *file){ 
    while(bgn->list->next!=NULL){   
         fprintf(file,"\n%d \t",bgn->list->next->borrowed);
        while(bgn->list->next->history->next!=NULL){
             fprintf(file,"%s\t",bgn->list->next->history->next->name);
              bgn->list->next->history->next= bgn->list->next->history->next->next;           
        }  
        bgn->list->next=bgn->list->next->next;
    }
    return 0;
  
}
int load_borrow(FILE* file){
    User* userstart=userbgn->list->next;
    while(userbgn->list->next!=NULL){
        Book* temp=userbgn->list->next->bookborrow;
         fscanf(file,"%d", &userbgn->list->next->number);
     
        for(int i=0;i<userbgn->list->next->number;i++){
        
            Book* new=(Book*)malloc(sizeof(Book));
               
             userbgn->list->next->bookborrow->next=new;
            userbgn->list->next->bookborrow->next->authors=(char*)malloc(100*sizeof(char));
            userbgn->list->next->bookborrow->next->title=(char*)malloc(100*sizeof(char));
             fscanf(file,"%d %s %s %d", &userbgn->list->next->bookborrow->next->id,userbgn->list->next->bookborrow->next->authors,userbgn->list->next->bookborrow->next->title,&userbgn->list->next->bookborrow->next->year);
             new->next=NULL;
             
             userbgn->list->next->bookborrow=new;
             
        }
        userbgn->list->next->bookborrow=temp;
        userbgn->list->next=userbgn->list->next->next;
        
        
    
    }
    userbgn->list->next=userstart;
    return 0;
}

int store_borrowed(FILE *file){
    while(userbgn->list->next!=NULL){
        fprintf(file,"\n%d \t",userbgn->list->next->number);
       while(userbgn->list->next->bookborrow->next!=NULL){
            fprintf(file,"%d\t%s\t%s\t%d\t",userbgn->list->next->bookborrow->next->id,userbgn->list->next->bookborrow->next->authors,userbgn->list->next->bookborrow->next->title,userbgn->list->next->bookborrow->next->year);
            userbgn->list->next->bookborrow->next=userbgn->list->next->bookborrow->next->next;
       }
       userbgn->list->next=userbgn->list->next->next;
    }
    return 0;
}



void registerCLI(){
    User *userstart=userbgn->list->next;
   start:
    printf("\n Please enter the user name\n");
    char name[1000];
    scanf("%s",name);
    fflush(stdin);
   
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
     fflush(stdin);
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
    User* temp=NULL;
    while(confirm==0){
     printf("Please enter the user name(input quit to return)\n");
    char name[1000];
    scanf("%s",name);
    if(strcmp(name,"quit")==0){
         fflush(stdin);
        return temp;
    }
    fflush(stdin);
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
    printf("Please enter the password(input quit to return)\n");
    char password[1000];
    scanf("%s",password);
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


void listavailablebook(){
     Book* liststart=bgn->list->next;
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
     while(bgn->list->next!=NULL){
         if(bgn->list->next->copies>0){
          printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",bgn->list->next->id,bgn->list->next->authors,bgn->list->next->title,bgn->list->next->year,bgn->list->next->copies);
         }
        bgn->list->next=bgn->list->next->next;
     }
     bgn->list->next=liststart;
}


int Borrowbooks(User* logeduser){
   listavailablebook();
   printf("\nwhich do you want to borrow: ");
  int id;
  id=optionChoice();
   if(id==-1){
           printf("\n You should input a digit \n");
            fflush(stdin);
   }
   else{
        fflush(stdin);
   Book* bookstart=bgn->list->next;
  
   while(bgn->list->next->id!=id){
       
       bgn->list->next=bgn->list->next->next;
       
       if(bgn->list->next==NULL){
           bgn->list->next=bookstart;
           printf("Error,id is out of range");
           return 0;
       }
   } 
   bgn->list->next->copies-=1;
    Book* temp2=logeduser->bookborrow;
  while(logeduser->bookborrow->next!=NULL){
      logeduser->bookborrow=logeduser->bookborrow->next;
  }
  
   logeduser->bookborrow->next=(Book*)malloc(sizeof(Book));
   logeduser->bookborrow->next->id=bgn->list->next->id;
   logeduser->bookborrow->next->year=bgn->list->next->year;
   logeduser->bookborrow->next->authors=bgn->list->next->authors;
   logeduser->bookborrow->next->title=bgn->list->next->title;
   logeduser->bookborrow->next->next=NULL;
   logeduser->bookborrow=temp2;
   logeduser->number+=1;
   User *temp=bgn->list->next->history;
   while(bgn->list->next->history->next!=NULL){
        bgn->list->next->history=bgn->list->next->history->next;
   }
   
   bgn->list->next->history->next=(User*)malloc(sizeof(User));
   
 bgn->list->next->history->next->name=logeduser->name;
 bgn->list->next->history->next->next=NULL;
 bgn->list->next->borrowed+=1;
  bgn->list->next->history=temp;
   bgn->list->next=bookstart;
    
    return 1;
   }
}


int showborrowed(User* logeduser){
Book* temp=logeduser->bookborrow->next;
if(temp==NULL){
    printf("\nYou have not borrowed any book\n");
    return 0;
}
 printf("%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR");
    while(logeduser->bookborrow->next!=NULL){  
         printf("%-10d\t%-10s\t%-10s\t%-10d\n",logeduser->bookborrow->next->id,logeduser->bookborrow->next->authors,logeduser->bookborrow->next->title,logeduser->bookborrow->next->year);
        logeduser->bookborrow->next=logeduser->bookborrow->next->next;
    }
    logeduser->bookborrow->next=temp;
    return 1;
}


int return_book(User* logeduser){
    int y;
y=showborrowed(logeduser);
if(y==0){
    return 1;
}
Book* bookstart=bgn->list->next;
Book* temp2=logeduser->bookborrow;
Book* temp=logeduser->bookborrow->next;
    printf("\nwhich do you want to return: ");
   int id;
   id=optionChoice();
   if(id==-1){
       printf("\n You should input a digit \n");
            fflush(stdin);
   }
   else{
    if(logeduser->bookborrow->next!=NULL){
    while(logeduser->bookborrow->next->id!=id){
            logeduser->bookborrow->next=logeduser->bookborrow->next->next;
            if(logeduser->bookborrow->next==NULL){
           logeduser->bookborrow->next=temp;
           printf("Error,id is out of range");
           
           return 0;
       }
    }
    while(bgn->list->next!=NULL){
        if(bgn->list->next->id==id){
            bgn->list->next->copies+=1;
            break;
        }
        bgn->list->next=bgn->list->next->next;
        if(bgn->list->next==NULL){
            printf("The book has been deleted");
        }
    }
    bgn->list->next=bookstart;
    Book* next =logeduser->bookborrow->next->next;
    Book* aim=logeduser->bookborrow->next;
    logeduser->bookborrow->next=temp;
   while(logeduser->bookborrow->next!=aim){
       logeduser->bookborrow=logeduser->bookborrow->next;
   }
   logeduser->bookborrow->next=next;
   
   logeduser->bookborrow=temp2;
   logeduser->number-=1;
    free(aim);
    }
    else{
        printf("You have not borrowed any books");
    }
   }
}








void showhistory(){
     Book* bookstart=bgn->list->next;
      printf("%-10s\t%-10s\n","Title","Name~~");   
    while(bgn->list->next!=NULL){   
        printf("%-10s\t",bgn->list->next->title);   
         User *temp=bgn->list->next->history->next;
        while(bgn->list->next->history->next!=NULL){
            printf("%-10s\t",bgn->list->next->history->next->name);
              bgn->list->next->history->next= bgn->list->next->history->next->next;  
                      
        }
         bgn->list->next->history->next=temp; 
        bgn->list->next=bgn->list->next->next;
        printf("\n");
    }
    bgn->list->next=bookstart;
    
    
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
            registerCLI();
        }
        else if( option == 2 ) {
        printf("\n Login");
         printf("\n Please choose an option\n 1)librarian Login\n 2)User Login\n 3)Back to previous\n Choice:");
         option = optionChoice();
        if(option==1){
        logininguser=loginCLI();
           if(logininguser==NULL){
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
            closecil(book,user,history,borrow);
            libraryopen=0;
            
        }
         else{
          printf("\nUnknown option\n");
        }


    }

}
}

int main( int argc, char **argv )
{
   
  
   FILE *user=fopen("user.txt","r+");
   FILE *fp =fopen("books.txt","r+");
   FILE *history=fopen("data3.txt","r+");
   FILE *borrow=fopen("userborrow.txt","r+");
   load_books(fp);
   load_user(user);
   load_history(history);
   load_borrow(borrow);
   fclose(borrow);
   fclose(history);
   fclose(user);
   fclose(fp);
   FILE *fp1 =fopen("books.txt","w");
   FILE *user1=fopen("user.txt","w");
   FILE *history1=fopen("data3.txt","w");
   FILE *borrow1=fopen("userborrow.txt","w");
  
   librarycil(fp1,user1,history1,borrow1);
    fclose(fp1);
    fclose(user1);
    fclose(history);
    fclose(borrow1);
    return 0;
}
