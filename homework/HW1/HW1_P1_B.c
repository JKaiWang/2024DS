#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100


struct Stack{
    char array[MAX];
    int top;
};

struct Stack* createStack(){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isFull(struct Stack* stack){
    return stack->top == (MAX-1);
}

int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack , char c){
    if(isFull(stack)){
        return ; 
    }
    else{
        stack->array[++stack->top] = c;
        return;
    }
}

char pop(struct Stack* stack){
    if(!isEmpty(stack)){
        return stack->array[stack->top--];
    }
    else{
        return ' ';
    } 
}

char peek(struct Stack* stack){
    if(!isEmpty(stack)){
        return stack->array[stack->top];
    }
    else{
        printf("the stack doesn't have anything");
    }
}

//determine the operator */  and +-
int precedence(char op){
    if(op == '*' || op == '/'){
        return 2;
    }
    else if(op == '+' || op == '-'){
        return 1;
    }
    else{
        return 0;
    }
}

//determine whether it is operator or not
int isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;
    }
    else{
        return 0;
    }
}

void infixToPostfix(char* string , char* postfix){
    int index =0;
    struct Stack* stack = createStack();
    for(int i=0 ; i<strlen(string) ; i++){
        char temp = string[i];
        if(!isOperator(temp)){
            postfix[index++] = temp;
        }
        else if(isOperator(temp)){
            //to make sure that the stack isn't empty the precedence of operator
            while(!isEmpty(stack) && precedence(peek(stack)) >= precedence(temp)){
                    postfix[index++] = pop(stack);
            }
            push(stack , temp);
        }
    }

    //pop out the rest of the stack
    while(!isEmpty(stack)){
        postfix[index++] = pop(stack);
    }
    postfix[index++] ='\0';
}


//e.g.
//input:
//  A*B-C/D
//output:
//  AB*CD/-
//input:
//  A+B-C*D/E
//output:
//  AB+CD*E/-
int main(){
    struct Stack* stack = createStack();
    char data[MAX];
    char postfix[MAX];
    scanf("%s" , data);
    infixToPostfix(data , postfix);
    for(int i=0 ; i<strlen(postfix) ; i++){
        printf("%c" , postfix[i]);
    }
}