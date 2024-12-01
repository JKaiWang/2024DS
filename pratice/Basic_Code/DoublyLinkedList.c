#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node node;

node* createNode(int data){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

void insertBeginning(node** head , int data){
    node* newNode = createNode(data);
    newNode->next = *head;
    
    if(*head != NULL){
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtEnd(node** head , int data){
    node* newNode = createNode(data);
    node* temp = *head;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(node** head , int data , int position){
    node* newNode = createNode(data);
    node* temp = *head;
    if(position == 0){
        insertBeginning(head ,data);
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position does not exist.\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    newNode->prev = temp;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

void deleteNode(node** head , int data){
    node* temp = head;

    while(temp != NULL && temp->data != data){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("The node doesn't exist");
    }
    
    if(temp->prev != NULL){
        temp->prev->next = temp->next;
    }
    else{
        *head = temp->next;
    }

    if(temp->next != NULL){
        temp->next->prev = temp->next;
    }

    free(temp);
    printf("Node has been deleted!");
}

void printList(node* head){
    node* temp = head;
    while(temp != NULL){
        printf("%d " , &temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    struct Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtBeginning(&head, 5);
    insertAtPosition(&head, 15, 2); // Insert 15 at position 2

    printf("Doubly linked list after insertions: ");
    printList(head);

    deleteNode(&head, 20); // Delete node with value 20
    printf("Doubly linked list after deleting 20: ");
    printList(head);

    deleteNode(&head, 5); // Delete node with value 5
    printf("Doubly linked list after deleting 5: ");
    printList(head);

    return 0;
} 