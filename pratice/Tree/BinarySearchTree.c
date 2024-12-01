#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* leftNode;
    struct Node* rightNode;
};
typedef struct Node TreeNode;

void createNode(int data);
int isEmpty(TreeNode* root);
TreeNode* search(TreeNode* root ,int data);
TreeNode* delete(TreeNode* root , int data);
TreeNode* insert(TreeNode* root , int data);

TreeNode* newNode(int data){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->leftNode = NULL;
    node->rightNode = NULL;
    return node;
}

int isEmpty(TreeNode* root){
    return root == NULL;
}

TreeNode* search(TreeNode* root , int data){
    if(root->data == data) return root;
    else if(data < root->data){
        return search(root->leftNode , data);
    }
    else{
        return search(root->rightNode , data);
    }
}

TreeNode* insert(TreeNode* root , int data){
    if(root == NULL) return newNode(data);
    else if(data < root->leftNode){
        root->leftNode = insert(root->leftNode , data);
    }
    else if(data > root->data){
        root->rightNode = insert(root->rightNode , data);
    }
    return root;
}

TreeNode* delete(TreeNode* root , int  data){
    
}

int main(){

}