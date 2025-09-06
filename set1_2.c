#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// ---------- Stack for operators ----------
char opStack[MAX];
int opTop = -1;

void pushOp(char c) {
    if (opTop < MAX - 1)
        opStack[++opTop] = c;
}

char popOp() {
    if (opTop >= 0)
        return opStack[opTop--];
    return '\0';
}

char peekOp() {
    if (opTop >= 0)
        return opStack[opTop];
    return '\0';
}

int precedence(char op) {
    switch (op) {
        case '/': case '*': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// ---------- Stack for evaluation ----------
int valStack[MAX];
int valTop = -1;

void pushVal(int v) {
    if (valTop < MAX - 1)
        valStack[++valTop] = v;
}

int popVal() {
    if (valTop >= 0)
        return valStack[valTop--];
    return 0;
}

// ---------- Infix to Postfix ----------
void infixToPostfix(const char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;

    while ((c = infix[i]) != '\0') {
        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c)) {
            // handle multi-digit numbers
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // delimiter
            continue;
        }

        if (c == '(') {
            pushOp(c);
        }
        else if (c == ')') {
            while (opTop >= 0 && peekOp() != '(') {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            popOp(); // remove '('
        }
        else if (isOperator(c)) {
            while (opTop >= 0 && precedence(peekOp()) >= precedence(c)) {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            pushOp(c);
        }

        i++;
    }

    while (opTop >= 0) {
        postfix[j++] = popOp();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

// ---------- Evaluate Postfix ----------
int evaluatePostfix(const char *postfix) {
    int i = 0;
    char token[MAX];

    while (postfix[i] != '\0') {
        if (isspace(postfix[i])) {
            i++;
            continue;
        }

        if (isdigit(postfix[i])) {
            int k = 0;
            while (isdigit(postfix[i])) {
                token[k++] = postfix[i++];
            }
            token[k] = '\0';
            pushVal(atoi(token));
        }
        else if (isOperator(postfix[i])) {
            int b = popVal();
            int a = popVal();
            switch (postfix[i]) {
                case '+': pushVal(a + b); break;
                case '-': pushVal(a - b); break;
                case '*': pushVal(a * b); break;
                case '/': pushVal(a / b); break;
            }
            i++;
        }
        else {
            i++;
        }
    }

    return popVal();
}

// ---------- Main ----------
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    // Join arguments into single string (to handle spaces)
    char expr[MAX] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
        strcat(expr, " ");
    }

    char postfix[MAX];
    infixToPostfix(expr, postfix);

    int result = evaluatePostfix(postfix);
    printf("%d\n", result);

    return 0;
}
