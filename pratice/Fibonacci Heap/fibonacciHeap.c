#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int key;
    int degree;    
    struct Node* child;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int childCut;
}Node;
typedef struct FibHeap{
    Node* min ;
    int n;
} FibHeap;

FibHeap* createFibHeap(){
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

Node* createNode(int key){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->parent = NULL;
    newNode->degree =0;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    int childCut =0;
    return newNode;
}

void insert(FibHeap* heap, Node* node){
    if(heap->min ==NULL) heap->min = node;
    else{
        node->left = heap->min ; 
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if(node->key < heap->min->key){
            heap->min = node;
        }
    }
    heap->n++;
}

FibHeap* unionHeap(FibHeap* heap1 , FibHeap* heap2){
    FibHeap* h = createFibHeap();
    h->min = heap1->min;
    if(heap1->min != NULL && heap2->min != NULL){
        Node* heap1Right = heap1->min->left;
        Node* heap2Left = heap2->min->left;
        heap1->min->right = heap2->min;
        heap2->min->left = heap1->min;
        heap1Right->left = heap2Left;
        heap2Left ->right = heap1Right;

        if(heap2->min->key < heap1->min->key){
            h->min = heap2->min;
        }
    }

    h->n = heap1->n + heap2->n;
    free(heap1);
    free(heap2);
    return h;
}

Node* findMin(FibHeap* heap){
    return heap->min;
}

void delete(int key){

}

void decrease(int key  , int value){

}

void extractMin(){

}

int main(){
    char string[100];
    int key;
    int value;
    while(scanf("%s" , string) == 1){
        if(string[0] == 'i'){
            scanf("%d" , &key);
        }
        if(string[0] == 'd' && string[2] == 'l'){
        }
        if(string[0] == 'd' && string[2] == 'c'){

        }
        if(string[0] == 'e'  && string[2] == 't'){

        }
        if(string[0] == 'e' && string[2] == 'i'){

        }
    }
}