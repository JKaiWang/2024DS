#include<stdio.h>
#include<stdlib.h>
#define MAX 10000
struct MinHeap{
    int *array;
    int capacity;
    int size;
};

typedef struct MinHeap MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* newHeap = (MinHeap*)malloc(sizeof(MinHeap));
    newHeap->capacity = capacity;
    newHeap->size = 0;
    newHeap->array = (int*)malloc(capacity*sizeof(int));
    return newHeap;
}

int parent(int i){
    return (i-1)/2;
}

int leftChild(int i){
    return (2*i +1 );
}

int rightChild(int i){
    return (2*i+2);
}

int getMin(MinHeap* heap){
    //return the minimum number of the Minheap
    return heap->array[0];
}

void swap(int* a , int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(MinHeap* heap , int index){
    int left = leftChild(index);
    int right = rightChild(index);
    int smallest = index;

    if(left< heap->size && heap->array[left] < heap->array[smallest]){
        smallest = left;
    }
    if(right < heap->size && heap->array[right] < heap->array[smallest]){
        smallest = right;
    }

    if(smallest != index){
        swap(&heap->array[smallest] , &heap->array[index]);
        heapifyDown(heap , smallest);
    }
    else{
        return;
    }
}

void heapifyUp(MinHeap* heap , int index){
    int par = parent(index);
    if(index> 0  && heap->array[index] < heap->array[par]){
        swap(&heap->array[index] , &heap->array[par]);
        heapifyUp(heap , par); 
    }
}

void free_minheap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->array);
    free(heap);
}

MinHeap* insert(MinHeap* heap , int value){
    if(heap->size == heap->capacity){
        printf("The heap is full ");
        return heap;
    }
    else{
        heap->array[heap->size] = value;
        heap->size ++;
        int current = heap->size -1;
        //this algorithm will first insert at the last position of the heap
        // and check whether it is bigger than it's parent
        //if it is bigger than it's parent than it is fine
        //however if it is smaller than it's parent you need to swap 
        while(current > 0 && heap->array[parent(current)] > heap->array[current]){
            //all you need to do is swap the element
            swap(&heap->array[parent(current)] , &heap->array[current]);
            current = parent(current);
        }
        return heap;

    }
}

MinHeap* delete(MinHeap* heap , int value){
    int index = -1;

    for(int i=0 ; i<heap->size ; i++){
        if(heap->array[i] == value){
            index = i;
            break;
        }
    }
    if(index == -1){
        return heap;
    }
    else{
        heap->array[index] = heap->array[heap->size -1];
        heap->size --;
        //調整heap 先往下調在往上調
        heapifyDown(heap , index);
        heapifyUp(heap , index);
    }
    return heap;

}

void printHeap(MinHeap* heap){
    for(int i=0 ; i<heap->size-1 ; i++){
        printf("%d " , heap->array[i]);
    }
    printf("%d" , heap->array[heap->size-1]);
    printf("\n");
}