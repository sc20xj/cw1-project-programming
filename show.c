
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"bookmanagement.h"
#include"lo_st.h"
#include"myutility.h"
#include"show.h"

BookList* bgn;



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



void display(){
    Book* liststart=bgn->list->next;
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "ID", "AUTHOR", "TITLE", "YEAR","COPIES");
    while(bgn->list->next!=NULL){
        printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10d\n",bgn->list->next->id,bgn->list->next->authors,bgn->list->next->title,bgn->list->next->year,bgn->list->next->copies);
        bgn->list->next=bgn->list->next->next;
         
    }
   
    bgn->list->next=liststart;
   
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



void showborrowing(){
    Book* bookstart=bgn->list->next;
    User* userstart=userbgn->list->next;
     printf("\n%-10s\t%-10s\n","Title","Name"); 
     while (bgn->list->next!=NULL){
          printf("%-10s\t",bgn->list->next->title);   
         if(bgn->list->next->borrowing>0){
            while(userbgn->list->next!=NULL){
                Book* temp=userbgn->list->next->bookborrow->next;
                while(userbgn->list->next->bookborrow->next!=NULL){
                if(userbgn->list->next->bookborrow->next->id==bgn->list->next->id){
                     printf("%-10s\t",userbgn->list->next->name);
                    
                }
                userbgn->list->next->bookborrow->next=userbgn->list->next->bookborrow->next->next;
                }
                userbgn->list->next->bookborrow->next=temp;
                userbgn->list->next=userbgn->list->next->next;
            }
         }
         userbgn->list->next=userstart;
         bgn->list->next=bgn->list->next->next;
          printf("\n");
     }
     bgn->list->next=bookstart;
   
     
}




