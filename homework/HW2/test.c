#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// 定義 Fibonacci Heap 節點結構
typedef struct Node {
    int key;
    int degree;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
    int childCut; // 用於標記是否需要進一步的級聯切割
} Node;

// 定義 Fibonacci Heap 結構
typedef struct Heap {
    Node *min; // 指向最小鍵值節點
    int nodeCount; // 節點總數
} Heap;

// 創建新節點
Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->childCut = 0;
    return node;
}

// 創建 Fibonacci Heap
Heap *createHeap() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->min = NULL;
    heap->nodeCount = 0;
    return heap;
}

// 將節點插入雙向環形鏈表
void linkNodes(Node *a, Node *b) {
    a->right->left = b->left;
    b->left->right = a->right;
    a->right = b;
    b->left = a;
}

// 將節點插入 Fibonacci Heap 的根列表
void insertNode(Heap *heap, int key) {
    Node *node = createNode(key);
    if (!heap->min) {
        heap->min = node;
    } else {
        linkNodes(heap->min, node);
        if (node->key < heap->min->key) {
            heap->min = node; // 更新最小值
        }
    }
    heap->nodeCount++;
    //printf("Inserted %d. Current min: %d\n", key, heap->min->key); // Debug
}


// 合併兩顆相同度數的樹
void mergeTrees(Node *a, Node *b) {
    if (a->key > b->key) {
        Node *temp = a;
        a = b;
        b = temp;
    }
    // 將 b 成為 a 的子節點
    b->left->right = b->right;
    b->right->left = b->left;
    b->parent = a;
    if (!a->child) {
        a->child = b;
        b->left = b->right = b;
    } else {
        linkNodes(a->child, b);
    }
    a->degree++;
    b->childCut = 0;
}

// Consolidate操作: 合併具有相同度數的樹
void consolidate(Heap *heap) {
    int maxDegree = (int)(log2(heap->nodeCount)) + 1;
    Node **degreeTable = (Node **)calloc(maxDegree, sizeof(Node *));
    Node *current = heap->min;
    Node *start = current;

    do {
        Node *x = current;
        current = current->right;
        while (degreeTable[x->degree]) {
            Node *y = degreeTable[x->degree];
            degreeTable[x->degree] = NULL;
            mergeTrees(x, y);
        }
        degreeTable[x->degree] = x;
    } while (current != start);

    heap->min = NULL;
    for (int i = 0; i < maxDegree; i++) {
        if (degreeTable[i]) {
            if (!heap->min || degreeTable[i]->key < heap->min->key) {
                heap->min = degreeTable[i];
            }
        }
    }
    free(degreeTable);
}

// 提取最小值
int extractMin(Heap *heap) {
    if (!heap->min) return INT_MAX;
    Node *minNode = heap->min;
    if (minNode->child) {
        Node *child = minNode->child;
        do {
            child->parent = NULL;
            child = child->right;
        } while (child != minNode->child);
        linkNodes(minNode, minNode->child);
    }
    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;

    if (minNode->right == minNode) {
        heap->min = NULL;
    } else {
        heap->min = minNode->right;
        consolidate(heap);
    }
    heap->nodeCount--;
    int minKey = minNode->key;
    free(minNode);
    //printf("Extracted min: %d. Current min: %d\n", minKey, heap->min ? heap->min->key : -1); // Debug
    return minKey;
}

Node *search(Node *root, int key) {
    if (!root) return NULL;

    Node *current = root;
    Node *found = NULL;

    do {
        if (current->key == key) {
            return current; // 找到目標節點
        }

        // 在子節點中遞迴查找
        if (current->child) {
            found = search(current->child, key);
            if (found) return found;
        }

        current = current->right;
    } while (current != root);

    return NULL; // 找不到
}



// 減少鍵值
void decreaseKey(Heap *heap, Node *node, int newKey) {
    if (newKey > node->key) {
        printf("New key is greater than current key\n");
        return;
    }

    node->key = newKey;
    Node *parent = node->parent;

    if (parent && node->key < parent->key) {
        // 切割節點並加入根列表
        if (parent->child == node) {
            parent->child = (node->right == node) ? NULL : node->right;
        }
        parent->degree--;
        linkNodes(heap->min, node);
        node->parent = NULL;
        node->childCut = 0;

        // 級聯切割
        while (parent && parent->childCut) {
            Node *grandParent = parent->parent;
            if (grandParent && grandParent->child == parent) {
                grandParent->child = (parent->right == parent) ? NULL : parent->right;
            }
            linkNodes(heap->min, parent);
            parent->parent = NULL;
            parent->childCut = 0;
            parent = grandParent;
        }

        if (parent) {
            parent->childCut = 1;
        }
    }

    if (node->key < heap->min->key) {
        heap->min = node; // 更新最小值
    }
}


// 刪除鍵值
void deleteKey(Heap *heap, Node *node) {
    decreaseKey(heap, node, INT_MIN);
    extractMin(heap);
}

// 打印 Fibonacci Heap 的層次結構
void printHeap(Node *root) {
    if (!root) return;
    Node *start = root;
    do {
        printf("%d ", root->key);
        if (root->child) {
            printf("[ ");
            printHeap(root->child);
            printf("] ");
        }
        root = root->right;
    } while (root != start);
    printf("\n");
}


// 主程式邏輯
int main() {
    Heap *heap = createHeap();
    char command[20];
    int key, value;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insertNode(heap, key);
        } else if (strcmp(command, "decrease") == 0) {
            scanf("%d %d", &key, &value);
            Node *node = search(heap->min, key); // 此處需補充 search 實作
            if (node) {
                decreaseKey(heap, node, key - value);
            }
        } else if (strcmp(command, "extract-min") == 0) {
            printf("Extracted min: %d\n", extractMin(heap));
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            Node *node = search(heap->min, key); // 此處需補充 search 實作
            if (node) {
                deleteKey(heap, node);
            }
        } else if (strcmp(command, "exit") == 0) {
            printHeap(heap->min);
            break;
        }
    }
    return 0;
}
