#include<stdio.h>
#include<stdlib.h>
//we need to create a stack struct including stack array , top  and capacity
//then we need the create stack function all they need to do is malloc a space to let the stack sotr
//and let the top = -1 and malloc an array so that we can put data in the stack
//there are some operation that dynamic stack array can use
// isFull() isEmpty() push() pop() peeek() those of them are basic functions of stack
//however there is a funtion that is different from the basic stack data structur
//which is resizeStack() : when the original stack is full and you want to add some data inside the stack
//you need to realloc the stack array 
//e.g. 
//     stack->capacity *= 2;
//     stack->arr = (int*)realloc(stack->arr , stack->capacity*sizeof(int));
typedef struct Stack{
    int *arr;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity){
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(stack->capacity*sizeof(int));
    return stack;
}

int isFull(Stack *stack){
    return stack->top == stack->capacity-1;
}

int isEmpty(Stack *stack){
    return stack->top == -1;
}

void resizeStack(Stack *stack){
    stack->capacity *= 2;
    stack->arr = (int*)realloc(stack->arr , stack->capacity*sizeof(int));
}

void push(Stack *stack , int data){
    if(isFull(stack)){
        resizeStack(stack);
    }
    stack->arr[++stack->top] = data;
}

int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("stack underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

int main(){
    Stack *stack = createStack(2);

    push(stack , 10);
    push(stack , 20);
    push(stack , 30);

    printf("Top element: %d\n" , peek(stack));

    printf("Popped element: %d\n" , pop(stack));
    printf("Popped element: %d\n" , pop(stack));

    free(stack->arr);
    free(stack);
    return 0;
}