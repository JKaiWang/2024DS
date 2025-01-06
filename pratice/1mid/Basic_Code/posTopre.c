#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack to hold expressions as a single 1D array
char stack[MAX][MAX];
int top = -1;

// Push function for the 1D stack
void push(char *str) {
    if (top < MAX - 1) {
        top++;
        strcpy(stack[top], str);
    }
}

// Pop function for the 1D stack
void pop(char *str) {
    if (top >= 0) {
        strcpy(str, stack[top]);
        top--;
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Convert postfix to prefix
void postfixToPrefix(char *postfix) {
    char operand1[MAX], operand2[MAX], temp[MAX];
    int len = strlen(postfix);

    // Traverse the postfix expression from left to right
    for (int i = 0; i < len; i++) {
        // If the character is an operand, push it to the stack
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        }
        // If the character is an operator
        else if (isOperator(postfix[i])) {
            // Pop two operands from the stack
            pop(operand2);
            pop(operand1);

            // Create a new expression by prepending the operator
            snprintf(temp, sizeof(temp), "%c%s%s", postfix[i], operand1, operand2);

            // Push the new expression back to the stack
            push(temp);
        }
    }

    // The final element in the stack is the prefix expression
    char result[MAX];
    pop(result);
    printf("Prefix Expression: %s\n", result);
}

int main() {
    char postfix[MAX];
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    postfixToPrefix(postfix);

    return 0;
}
