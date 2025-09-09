#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack structure
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    if (!stack->array)
        return NULL;
    return stack;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Push an item to the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Pop an item from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack))
        return '$';
    return stack->array[stack->top--];
}

// Peek at the top item of the stack without popping
char peek(struct Stack* stack) {
    if (isEmpty(stack))
        return '$';
    return stack->array[stack->top];
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get the precedence of an operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to convert infix to postfix
void infixToPostfix(const char* exp) {
    int i, k;
    // Create a stack with a capacity equal to the expression length
    struct Stack* stack = createStack(strlen(exp));
    if (!stack)
        return;

    printf("Infix expression: %s\n", exp);
    printf("Postfix expression: ");
    for (i = 0, k = -1; exp[i]; ++i) {
        // If the character is an operand, add it to the output
        if (isdigit(exp[i])) {
            printf("%c", exp[i]);
        }
        // If the character is '(', push it to the stack
        else if (exp[i] == '(') {
            push(stack, exp[i]);
        }
        // If the character is ')', pop from stack until '(' is found
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                printf("%c", pop(stack));
            }
            if (!isEmpty(stack) && peek(stack) != '(') {
                // Invalid expression
                printf("Invalid Expression\n");
                return;
            } else {
                pop(stack); // Pop '('
            }
        }
        // If an operator is encountered
        else {
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack))) {
                printf("%c", pop(stack));
            }
            push(stack, exp[i]);
        }
    }

    // Pop all remaining operators from the stack
    while (!isEmpty(stack)) {
        printf("%c", pop(stack));
    }
    printf("\n");
    free(stack->array);
    free(stack);
}

// Main function to test the converter
int main() {
    char expression1[] = "1+2*3";
    infixToPostfix(expression1);

    char expression2[] = "1*2+3";
    infixToPostfix(expression2);

    char expression3[] = "(1+2)*3";
    infixToPostfix(expression3);

    char expression4[] = "1+(2*3)";
    infixToPostfix(expression4);
    
    char expression5[] = "1+(2+3)*4/5-6";
    infixToPostfix(expression5);

    return 0;
}
