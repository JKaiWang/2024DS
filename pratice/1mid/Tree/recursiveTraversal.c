#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* leftNode;
    struct Node* rightNode;
};
typedef struct Node node;

node* createNode(int data){
    struct Node *n;
    n = (node*)malloc(sizeof(node));
    n->data = data;
    n->leftNode = NULL;
    n->rightNode = NULL;
    return n;
}

void preOrder(node* root){
    if(root == NULL) return;
    else{
        printf("%d" , root->data);
        preOrder(root->leftNode);
        preOrder(root->rightNode);
    }
}

void postOrder(node* root){
    if(root == NULL){
        return;
    }
    else{
        postOrder(root->leftNode);
        postOrder(root->rightNode);
        printf("%d" , root->data);
    }
}

void inOrder(node* root){
    if(root == NULL){
        return;
    }
    else{
        inOrder(root->leftNode);
        printf("%d" , root->data);
        inOrder(root->rightNode);
    }
}

int main(){
    node *p = createNode(1);
    node *p1 = createNode(2);
    node *p2 = createNode(3);
    node *p3 = createNode(4);
    node *p4 = createNode(5);
    node *p5 = createNode(6);
    node *p6 = createNode(7);

    p->leftNode = p1;
    p->rightNode = p2;
    p1->leftNode = p3;
    p1->rightNode = p4;
    p2->leftNode = p5;
    p2->rightNode = p6;

    //           1
    //          /  \ 
    //        2      3
    //       / \    /  \
    //      4   5  6    7

    printf("preOrder: \n");
    preOrder(p);
    printf("\npost order: \n");
    postOrder(p);
    printf("\ninOrder: \n");
    inOrder(p);
    return 0;
}