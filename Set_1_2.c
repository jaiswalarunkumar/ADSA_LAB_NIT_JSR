#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack for numbers
double numStack[100];
int numTop = -1;

void pushNum(double val) {
    numStack[++numTop] = val;
}
double popNum() {
    return numStack[numTop--];
}

// Stack for operators
char opStack[100];
int opTop = -1;

void pushOp(char op) {
    opStack[++opTop] = op;
}
char popOp() {
    return opStack[opTop--];
}
char peekOp() {
    return opStack[opTop];
}

// precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// apply operator on two numbers
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// evaluate arithmetic expression
double evaluate(char* expr) {
    int i;
    for (i = 0; i < strlen(expr); i++) {
        // skip spaces
        if (expr[i] == ' ')
            continue;

        // number
        if (isdigit(expr[i])) {
            double val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--;
            pushNum(val);
        }

        // opening bracket
        else if (expr[i] == '(') {
            pushOp(expr[i]);
        }

        // closing bracket
        else if (expr[i] == ')') {
            while (opTop != -1 && peekOp() != '(') {
                double b = popNum();
                double a = popNum();
                char op = popOp();
                pushNum(applyOp(a, b, op));
            }
            if (opTop != -1) popOp(); // remove '('
        }

        // operator
        else {
            while (opTop != -1 && precedence(peekOp()) >= precedence(expr[i])) {
                double b = popNum();
                double a = popNum();
                char op = popOp();
                pushNum(applyOp(a, b, op));
            }
            pushOp(expr[i]);
        }
    }

    // remaining ops
    while (opTop != -1) {
        double b = popNum();
        double a = popNum();
        char op = popOp();
        pushNum(applyOp(a, b, op));
    }

    return popNum();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    // join command line args into one expression string
    char expr[1000] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
        strcat(expr, " ");
    }

    double result = evaluate(expr);
    printf("%.0f\n", result);

    return 0;
}
