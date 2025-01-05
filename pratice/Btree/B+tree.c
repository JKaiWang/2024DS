#include <stdio.h>
#include <stdlib.h>

int isfull;
int Max = 2;
int fisrtnode = 0;

typedef struct inNode {
    int key;
    struct inNode* next;
    struct Node* right;
} inNode;

inNode* createInNode(int data) {
    inNode* newNode = (inNode*)malloc(sizeof(inNode));
    newNode->key = data;
    newNode->right = NULL;
    newNode->next = NULL;
    return newNode;
}

typedef struct Node {
    int n;
    struct inNode* member;
    struct Node* child;
    int isindex; // 0 = data node, 1 = index node
    struct Node* parent;
} Node;

Node* create(int data, int who) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->isindex = who;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->n = 1;
    newNode->member = createInNode(data);
    return newNode;
}

void inNodeinsert(inNode** head, int data) {
    inNode* newnode = createInNode(data);
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    inNode* temp = *head;
    if (temp->key > data) {
        *head = newnode;
        newnode->next = temp;
    } else {
        while (temp->next != NULL) {
            if (temp->key < data && temp->next->key > data) {
                newnode->next = temp->next;
                temp->next = newnode;
                return;
            }
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

Node* reinsert(Node* parent, Node* child) {
    // 創建新的節點
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->isindex = child->isindex;
    newNode->parent = parent;
    newNode->n = 0;
    newNode->member = NULL;

    // 分裂節點
    int mid = (child->n + 1) / 2;
    inNode* temp = child->member;
    inNode* prev = NULL;
    for (int i = 0; i < mid - 1; i++) {
        prev = temp;
        temp = temp->next;
    }
    inNode* middle = temp; // 中間鍵
    temp = temp->next; // 後半部分的開始
    if (prev != NULL) {
        prev->next = NULL; // 將鏈結串列分成兩部分
    }

    if (child->isindex == 0) {
        // 將中間鍵分裂到右半邊
        newNode->member = middle;
        newNode->member->next = temp;
        newNode->isindex = 0;
        newNode->n = child->n - mid + 1;
        child->n = mid - 1;

        // 再建一個相同值的結點提升到父結點
        middle = createInNode(middle->key);
    } else {
        newNode->member = temp;
        newNode->isindex = 1;
        newNode->n = child->n - mid;
        child->n = mid - 1;
    }

    // 更新指標
    temp = newNode->member;
    while (temp != NULL) {
        if (newNode->child != NULL) {
            newNode->child->parent = newNode;
        }
        if (temp->right != NULL) {
            temp->right->parent = newNode;
        }
        temp = temp->next;
    }

    // 將中間鍵提升到父節點
    middle->right = newNode;

    // 插入中間鍵到父節點
    inNodeinsert(&(parent->member), middle->key);
    inNode* now = parent->member;
    while (now->key != middle->key) {
        now = now->next;
    }
    now->right = middle->right;

    // 更新父節點的子節點數量
    parent->n++;
    if (parent->n > Max) {
        isfull = 1;
    } else {
        isfull = 0;
    }
    return parent;
}

Node* insert(Node* node, int data) {
    isfull = 0;

    if (fisrtnode == 0) {
        Node* newNode = create(data, 0);
        node = create(data, 1);
        node->member->right = newNode;
        newNode->parent = node;
        fisrtnode = 1;
        return node;
    }

    inNode* now = node->member;
    Node* nextNode;

    if (data < now->key) {
        nextNode = node->child;
    } else {
        while (now->next != NULL && data >= now->next->key) {
            now = now->next;
        }
        nextNode = now->right;
    }

    if (node->isindex == 0) {
        inNode* dataNode = createInNode(data);
        dataNode->next = now->next;
        now->next = dataNode;
        (node->n)++;
        if (node->n > Max) {
            isfull = 1;
        }
        return node;
    }

    nextNode = insert(nextNode, data);

    if (isfull == 1) {
        Node* childNode;
        inNode* findnode = node->member;
        while (findnode != NULL) {
            if (node->child != NULL && node->child->n > Max) {
                childNode = node->child->n;
                break;
            }
            if (findnode->right != NULL && findnode->right->n > Max) {
                childNode = findnode->right;
                break;
            }
            findnode = findnode->next;
        }
        node = reinsert(node, childNode);
    }
    if(isfull == 1 && node->parent == NULL){
        Node* newroot = create(node->member->next, 1);
        
    }
    return node;
}

int main() {
    Node* root = NULL;
    root = insert(root, 3);
    printf("%d\n", root->member->right->member->key);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    printf("%d\n", root->member->next->right->member->key);
    printf("%d\n", root->member->next->right->member->next->key);

    return 0;
}