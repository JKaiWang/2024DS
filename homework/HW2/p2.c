#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct Node {
    int key;
    int degree;
    int marked;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Heap {
    Node *min;
    int node_count;
} Heap;

Heap* createHeap() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->min = NULL;
    heap->node_count = 0;
    return heap;
}

Node* createNode(int key) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->marked = 0;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    return node;
}

void linkNodes(Node *a, Node *b) {
    b->left = a->left;
    b->right = a;
    a->left->right = b;
    a->left = b;
}

Heap* insert(Heap *heap, int key) {
    Node *newNode = createNode(key);
    if (heap->min == NULL) {
        heap->min = newNode;
    } else {
        linkNodes(heap->min, newNode);
        if (newNode->key < heap->min->key) {
            heap->min = newNode;
        }
    }
    heap->node_count++;
    return heap;
}

void consolidate(Heap *heap) {
    int max_degree = (int)(log2(heap->node_count)) + 1;
    Node *degree_table[max_degree];
    memset(degree_table, 0, sizeof(degree_table));

    Node *start = heap->min;
    Node *current = start;
    do {
        Node *x = current;
        current = current->right;
        int d = x->degree;
        while (degree_table[d] != NULL) {
            Node *y = degree_table[d];
            if (x->key > y->key) {
                Node *temp = x;
                x = y;
                y = temp;
            }
            if (y == start) {
                start = start->right;
            }
            if (y == current) {
                current = current->right;
            }
            // Link y under x
            y->left->right = y->right;
            y->right->left = y->left;
            y->parent = x;
            y->right = y->left = y;
            if (x->child == NULL) {
                x->child = y;
            } 
            else {
                linkNodes(x->child, y);
            }
            x->degree++;
            degree_table[d] = NULL;
            d++;
        }
        degree_table[d] = x;
    } while (current != start);

    heap->min = NULL;
    for (int i = 0; i < max_degree; i++) {
        if (degree_table[i]) {
            if (heap->min == NULL) {
                heap->min = degree_table[i];
            } else {
                linkNodes(heap->min, degree_table[i]);
                if (degree_table[i]->key < heap->min->key) {
                    heap->min = degree_table[i];
                }
            }
        }
    }
}

Heap* extractMin(Heap *heap) {
    if (heap->min == NULL) return heap;

    Node *z = heap->min;
    if (z->child != NULL) {
        Node *child = z->child;
        do {
            Node *next = child->right;
            linkNodes(heap->min, child);
            child->parent = NULL;
            child = next;
        } while (child != z->child);
    }

    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        consolidate(heap);
    }

    heap->node_count--;
    free(z);
    return heap;
}

Node* search(Node *root, int key) {
    if (root == NULL) return NULL;

    Node *current = root;
    do {
        if (current->key == key) {
            return current;
        }
        Node *result = search(current->child, key);
        if (result != NULL) return result;
        current = current->right;
    } while (current != root);

    return NULL;
}

Heap* decreaseKey(Heap *heap, Node *node, int value) {
    if (node == NULL || value >= node->key) return heap;

    node->key -= value;
    Node *parent = node->parent;

    if (parent != NULL && node->key < parent->key) {
        // Cut and cascading cuts
        Node *current = node;
        while (parent != NULL) {
            if (current->marked == 0) {
                current->marked = 1;
                break;
            }

            // Cut the current node
            if (current == parent->child) {
                parent->child = current->right == current ? NULL : current->right;
            }
            parent->degree--;
            current->left->right = current->right;
            current->right->left = current->left;
            linkNodes(heap->min, current);
            current->parent = NULL;
            current->marked = 0;

            current = parent;
            parent = parent->parent;
        }
    }

    if (node->key < heap->min->key) {
        heap->min = node;
    }

    return heap;
}

Heap* deleteKey(Heap *heap, Node *node) {
    if (node == NULL) return heap;

    decreaseKey(heap, node, node->key + INT_MAX);
    extractMin(heap);
    return heap;
}

void levelOrderTraversal(Node *root) {
    if (root == NULL) return;

    Node *queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    while (front != rear) {
        Node *current = queue[front++];
        printf("%d ", current->key);

        Node *child = current->child;
        if (child) {
            do {
                queue[rear++] = child;
                child = child->right;
            } while (child != current->child);
        }
    }
    printf("\n");
}

void printHeap(Heap *heap) {
    if (heap->min == NULL) return;

    Node *current = heap->min;
    do {
        levelOrderTraversal(current);
        current = current->right;
    } while (current != heap->min);
}

int main() {
    Heap *heap = createHeap();
    char command[20];
    int key, value;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            heap = insert(heap, key);
            printHeap(heap);
        } 
        else if (strcmp(command, "decrease") == 0) {
            scanf("%d %d", &key, &value);
            Node *node = search(heap->min, key);
            heap = decreaseKey(heap, node, value);
            printHeap(heap);
        } 
        else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            Node *node = search(heap->min, key);
            heap = deleteKey(heap, node);
            printHeap(heap);
        } 
        else if (strcmp(command, "extract-min") == 0) {
            heap = extractMin(heap);
            printHeap(heap);
        } 
        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    printHeap(heap);
    return 0;
}