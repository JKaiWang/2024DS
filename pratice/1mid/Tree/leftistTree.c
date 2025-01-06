#include<stdio.h>
#include<stdlib.h>
struct LeftistTree{
    int element;
    int count;
    struct LeftistTree *left , *right;
};
typedef struct LeftistTree Tree;

Tree* createNode(int key){
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->count = 0;
    newNode->element = key;
    newNode->left = newNode->right = NULL;
    return newNode;

}

void swap(Tree* node){
    Tree *temp = node->left;
    node->left = node->right;
    node->right = temp;
}
Tree* merge(Tree* node1 , Tree* node2){
    if(!node1) return node2;
    if(!node2) return node1;
    if(node1->element > node2->element){
        Tree *temp = node1;
        node1 = node2 ;
        node2 = temp;
    }
    node1->right = merge(node1->right , node2);
    if(!node1->left || node1->left->count < node1->right->count){
        swap(node1);
    }

    node1->count = node1->right ? node1->right->count+1: 0;

    return node1;

}

Tree* insert(Tree* root , int val){
    Tree* newNode = createNode(val);
    newNode->element = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return merge(root , newNode);
}

Tree* deleteMin(Tree* root){
    Tree* left = root->left;
    Tree* right = root->right;
    free(root);
    return merge(left , right);
}

void inorderTraversal(Tree* root){
    if(root){
        inorderTraversal(root->left);
        printf("%d ", root->element);
        inorderTraversal(root->right);
    }
}

void freeTree(Tree* root){
    if(root){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main(){
    Tree *root = NULL;

    root = insert(root ,10);
    root = insert(root ,20);
    root = insert(root , 5);
    root = insert(root , 15);

    printf("Inorder Traversal:");
    inorderTraversal(root);
    printf("\n");

    root = deleteMin(root);
    printf("After deleting");
    inorderTraversal(root);
    printf("\n");

    freeTree(root);
    return 0;
}