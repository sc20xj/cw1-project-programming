
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"login_register.h"
#include"bookmanagement.h"

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
    new->namesize=strlen(name)+1;
    new->passwordsize=strlen(password)+1;
    new->name=(char *)malloc((new->namesize)*sizeof(char));
    new->password=(char *)malloc((new->passwordsize)*sizeof(char));
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
    printf("\nSuccessfully registered\n");
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

int  librarianlogin(){
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
   printf("\nSuccessfully logined\n");
   return 1;
}

