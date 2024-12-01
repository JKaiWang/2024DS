#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Create the tree struct 
struct Node {
    int data;
    struct Node *left, *right;
};
typedef struct Node* TreeNode;

struct Node* newNode(int data) {
    TreeNode node = (TreeNode)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Create a stack struct
struct Stack {
    int size;
    int top;
    struct Node** array;
};

struct Stack* createStack(int size) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (TreeNode*)malloc(size * sizeof(TreeNode)); 
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->size - 1; 
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, TreeNode node) {
    if (!isFull(stack)) {
        stack->array[++stack->top] = node;
    }
}

TreeNode pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return NULL;
}

TreeNode peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top];
    }
    return NULL;
}

// Binary tree iterative traversal contains postOrder, inOrder, and preOrder
// PostOrder
void postOrderIterative(TreeNode root) {
    if (root == NULL) return;
    struct Stack* stack = createStack(MAX);
    do {
        while (root != NULL) {
            if (root->right) push(stack, root->right);
            push(stack, root);
            root = root->left;
        }

        root = pop(stack);
        if (root->right && peek(stack) == root->right) {
            pop(stack);
            push(stack, root);
            root = root->right;
        } else {
            printf("%d ", root->data); 
            root = NULL;
        }
    } while (!isEmpty(stack));
}

// PreOrder
void preOrderIterative(TreeNode root) {
    if (root == NULL) return;
    struct Stack* stack = createStack(MAX);
    push(stack, root);

    while (!isEmpty(stack)) {
        TreeNode current = pop(stack);
        printf("%d ", current->data); 
        if (current->right != NULL) {
            push(stack, current->right);
        }
        if (current->left != NULL) {
            push(stack, current->left);
        }
    }

    free(stack->array);
    free(stack);
}

// InOrder
void inOrderIterative(TreeNode root) {
    if (root == NULL) return;
    struct Stack* stack = createStack(MAX);
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) { 
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("%d ", current->data); 
        current = current->right;
    }

    free(stack->array);
    free(stack);
}

// Free the binary tree nodes
void freeTree(TreeNode root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main Code
int main() {
    TreeNode root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    // Binary Tree
    //                   1
    //                 /   \
    //                2     3
    //               / \   / \
    //              4   5 6   7

    // Iterative version
    printf("Iterative traversal version\n");
    printf("PostOrder traversal of binary tree is: \n[");
    postOrderIterative(root);
    printf("]\n");

    printf("PreOrder traversal of binary tree is: \n[");
    preOrderIterative(root);
    printf("]\n");

    printf("InOrder traversal of binary tree is: \n[");
    inOrderIterative(root);
    printf("]\n");

    // Free allocated memory for the tree
    freeTree(root);

    return 0;
}
