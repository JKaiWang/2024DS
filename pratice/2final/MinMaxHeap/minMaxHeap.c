#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 100

typedef struct Node{
    int data[MAX];
    int size;
}Node;

int isMinLevel(int index){
    return ((int)log2(index+1)) %2 ==0;
}

void swap(int *a , int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    if(i>0){
        return (i-1)/2;
    }
    return -1;
}
int left(int i){
    return 2*i+1;
}
int right(int i){
    return 2*i+2;
}

void pushDown(Node* heap , int index){
    int size = heap->size;
    int leftC = left(index);
    int rightC = right(index);

    if(isMinLevel(index)){
        int smallest = index;
        if(leftC < size && heap->data[leftC] < heap->data[smallest]) smallest = leftC;
        if(rightC < size && heap->data[rightC] < heap->data[smallest])smallest = rightC;
        if(smallest != index){
            swap(&heap->data[index] , &heap->data[smallest]);
            pushDown(heap, smallest);
        }
    }
    else{
        int largest = index;
        if(leftC < size && heap->data[leftC] > heap->data[largest]) largest = leftC;
        if(rightC < size && heap->data[rightC] > heap->data[largest]) largest = rightC;
        if(largest != index){
            swap(&heap->data[largest] , &heap->data[index]);
            pushDown(heap , largest);
        }
    }
}

void pushUp(Node* heap , int index , int check){
    //printf("index: %d\n" , index);
    if(index <=0) return;
    int parentIndex = parent(index);
    int grand = parent(parentIndex);
    if(isMinLevel(index)){ /// min level
        if(parentIndex >=0 && heap->data[index] > heap->data[parentIndex] && check >=0){
            swap(&heap->data[index] , &heap->data[parentIndex]);
            check = 1;
            pushUp(heap , parentIndex , check);
            
        }
        else if(grand >=0 && heap->data[index] < heap->data[grand] &&check <=0){
            swap(&heap->data[index] , &heap->data[grand]);
            check = -1;
            pushUp(heap , grand , check);
        }
    }
    else{
        if(parentIndex >=0 && heap->data[index] < heap->data[parentIndex] && check >=0){
            swap(&heap->data[index] , &heap->data[parentIndex]);
            check = 1;
            pushUp(heap , parentIndex , check);
            
        }
        else if(grand >=0 && heap->data[index] > heap->data[grand] &&check <=0){
            swap(&heap->data[index] , &heap->data[grand]);
            check = -1;
            pushUp(heap , grand , check);
        }
    }
}
void display(Node *heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void insert(Node* heap , int value){
    if(heap->size >= MAX){
        return;
    }
    heap->data[heap->size] = value;
    heap->size +=1;
    pushUp(heap , heap->size-1 ,0);
}

int extractMin(Node* heap){
    if(heap->size == 0 ){
        return -1;
    }
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    pushDown(heap, 0);  // Only pushDown is needed
    return min;
}

int extractMax(Node* heap) {
    if (heap->size == 0) {
        return -1;
    }
    int maxIndex;
    if (heap->size == 1) {
        maxIndex = 0;
    } else if (heap->size == 2) {
        maxIndex = 1; // Only one child exists
    } else {
        maxIndex = heap->data[1] > heap->data[2] ? 1 : 2;
    }
    int maxValue = heap->data[maxIndex];
    heap->data[maxIndex] = heap->data[heap->size - 1];
    heap->size--;
    if (maxIndex < heap->size) {
        pushDown(heap, maxIndex);
    }
    return maxValue;
}




int main() {
    Node heap = {.size = 0};

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    insert(&heap, 30);
    insert(&heap, 3);
    //insert(&heap ,11);

    display(&heap);

    printf("Extracted Min: %d\n", extractMin(&heap));
    display(&heap);

    printf("Extracted Max: %d\n", extractMax(&heap));
    display(&heap);

    return 0;
}