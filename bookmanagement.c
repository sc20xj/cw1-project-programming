#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"myutility.h"
#include"bookmanagement.h"
#include"show.h"
#include"lo_st.h"
#include"structure.h"
BookList* bgn;//the pointer to the booklist
Userlist *userbgn;//the pointer to the userlist

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book){
   
     Book* liststart=bgn->list->next;//save the head pointer of the book link list
    
     Book* aimbook=(Book*)malloc(sizeof(Book));//allocate the address of the newly added book
     aimbook->history=(User*)malloc(sizeof(User));//allocate the address of the history of newly added book
      aimbook->history->next=NULL;

      //if there is no book in the booklist
      if(bgn->list->next!=NULL){
     int a=0;
    
    while(bgn->list->next!=NULL){
        if(strcmp(bgn->list->next->title,book.title)==0){
            a=1;
            break;//if the added book's title is the same as previous one,out of the loop
        }
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next=liststart;
    if(a==1){
        //copies plus one if the added book's title is the same as previous one
        bgn->list->next->copies+=1;
        bgn->list->next=liststart;
        printf("\nThe title is same with the former one,copies has been added 1\n");
    }
    else{
     //the added book is new,set the information of the new book
    while(bgn->list->next->next!=NULL){
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next->next=aimbook;
    aimbook->id=bgn->list->next->id+1;
    aimbook->borrowed=0;
    aimbook->copies=book.copies;
    aimbook->year=book.year;
    aimbook->titlesize=strlen(book.title)+1;
    aimbook->authorsize=strlen(book.authors)+1;
    aimbook->authors=(char*)malloc(sizeof(char)*(aimbook->authorsize));
    aimbook->title=(char*)malloc(sizeof(char)*(aimbook->titlesize));
    strcpy(aimbook->authors,book.authors);
    strcpy(aimbook->title,book.title);
  
    aimbook->borrowing=0;
    bgn->list->next=liststart;
    bgn->length+=1;
    aimbook->next=NULL;
    }
     printf("\nSuccessfully added\n");
    return 0;
     }

   //set the book information of the situation that the booklist is empty
     else{  
    bgn->list->next=aimbook;
    aimbook->titlesize=strlen(book.title)+1;
    aimbook->authorsize=strlen(book.authors)+1;
    aimbook->authors=(char*)malloc(sizeof(char)*(aimbook->authorsize));
    aimbook->title=(char*)malloc(sizeof(char)*(aimbook->titlesize));
    strcpy(aimbook->authors,book.authors);
    strcpy(aimbook->title,book.title);
    aimbook->id=1;
    aimbook->borrowed=0;
    aimbook->copies=book.copies;
    aimbook->year=book.year;
    aimbook->borrowing=0;
    bgn->length+=1;
    aimbook->next=NULL;
    printf("\nSuccessfully added\n");
    return 0;
     }
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book){
    
    //To judge if the booklist is empty
     if(bgn->list->next==NULL){
        printf("\nThis list is NULL\n");
        return -1;
     }

   
     Book* liststart=bgn->list->next;//save the head pointer of the book link list
    
    //running through the list to find if there is the assigned book
    while(bgn->list->next->id!=book.id){
        bgn->list->next=bgn->list->next->next;
        //if there is no assigned book,return
        if(bgn->list->next==NULL){
             printf("\nThere is no assigned book in the list\n");
             bgn->list->next=liststart;
             return -1;
        }
    }
    //if someone is borrowing this book,it can not be removed
    if(bgn->list->next->id==book.id){
        if(bgn->list->next->borrowing>0){
            printf("\nError,someone is borrowing this book\n");
            bgn->list->next=liststart;
            return 0;
        }

        //remove the book and reconnect the linklist
        User* usertemp=userbgn->list->next;
        Book* temp2=bgn->list->next->next;
      
        while(bgn->list->next->next!=NULL){
            
            while(userbgn->list->next!=NULL){
                 Book* booktemp=userbgn->list->next->bookborrow->next;
                while(userbgn->list->next->bookborrow->next!=NULL){
                    if(userbgn->list->next->bookborrow->next->id== bgn->list->next->next->id){
                        userbgn->list->next->bookborrow->next->id-=1;
                    }
                    userbgn->list->next->bookborrow->next= userbgn->list->next->bookborrow->next->next;
                }
                userbgn->list->next->bookborrow->next=booktemp;
                 userbgn->list->next=userbgn->list->next->next;
            }
            userbgn->list->next=usertemp;
              bgn->list->next->next->id-=1;
              bgn->list->next->next= bgn->list->next->next->next;
        }
         bgn->list->next->next=temp2;
        

        if(bgn->list->next==liststart){
            bgn->list->next=liststart->next;
            bgn->length-=1;
            free(liststart->history);
            free(liststart);
        }
        else{
          
            Book* temp=bgn->list->next;
            bgn->list->next=liststart;
            while(bgn->list->next->next!=temp){
                bgn->list->next=bgn->list->next->next;
            }
            bgn->list->next->next=temp->next;
            bgn->length-=1;
            bgn->list->next=liststart;
        }
        return 0;
        
    }
    else{
        printf("There is no assigned book in the list");
        return -1;
    }
    
}
     

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
    //ruuning through the booklist to find if there is assigned book
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

    //ruuning through the booklist to find if there is assigned book
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

    //ruuning through the booklist to find if there is assigned book
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





//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
int Borrowbooks(User* logeduser){
   int a=listavailablebook();
if(a==0){
return 0;
}
   printf("\nwhich do you want to borrow: ");
  int id;
  //get the choice of users
  id=optionChoice();

  //To judge if the choice is valid
   if(id==-1){
           printf("\n You should input a digit \n");
   }
   else{
       
   Book* bookstart=bgn->list->next;
  
  //running through the list to find if there is assigned book existing
   while(bgn->list->next->id!=id){
       
       bgn->list->next=bgn->list->next->next;
       
       if(bgn->list->next==NULL){
           bgn->list->next=bookstart;
           printf("Error,id is out of range\n");
           return 0;
       }
   } 

   //if there is assigned book, set the relative information
   //includeing the borrowed history and user borrowing list.
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
    logeduser->bookborrow->next->titlesize=bgn->list->next->titlesize;
     logeduser->bookborrow->next->authorsize=bgn->list->next->authorsize;
   logeduser->bookborrow->next->next=NULL;
   logeduser->bookborrow=temp2;
   logeduser->number+=1;
   User *temp=bgn->list->next->history;
   while(bgn->list->next->history->next!=NULL){
      
        bgn->list->next->history=bgn->list->next->history->next;
   }
   
   bgn->list->next->history->next=(User*)malloc(sizeof(User));
   bgn->list->next->borrowed+=1;
 bgn->list->next->history->next->name=logeduser->name;
 bgn->list->next->history->next->namesize=logeduser->namesize;
  
 bgn->list->next->history->next->next=NULL;
 bgn->list->next->borrowing+=1;
  bgn->list->next->history=temp;
   bgn->list->next=bookstart;
    printf("\nsuccessfully borrowed the book\n");
    
   }
return 1;
}



//For users to return books to the library
//return 1 if the book is returned successfully, or the error codes otherwise.
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

   //get the users choice
   id=optionChoice();

   //To judge if the choice is valid
   if(id==-1){
       printf("\n You should input a digit \n");     
   }

   //To judge if the assigned book is existing
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
    }

    //set the relative information and the relative list structure
    bgn->list->next->borrowing-=1;
     
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
    printf("\nReturn successfully\n");
    }
    else{
        printf("You have not borrowed any books");
    }

   }
return 1;
}



