#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 8
int stack[MAXSIZE];
int top = -1;

int isEmpty();
int isFull();
int pop();
void push(int data);

int main(){
    push(1);
}

int isEmpty(){
    if(top == -1) return 1;
    else return 0;
}

int isFull(){
    if(top == MAXSIZE) return 1;
    else return 0;
}

int pop(){
    int data;
    if(!isEmpty()){
        data = stack[top--];
        return data;
    }
    else{
        printf("Can't not pop the data cuz the stack is empty!");
    }
}

void push(int data){
    if(!isFull()){
        stack[++top] = data;
    }
    else{
        printf("Couldn't push the data in stack because the stack is full");

    }
}