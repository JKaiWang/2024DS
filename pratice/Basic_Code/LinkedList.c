#include<stdio.h>
#include<stdlib.h>

// create a node
struct Node{
    int data;
    struct Node* next;
};
typedef struct Node* node;

//Insert at the beginning
void insertStart(struct Node **head , int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;

    newNode->next = *head;

    *head = newNode;
}  

void insertEnd (struct Node **head, int data)
{

  struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));

  newNode->data = data;
  // since this will be the last node so it will point to NULL
  newNode->next = NULL;

  // if the Linked List is empty this is the first node being entered
  if (*head == NULL)
    {
      *head = newNode;
      return;
    }

  // create another variable to traverse the LL
  // *head should not be used as we do not want to change head
  struct Node *temp = *head;

  // traverse to the last node of Linked List
  while (temp->next != NULL)
    temp = temp->next;

  // assign last node's next to this newNode
  temp->next = newNode;
}

// required for insertAfter
int getCurrSize (struct Node *node)
{
  int size = 0;

  while (node != NULL)
    {
      node = node->next;
      size++;
    }
  return size;
}

void insertPosition (int pos, int data, struct Node **head)
{
  int size = getCurrSize (*head);

  // Can only insert after 1st position
  // Can't insert if position to insert is greater than size of Linked List
  if (pos < 1 || pos > size)
    printf ("Invalid position to insert");

  else
    {
      struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
      newNode->data = data;
      newNode->next = NULL;

      // temp used to traverse the Linked List
      struct Node *temp = *head;

      // traverse till the nth node
      while (--pos)
	temp = temp->next;

      // assign newNode's next to nth node's next
      newNode->next = temp->next;
      // assign nth node's next to this new node
      temp->next = newNode;
      // newNode inserted b/w 3rd and 4th node
    }
}

void display (struct Node *node)
{

  // as linked list will end when Node is Null
  while (node != NULL)
    {
      printf ("%d ", node->data);
      node = node->next;
    }
  printf ("\n");
}

int main ()
{
  struct Node *head = NULL;

  // Need '&' i.e. address as we need to change head
  insertStart (&head, 3);
  insertStart (&head, 2);
  insertStart (&head, 1);

  // no need for '&' as head need not be changed
  // only doing traversal
  display (head);

  insertEnd (&head, 5);
  insertEnd (&head, 6);
  insertEnd (&head, 7);

  display (head);

  //Inserts data: 4 after 3rd position
  insertPosition (3, 4, &head);

  display (head);
  return 0;
}