
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"projectheader.h"
#include"lo_st.h"
#include"myutility.h"
#include"librarian.h"

BookList* bgn;



int add_book(Book book){
   
     Book* liststart=bgn->list->next;
     Book* aimbook=(Book*)malloc(sizeof(Book));
     int a=0;
    
    while(bgn->list->next!=NULL){
        if(strcmp(bgn->list->next->title,book.title)==0||bgn->list->next->id==book.id){
            a=1;
            break;
        }
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next=liststart;
    if(a==1){
        bgn->list->next->copies+=1;
        bgn->list->next=liststart;
    }
    else{
    while(bgn->list->next->next!=NULL){
        bgn->list->next=bgn->list->next->next;
    }
    bgn->list->next->next=aimbook;
    aimbook->id=book.id;
    aimbook->history=book.history;
    aimbook->copies=book.copies;
    aimbook->year=book.year;
    aimbook->authors=book.authors;
    aimbook->title=book.title;
    bgn->list->next=liststart;
    bgn->length+=1;
    aimbook->next=NULL;
    }
    return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book){
    
     if(bgn->list->next==NULL){
        printf("\nThis list is NULL\n");
        return -1;
     }
   
     Book* liststart=bgn->list->next;
    while(bgn->list->next->id!=book.id){
        bgn->list->next=bgn->list->next->next;
        if(bgn->list->next==NULL){
             printf("\nThere is no assigned book in the list\n");
             bgn->list->next=liststart;
             return -1;
        }
    }
  
    if(bgn->list->next->id==book.id){
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
     


void showhistory(){
     Book* bookstart=bgn->list->next;
     
      printf("\n%-10s\t%-10s\n","Title","Name");   
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