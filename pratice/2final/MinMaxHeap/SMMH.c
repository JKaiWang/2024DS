#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_SIZE 100
typedef struct {
    int data[MAX_SIZE];
    int size;
} SMMH;


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void insert(SMMH* heap, int value) {
    if (heap->size == MAX_SIZE) {
        return;
    }

    int current = heap->size;
    heap->data[current] = value;
    heap->size++;

    //check sibling
    if(current%2==0 && heap->data[current] < heap->data[current-1]) {
        swap(&heap->data[current], &heap->data[current-1]);
        current--;
    }
    int done = 0;
    while(!done && current > 2) {
        int gp = ((current+1)/4) - 1;
        int lcp = 2*gp + 1;
        int rcp = 2*gp + 2;
        if(heap->data[current] < heap->data[lcp]) {
            swap(&heap->data[current], &heap->data[lcp]);
            current = lcp;
        }

        else if(heap->data[current] > heap->data[rcp]) {
            swap(&heap->data[current], &heap->data[rcp]);
            current = rcp;
        }
        else done = 1;   
    }
}

void deleteMin(SMMH* heap) {
    int current = 1;
    int last = heap->size - 1;
    if(last == 1){
        return;
    }

    if(last != 1) {
        swap(&heap->data[current], &heap->data[heap->size - 1]);
        heap->size--;

    }
    int done = 0;
    while(!done && (current <= (last-2)/2)) {
        int gp = ((current+1)/2) - 1;
        int gc1 = (4*(gp+1))-1;
        int gc2 = gc1 + 2;

        if(gc2 < last) {
            if(heap->data[gc1] > heap->data[gc2]) {
                gc1 = gc2;
            }
        }
        if(heap->data[gc1] < heap->data[current]){
           swap(&heap->data[current],&heap->data[gc1]);
           current = gc1;  
        }
        else{
            done = 1;
        }
        
    }

    if((heap->data[current] > heap->data[current+1]) && (current+1) < heap->size) {
        swap(&heap->data[current],&heap->data[current+1]); 
    }
        
}

void deleteMax(SMMH* heap) {
    int current = 2;
    int last = heap->size - 1;
    if(last == 2){
        return;
    }
    
    if(last != 2) {
        swap(&heap->data[current], &heap->data[heap->size - 1]);
        heap->size--;

    }
    int done = 0;
    while(!done && (current <= (last-1)/2)) {
        int gp = ((current)/2) - 1;
        int gc1 = (4*(gp+1));
        int gc2 = gc1 + 2;

        if(gc2 < last) {
            if(heap->data[gc1] < heap->data[gc2]) {
                    gc1 = gc2;
            }
        }
        if(heap->data[gc1] > heap->data[current]){
           swap(&heap->data[current],&heap->data[gc1]);
           current = gc1;  
        }
        else{
            done = 1;
        }
        
    }
    if(heap->data[current] < heap->data[current-1]) {
            swap(&heap->data[current],&heap->data[current-1]); 
    }
        
}



int main(){
    char input[100];
    SMMH* heap = (SMMH*)malloc(sizeof(SMMH));
    heap->size = 1;
    while(1){
        char command[100];
        int  value;
        scanf("%s" , command);
        if(strcmp("insert" , command) ==0){
            scanf("%d" , &value);
            insert(heap , value);
        }
        if(strcmp("delete-min" , command) == 0){
            deleteMin(heap);
        }
        if(strcmp("delete-max" , command) ==0){
            deleteMax(heap);
        }
        if(strcmp("exit" , command) ==0 ){
            break;
        }
    }

    printf("- ");

    for(int i = 1; i < heap->size;i++) {
        printf("%d ", heap->data[i]);
    }

    return 0;
}