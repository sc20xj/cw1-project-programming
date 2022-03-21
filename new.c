#include<stdio.h>
#include <string.h>
//可以退出的头文件
#include <stdlib.h>
//结构体的长度
#define DATALEN 15
//函数声明
//定义结构数组
struct wordUnit{
    int id;         //id
    char word[10];    //词语
    char depId[10];   //依存词语的id
    char pos[10];     //词性
    char depRel[10];  //依存目标的关系
};
int main(){
    FILE *data;//要读取的文件指针
    int i=0;//结构题数组移动
    struct wordUnit words[DATALEN];
    if((data=fopen("data3.txt","r"))==NULL){
        printf("Can not open file\n");
        return 0;
    }
    while(!feof(data)){
        //原txt文档的数据之间是以空格隔开的
        fscanf(data,"%d %s %s %s %s\n",&words[i].id,words[i].word,words[i].depId,words[i].pos,words[i].depRel);
        i++;
    }
    fclose(data);
    for(int j=0;j<i;j++){
        printf("%d %s %s %s %s\n",words[j].id,words[j].word,words[j].depId,words[j].pos,words[j].depRel);
    }
    return 0;
}
