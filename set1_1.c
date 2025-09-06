#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

char peek() {
    if (top >= 0) return stack[top];
    return '\0';
}

int precedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 3;
        case '+': return 2;
        case '-': return 2;
        default: return 1;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void infixToPostfix(const char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;

    while ((c = infix[i++]) != '\0') {
        if (isdigit(c)) {
            // Operand: directly add to output
            postfix[j++] = c;
        } 
        else if (c == '(') {
            push(c);
        } 
        else if (c == ')') {
            // Pop until '('
            while (top >= 0 && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // remove '('
        } 
        else if (isOperator(c)) {
            while (top >= 0 && precedence(peek()) >= precedence(c)) {
                postfix[j++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top >= 0) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
