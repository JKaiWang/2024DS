#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX 100

typedef struct{
    int data[MAX];
    int size;
}DEPQ;

void initDEPQ(DEPQ *depq){
    depq->size=0;
}

void swap(int* a , int* b){
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void heapifyUpMin(int *heap , int index){
    while(index > 0 && heap[index] < heap[(index-1)/2]){
        swap(&heap[index] , &heap[(index-1)/2]);
        index = (index-1)/2;
    }
}