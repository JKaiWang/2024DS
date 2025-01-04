#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHILD 100

typedef struct Node {
    int key;
    int degree;
    int flag;
    struct Node *parent;
    struct Node *child; // Points to one of the children (doubly circular linked list)
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int key) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->flag = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    return newNode;
}

void insertNode(Node **minNode, Node **newNode) {
    if (*minNode == NULL) {
        *minNode = *newNode;
    } else {
        (*newNode)->right = (*minNode)->right;
        (*newNode)->left = *minNode;
        (*minNode)->right->left = *newNode;
        (*minNode)->right = *newNode;
        if ((*newNode)->key < (*minNode)->key) {
            *minNode = *newNode;
        }
    }
}

Node *searchNode(Node *minNode, int key) {
    if (minNode == NULL) return NULL;
    Node *current = minNode;
    do {
        if (current->key == key) return current;
        if (current->child != NULL) {
            Node *found = searchNode(current->child, key);
            if (found != NULL) return found;
        }
        current = current->right;
    } while (current != minNode);
    return NULL;
}

void merge(Node **small, Node **big) {
    (*big)->parent = *small;
    if ((*small)->child == NULL) {
        (*small)->child = *big;
        (*big)->left = *big;
        (*big)->right = *big;
    } else {
        Node *child = (*small)->child;
        (*big)->right = child->right;
        (*big)->left = child;
        child->right->left = *big;
        child->right = *big;
    }
    (*small)->degree++;
}

void consolidate(Node **minNode) {
    if (*minNode == NULL) return;
    Node *degreeTable[MAX_CHILD] = {NULL};
    Node *current = *minNode;
    Node *start = current;
    do {
        Node *x = current;
        current = current->right;
        int d = x->degree;
        while (degreeTable[d] != NULL) {
            Node *y = degreeTable[d];
            if (x->key > y->key) {
                Node *temp = x;
                x = y;
                y = temp;
            }
            merge(&x, &y);
            degreeTable[d] = NULL;
            d++;
        }
        degreeTable[d] = x;
    } while (current != start);

    *minNode = NULL;
    for (int i = 0; i < MAX_CHILD; i++) {
        if (degreeTable[i] != NULL) {
            insertNode(minNode, &degreeTable[i]);
        }
    }
}

void deleteNode(Node **deleteTarget, Node **minNode) {
    if (*deleteTarget == NULL) return;
    if (*deleteTarget == *minNode) {
        *minNode = (*deleteTarget)->right;
    }
    Node *child = (*deleteTarget)->child;
    while (child != NULL) {
        Node *next = child->right;
        child->parent = NULL;
        insertNode(minNode, &child);
        if (next == child) break;
        child = next;
    }
    (*deleteTarget)->left->right = (*deleteTarget)->right;
    (*deleteTarget)->right->left = (*deleteTarget)->left;
    free(*deleteTarget);
    *deleteTarget = NULL;
    if (*minNode != NULL) {
        consolidate(minNode);
    }
}

void printHeap(Node *minNode) {
    if (minNode == NULL) return;
    Node *current = minNode;
    do {
        printf("%d ", current->key);
        Node *child = current->child;
        if (child != NULL) {
            printf("(Child: ");
            Node *childStart = child;
            do {
                printf("%d ", child->key);
                child = child->right;
            } while (child != childStart);
            printf(") ");
        }
        current = current->right;
    } while (current != minNode);
    printf("\n");
}

int main() {
    char input[20];
    int inputNum;
    Node *minNode = NULL;
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            printHeap(minNode);
            return 0;
        } else if (strcmp(input, "insert") == 0) {
            scanf("%d", &inputNum);
            Node *newNode = createNode(inputNum);
            insertNode(&minNode, &newNode);
        } else if (strcmp(input, "delete") == 0) {
            scanf("%d", &inputNum);
            Node *deleteTarget = searchNode(minNode, inputNum);
            deleteNode(&deleteTarget, &minNode);
        } else if (strcmp(input, "decrease") == 0) {
            int decreaseAmount;
            scanf("%d %d", &inputNum, &decreaseAmount);
            Node *targetNode = searchNode(minNode, inputNum);
            if (targetNode != NULL) {
                targetNode->key -= decreaseAmount;
                if (targetNode->key < minNode->key) {
                    minNode = targetNode;
                }
            }
        } else if (strcmp(input, "extract-min") == 0) {
            if (minNode != NULL) {
                Node *extractNode = minNode;
                deleteNode(&extractNode, &minNode);
            }
        }
    }
}
