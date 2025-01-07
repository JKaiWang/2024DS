#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
int* bloomFilter;

int hash1(int key){
    return key % bucket;
}

int hash2(int key){
    return (key / bucket) % bucket;
}

void bloomInsert(int key ){
    bloomFilter[hash1(key)] = 1;
    bloomFilter[hash2(key)] = 1;
}

int bloomSearch(int key){
    return bloomFilter[hash1(key)] ==1 && bloomFilter[hash2(key)] ==1 ;
}



void insert(int key){
    int temp = key % bucket;
    for(int i=0 ; i<bucket ; i++){
        int current = (temp+i)%bucket;
        for(int j=0 ; j<slot ; j++){
            if(hashtable[current][j] == -1){
                hashtable[current][j] = key;
                bloomInsert(key);
                return;
            }
        }
    }
}

void rearrange_after_delete(int start_bucket, int start_slot) {
    int current_bucket = start_bucket;
    int current_slot = start_slot;

    while (true) {
        current_slot++;
        if (current_slot >= slot) {
            current_slot = 0;
            current_bucket = (current_bucket + 1) % bucket;
        }
        if (current_bucket == start_bucket && current_slot == start_slot) {
            break;
        }
        if (hashtable[current_bucket][current_slot] == -1) {
            break;
        }
        int key = hashtable[current_bucket][current_slot];
        int ideal_bucket = key % bucket;
        if (ideal_bucket != current_bucket) {
            hashtable[current_bucket][current_slot] = -1;
            insert(key);
        }
    }
}

void search(int key){
    int temp =key % bucket;
    for(int i=0; i < bucket-temp ; i++){
        int current = (temp+i)%bucket;
        for(int j=0 ; j< slot ; j++){
            if(hashtable[current][j] == key){
                printf("%d %d\n" , current , j);
                return;
            }
        }
    }
}

void delete(int key){
    int temp = key % bucket;
    for(int i=0 ; i<bucket-temp ; i++){
        int current = (temp + i) % bucket;
        for(int j=0 ; j<slot ; j++){
            if(hashtable[current][j] == key){
                hashtable[current][j] = -1;
                bloomInsert(key);
                rearrange_after_delete(current , j);
                return;
            }
        }
        temp +=1;
    }
}

int main(){
    char string[100];
    int data;
    
    //printf("yes");
    while(scanf("%s " , string)==1){
        if(string[0] == 'b'){
            scanf("%d" , &bucket);
            bloomFilter = (int*)malloc(bucket*sizeof(int));
            //printf("bucket\n");
        }
        if(string[0] == 's' && string[1] == 'l'){
            scanf("%d" , &slot);
            create();
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