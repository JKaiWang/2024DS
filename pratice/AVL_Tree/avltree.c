#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int val;
    struct Node* left;
    struct Node* right;
    int height;
}Node;

int max(int a , int b){
    return a>b ? a:b;
}

int getHeight(Node* root){
    if(root == NULL) return 0;
    return root->height;
}

Node* create(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

Node* rightRotate(Node* root){
    Node* leftTree = root->left;
    Node* rightTree = root->right;
    leftTree->right = root;
    root->left = rightTree;
    root->height = max(getHeight(root->left) , getHeight(root->right))+1;
    leftTree->height = max(getHeight(leftTree->left) , getHeight(leftTree->right))+1;
    return leftTree;
}

Node* leftRotate(Node* root){
    Node* leftTree = root->left;
    Node* rightTree = root->right;
    rightTree->left = root;
    root->right = leftTree;

    root->height = max(getHeight(root->left) , getHeight(root->right))+1;
    rightTree->height = mac(getHeight(rightTree->left) , getHeight(rightTree->right))+1;
    return rightTree;
}

int BalanceFactor(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->left->height - root->right->height;
}

Node* insert(Node* root , int data){
    if(root == NULL){
        return(create(data));
    }
    if(data > root->val){
        root->right = insert(root->right , data);
    }
    if(data < root->val){
        root->left = insert(root->left , data);
    }
    root->height = max(getHeight(root->left)  , getHeight(root->left))+1;
    int BF = BalanceFactor(root);
    
    if(BF > 1 && data < root->left->val){
        return rightRotate(root);
    } 
    if(BF < -1 && data > root->right->val){
        return leftRotate(root);
    }
    if(BF > 1 && data > root->left->val){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(BF < -1 && data < root->right->val){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inOrder(Node* root){
    inOrder(root->left);
    printf("%d " , root->val );
    inOrder(root->right);
}

int main()
{
  struct Node *root = NULL;

  /* Constructing tree given in the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

    printf("Preorder traversal : \n");
    preOrder(root);

    return 0;
}