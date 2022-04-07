
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"login_register.h"
#include"structure.h"

#include"lo_st.h"
#include"myutility.h"

BookList* bgn;//the pointer to the booklist
Userlist *userbgn;//the pointer to the user list



//The function to register for users, return 1 if register successfully
//or the error codes otherwise.
int registerCLI(){
    User *userstart=userbgn->list->next;
    
    User * userstart2=userbgn->list;
   

   start:
    printf("\nPlease enter the user name(input quit to return),(Please less than 100 letters)\n");
    char name[1000];
    scanf("%[^\n]",name);
    getchar();

    //input "quit" so that to quit
   if(strcmp(name,"quit")==0){
       
        return 0;
    }
    //To judge if the name input was already used by others
    while(userbgn->list->next!=NULL){      
        if(strcmp(userbgn->list->next->name,name)==0){
            printf("Error,this name has already been used.");
            userbgn->list->next=userstart;
            goto start;
        }
        userbgn->list->next=userbgn->list->next->next;
       
    }
    
    printf("\nPlease enter the password(Please less than 100 letters)\n");
    char password[1000];
    scanf("%[^\n]",password);
     getchar();
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
   
    return 1;
}



//The function to Login for users, return the user struct pointer if it successfully logined
//or the error codes otherwise.
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

    //input "quit" so that to quit
    if(strcmp(name,"quit")==0){
       
        return temp;
    }
        getchar();

    //To judge if the name is existing
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
         getchar();
        return temp;
    }
        getchar();

    //To judge if the password is correct
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





//The function for librarian to login, return 1  if it successfully logined
//or the error codes otherwise.
int  librarianlogin(){
     int a=0;
    int b=0;
    int confirm=0;
    int confirm2=0;
    
    while(confirm==0){
     printf("Please enter the librarian account name(input quit to return)\n");
    char name[1000];
    scanf("%[^\n]",name);
     //input "quit" so that to quit
    if(strcmp(name,"quit")==0){
        getchar();
        return 0;
    }
        getchar();
    //To judge if the name input is "librarian"
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
         getchar();
          return 0;
    }
        getchar();
   //To judge if the librarian password is "librarian"
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

