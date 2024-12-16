#include<stdio.h>
#include<stdlib.h>


int** hashtable;
int bucket;
int slot;

void create(){
    hashtable = (int**)malloc(bucket*sizeof(int*));
    for(int i=0 ; i< bucket ; i++){
        hashtable[i] = (int*)malloc(slot*sizeof(int));
        for(int j=0 ; j< slot ; j++){
            hashtable[i][j] = -1;
        }
    }   
}

void insert(int key){
    int temp = key % bucket;
    for(int i=0 ; i<bucket ; i++){
        int current = (temp+i)%bucket;
        for(int i=0 ; i<slot ; i++){
            if(hashtable[current][i] == -1){
                hashtable[current][i] = key;
                return;
            }
        }
    }
}

void search(int key){
    int temp =key % bucket;
    for(int i=0; i < bucket-temp ; i++){
        int current = (temp+i)%bucket;
        for(int i=0 ; i< slot ; i++){
            if(hashtable[current][i] == key){
                printf("%d %d\n" , current , i);
                return;
            }
        }
    }
}

void delete(int key){
    int temp = key % bucket;
    for(int i=0 ; i<bucket-temp ; i++){
        int current = (temp + i) % bucket;
        for(int i=0 ; i<slot ; i++){
            if(hashtable[current][i] == key){
                hashtable[current][i] = -1;
                return;
            }
        }
        temp +=1;
    }
ㄨㄨ

int main(){
    char string[100];
    int data;
    
    //printf("yes");
    while(scanf("%s " , string)==1){
        if(string[0] == 'b'){
            scanf("%d" , &bucket);
            //printf("bucket\n");
        }
        if(string[0] == 's' && string[1] == 'l'){
            scanf("%d" , &slot);
            create();
            //printf("slot\n");
        }
        if(string[0] == 'i'){
            scanf("%d" , &data);
            insert(data);
            //printf("insert %d \n" , data);
        }
        if(string[0] == 's' && string[1] == 'e'){
            scanf("%d" , &data);
            search(data);
            //printf("search\n");
            
        }
        if(string[0] == 'd'){
            scanf("%d" , &data);
            delete(data);
            //printf("delete\n");
        }
        if(string[0] == 'e'){
            break;
        }
    }
}