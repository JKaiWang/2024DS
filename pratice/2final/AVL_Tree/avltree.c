#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    return root->height;
}

Node* create(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int updateHeight(Node* root){
    return  max(getHeight(root->left) , getHeight(root->right))+1;
}

Node* LLRotate(Node* root) { // Renamed from rightRotate
    Node* leftTree = root->left;
    Node* rightTree = leftTree->right;

    leftTree->right = root;
    root->left = rightTree;

    root->height = updateHeight(root);
    leftTree->height = updateHeight(leftTree);

    return leftTree;
}

Node* RRRotate(Node* root) { // Renamed from leftRotate
    Node* rightTree = root->right;
    Node* leftTree = rightTree->left;

    rightTree->left = root;
    root->right = leftTree;

    root->height =updateHeight(root);
    rightTree->height = updateHeight(rightTree);

    return rightTree;
}

int BalanceFactor(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create(data);
    }
    if (data > root->val) {
        root->right = insert(root->right, data);
    }
    if (data < root->val) {
        root->left = insert(root->left, data);
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int BF = BalanceFactor(root);

    // Perform rotations
    if (BF > 1 && data < root->left->val) {
        return LLRotate(root);
    }
    if (BF < -1 && data > root->right->val) {
        return RRRotate(root);
    }
    if (BF > 1 && data > root->left->val) {
        root->left = RRRotate(root->left);
        return LLRotate(root);
    }
    if (BF < -1 && data < root->right->val) {
        root->right = LLRotate(root->right);
        return RRRotate(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
Node* maxValueNode(Node* node){
    Node* current = node;
    while(current->right != NULL){
        current = current->right;
    }
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) { // No child case
                temp = root;
                root = NULL;
            } else { // One child case
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = maxValueNode(root->left);
            root->val = temp->val;
            root->left = deleteNode(root->left, temp->val);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = BalanceFactor(root);

    if (balance > 1 && BalanceFactor(root->left) >= 0) {
        return LLRotate(root);
    }
    if (balance > 1 && BalanceFactor(root->left) < 0) {
        root->left = RRRotate(root->left);
        return LLRotate(root);
    }
    if (balance < -1 && BalanceFactor(root->right) <= 0) {
        return RRRotate(root);
    }
    if (balance < -1 && BalanceFactor(root->right) > 0) {
        root->right = LLRotate(root->right);
        return RRRotate(root);
    }

    return root;
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

void preOrder(Node* root) { // Missing preOrder function
    if (root == NULL) return;
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

void levelOrder(Node* root) {
    if (root == NULL) return;

    Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->val);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

int main() {
    struct Node* root = NULL;

    /* Constructing tree */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = deleteNode(root , 20);

    /* The constructed AVL Tree would be:
            30
           /  \
         20    40
        /  \     \
       10   25    50
    */

    printf("Preorder traversal : \n");
    preOrder(root);
    printf("\n");
    levelOrder(root);


    return 0;
}
