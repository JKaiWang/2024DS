#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

static int DEBUG =0;

int pow(int x, int y){
    int result = 1;
    while(y--){
        result *= x;
    }
    return result;
}

typedef struct Node{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int key;
    char color;
}Node;


Node* create(int key , char color){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = color;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

typedef struct RBtree{
    Node* root;
    Node* nil;
    int size;
    Node *(*search)(struct RBtree *T , const int key);
    int (*insert)(struct RBtree *T , const int key);
    int (*delete)(struct RBtree *T , const int key);
}RBtree;

void printRBtree(RBtree *T);
Node* search(RBtree *T , const int key);
int insert(RBtree *T , const int key);
void rightRotate(RBtree *T , Node* cur);
void leftRotate(RBtree *T , Node* cur);
void insertFixUp(RBtree* , Node* cur);
int delete(RBtree* T , const int key);
void deleteFixUp(RBtree *T , Node* cur);
Node* successor(RBtree *T , Node* cur);
RBtree* createRB();

typedef struct LinkNode{
    struct LinkNode *next;
    Node* data;
}LinkNode;

typedef struct LinkList{
    LinkNode* head; 
    int size;
}LinkList;

LinkList *createLinkList(){
    LinkList *newList = (LinkList*)malloc(sizeof(LinkList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

void pushBack(LinkList **list , Node* data){
    LinkNode* newNode = (LinkNode*)malloc(sizeof(LinkNode));
    newNode->data = data;
    newNode->next = NULL;
    if((*list)->head== NULL){
        (*list)->head = newNode;
    }
    else{
        LinkNode* cur = (*list)->head;
        (*list)->head = (*list)->head->next;
        Node* data = cur->data;
        free(cur);
        (*list)->size -- ;
        return data;
    }
}