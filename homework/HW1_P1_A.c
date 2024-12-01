#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int isOper(char c){
    if(c == '+' || c =='-' || c =='*' || c== '/'){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    char string[100000];
    char oper[100000];
    int push=0;
    scanf("%s" , string);
    int count = strlen(string);
    for(int i=0 ; i<count ; i++){
        if(isOper(string[i])){
            oper[push++] = string[i];
            
        }
        else{
            printf("%c" , string[i]);
            if(push >0){
                printf("%c" , oper[--push]);
            }
        }
    }
}