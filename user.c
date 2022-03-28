#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"myutility.h"
#include"projectheader.h"

#include"lo_st.h"

BookList* bgn;
Userlist *userbgn;

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title){
   Book* liststart=bgn->list->next;
    BookList findbytitle;
    findbytitle.list=0;  
    findbytitle.length=0; 
    Book* booknew=(Book*)malloc(sizeof(Book));
    Book* start=booknew;
    int a=0;
    for (int i=0; i< bgn->length; i++) {
			if (!strcmp(bgn->list->next->title, title)){  
                   
               booknew->id=bgn->list->next->id;
               booknew->year=bgn->list->next->year;
               booknew->copies=bgn->list->next->copies;
                 
                booknew->authors=bgn->list->next->authors;
                 booknew->title=bgn->list->next->title;
             
                 findbytitle.length+=1;
               booknew->next=(Book*)malloc(sizeof(Book));
              booknew=booknew->next;
              a+=1;
            }
            bgn->list->next=bgn->list->next->next;
         
           	  
		}
        if(a==0){
            printf("\nError, no such title\n");
            findbytitle.list=NULL;
            return findbytitle;
        }
        booknew=NULL;
        findbytitle.list=start;
        bgn->list->next=liststart;
        return findbytitle;
}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author){
    Book* liststart=bgn->list->next;
    BookList findbyauthor;
    findbyauthor.list=NULL;
    findbyauthor.length=0; 
    Book* booknew=(Book*)malloc(sizeof(Book));
    Book* start=booknew;
    int a=0;
    for (int i=0; i< bgn->length; i++) {
			if (!strcmp(bgn->list->next->authors, author)){  
                   
               booknew->id=bgn->list->next->id;
               booknew->year=bgn->list->next->year;
               booknew->copies=bgn->list->next->copies;
                 
                booknew->authors=bgn->list->next->authors;
                 booknew->title=bgn->list->next->title;
             
                 findbyauthor.length+=1;
               booknew->next=(Book*)malloc(sizeof(Book));
               booknew=booknew->next;
               a+=1;
            }
            bgn->list->next=bgn->list->next->next;
         
           	  
		}
        if(a==0){
            printf("\nError, no such author\n");
            findbyauthor.list=NULL;
            return findbyauthor;
        }
        booknew=NULL;
        findbyauthor.list=start;
        bgn->list->next=liststart;
       
        return findbyauthor;
}


//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year){
    Book* liststart=bgn->list->next;
    BookList findbyyear;
    
    findbyyear.length=0; 
    Book* booknew=(Book*)malloc(sizeof(Book));
    Book* start=booknew;
    int a=0;
    for (int i=0; i< bgn->length; i++) {
			if(bgn->list->next->year==year){  
               booknew->id=bgn->list->next->id;
               booknew->year=bgn->list->next->year;
               booknew->copies=bgn->list->next->copies;
                booknew->authors=bgn->list->next->authors;
                 booknew->title=bgn->list->next->title;
               booknew->next=(Book*)malloc(sizeof(Book));
               booknew=booknew->next;
               findbyyear.length+=1;
              a+=1;
            }
            bgn->list->next=bgn->list->next->next;
                	  
		}
        if(a==0){
            printf("\nError, no such year\n");
            findbyyear.list=NULL;
            return findbyyear;
            
        }
        booknew=NULL;
        findbyyear.list=start;
        bgn->list->next=liststart;
       
        return findbyyear;
}

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




int showborrowed(User* logeduser){
Book* temp=logeduser->bookborrow->next;
if(temp==NULL){
    printf("\nYou have not borrowed any book\n");
    return 0;
}
 printf("\n%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR");
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
           printf("Error,id is out of range\n");
           
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
            printf("The book has been deleted\n");
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


