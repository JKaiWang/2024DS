#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define MAX 10
typedef struct Node {
    int key;
    int degree;
    int marked;
    struct Node *parent;
    struct Node *child[MAX];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Heap {
    Node *min;
    int nodeCount;
} Heap;

Heap* createHeap() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->min = NULL;
    heap->nodeCount = 0;
    return heap;
}

Node* createNode(int key) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->marked = 0;
    node->parent=NULL;
    for(int i=0 ; i<MAX ; i++){
        node->child[i] = NULL;
    }
    node->left = node->right = node;
    return node;
}

void linkTree(Node* y, Node* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    
    y->parent = x;

    int i;
    for (i = x->degree; i > 0 && x->child[i - 1]->key > y->key; i--) {
        x->child[i] = x->child[i - 1];
    }
    x->child[i] = y;
    x->degree++;

    y->left = y;
    y->right = y;
    y->marked = 0;
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
    heap->nodeCount++;
    return heap;
}

void consolidate(Heap* heap) {
    if (heap->min == NULL) return;

    int maxDegree = (int)(log(heap->nodeCount) / log(2)) + 1;
    Node** degreeTable = (Node**)calloc(maxDegree, sizeof(Node*));
    
    Node* current = heap->min;
    Node* start = current;
    int rootCount = 0;
    do {
        rootCount++;
        current = current->right;
    } while (current != start);
    
    Node** roots = (Node**)malloc(rootCount * sizeof(Node*));
    int idx = 0;
    current = heap->min;
    do {
        roots[idx++] = current;
        current = current->right;
    } while (current != start);

    // bubble sort
    for (int i = 0; i < rootCount - 1; i++) {
        for (int j = 0; j < rootCount - i - 1; j++) {
            if (roots[j]->key > roots[j + 1]->key) {
                Node* temp = roots[j];
                roots[j] = roots[j + 1];
                roots[j + 1] = temp;
            }
        }
    }

    // 重新整理root
    for (int i = 0; i < rootCount; i++) {
        Node* x = roots[i];
        int d = x->degree;

        while (degreeTable[d] != NULL) {
            Node* y = degreeTable[d];
            if (x->key > y->key) {
                Node* temp = x;
                x = y;
                y = temp;
            }
            
            linkTree(y, x);  
            degreeTable[d] = NULL;
            d++;
        }
        degreeTable[d] = x;
    }
    
    heap->min = NULL;
    for (int i = 0; i < maxDegree; i++) {
        if (degreeTable[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = degreeTable[i];
                degreeTable[i]->left = degreeTable[i];
                degreeTable[i]->right = degreeTable[i];
            } else {
                linkNodes(heap->min, degreeTable[i]);
                if (degreeTable[i]->key < heap->min->key) {
                    heap->min = degreeTable[i];
                }
            }
        }
    }
    
    free(roots);
    free(degreeTable);
}




Heap* extractMin(Heap *heap) {
    if (heap->min == NULL) return heap;

    Node *z = heap->min;

   
    for (int i = 0; i < z->degree; i++) {
        Node *child = z->child[i];
        if (child != NULL) {
            child->parent = NULL;
            linkNodes(heap->min, child);  
        }
    }

    // 從根列表移除 z
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        consolidate(heap);
    }

    heap->nodeCount--;
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
        for (int i = 0; i < current->degree; i++) {
            Node *result = search(current->child[i], key);
            if (result != NULL) {
                //printf("search : %d\n" , key);
                return result;
            }
        }
        current = current->right;
    } while (current != root);

    return NULL;
}

Heap* decreaseKey(Heap *heap, Node *node, int newKey) {

    node->key = node->key - newKey;
    Node *parent = node->parent;

    // Check for violation of heap property
    if (parent != NULL && node->key < parent->key) {
        Node *current = node;

        // Cascading cuts
        while (parent != NULL) {
            // Remove current from parent's child array
            for (int i = 0; i < parent->degree; i++) {
                if (parent->child[i] == current) {
                    // Shift children to remove current
                    for (int j = i; j < parent->degree - 1; j++) {
                        parent->child[j] = parent->child[j + 1];
                    }
                    parent->child[parent->degree - 1] = NULL;
                    parent->degree--;
                    break;
                }
            }

            // Add current to the root list
            linkNodes(heap->min, current);
            current->parent = NULL;
            current->marked = 0;

            if (parent->marked == 0) {
                parent->marked = 1;
                break;
            }
            current = parent;
            parent = parent->parent;
        }
    }
    // Update the heap's min pointer if necessary
    if (node->key < heap->min->key) {
        heap->min = node;
    }
    return heap;
}


Heap* deleteKey(Heap *heap, Node *node) {
    if (node == NULL) return heap;
    decreaseKey(heap, node, node->key);
    extractMin(heap);
    return heap;
}

void levelOrderTraversal(Node *root) {
    if (root == NULL) return;
    
    // 使用 queue 來實現層序遍歷
    Node *queue[100];
    int front = 0, rear = 0;
    
    // 將根節點加入 queue
    queue[rear++] = root;
    
    // 打印第一個節點（不帶空格）
    printf("%d", root->key);
    
    // 處理剩下的節點
    while (front < rear) {
        Node *current = queue[front++];
        
        // 按照 child array 的順序將子節點加入 queue
        for (int i = 0; i < current->degree; i++) {
            if (current->child[i] != NULL) {
                printf(" %d", current->child[i]->key);
                queue[rear++] = current->child[i];
            }
        }
    }
    printf("\n");
}

void printHeap(Heap *heap) {
    if (heap->min == NULL) return;
    
    Node *roots[100];  
    int rootCount = 0;
    
    Node *current = heap->min;
    do {
        roots[rootCount++] = current;
        current = current->right;
    } while (current != heap->min);
    
    for (int i = 0; i < rootCount - 1; i++) {
        for (int j = 0; j < rootCount - i - 1; j++) {
            if (roots[j]->degree > roots[j + 1]->degree) {
                Node *temp = roots[j];
                roots[j] = roots[j + 1];
                roots[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < rootCount; i++) {
        levelOrderTraversal(roots[i]);
    }
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
            //printHeap(heap);
        } 
        else if (strcmp(command, "decrease") == 0) {
            scanf("%d %d", &key, &value);
            Node *node = search(heap->min, key);
            heap = decreaseKey(heap, node, value);
            //printHeap(heap);
        } 
        else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            Node *node = search(heap->min, key);
            heap = deleteKey(heap, node);
            //printHeap(heap);
        } 
        else if (strcmp(command, "extract-min") == 0) {
            heap = extractMin(heap);
            //printHeap(heap);
        } 
        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    printHeap(heap);
    return 0;
}