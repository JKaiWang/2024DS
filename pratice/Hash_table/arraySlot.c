//search(key)
//insert(key , elemeny)
//delete(key)
//time complexity: O(1)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10

typedef struct Node{
    int key;
    char value[100];
    struct Node* next;
}Node;

Node* hashTable[MAX];

int hashFunction(int key){
    return key%MAX;
}

void insert(int key , const char* value){
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value , value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

char* search(int key){
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    while(temp){
        if(temp->key == key){
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

void delete(int key){
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;
    while(temp){
        if(temp->key == key){
            if(prev){
                prev->next = temp->next;
            }
            else{
                hashTable[index] = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void printHashTable(){
    for(int i=0 ; i< MAX ; i++){
        printf("Buckey %d" , i);
        Node* temp = hashTable[i];
        while(temp){
            printf("(%d , %s)" , temp->key , temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    // 初始化哈希表
    for (int i = 0; i < MAX; i++) {
        hashTable[i] = NULL;
    }

    // 測試
    insert(1, "One");
    insert(11, "Eleven");
    insert(21, "Twenty One");
    insert(2, "Two");
    insert(12, "Twelve");

    printf("Hash Table:\n");
    printHashTable();

    printf("\nSearch for key 11: %s\n", search(11));
    printf("Search for key 3: %s\n", search(3) ? search(3) : "Not found");

    printf("\nDeleting key 11...\n");
    delete (11);
    printHashTable();

    return 0;
}