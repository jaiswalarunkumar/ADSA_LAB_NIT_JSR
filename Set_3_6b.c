#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *rear = NULL;

void enqueue(int x) {
    Node *n = malloc(sizeof(Node));
    n->data = x;
    if (!rear) { rear = n; rear->next = rear; }
    else { n->next = rear->next; rear->next = n; rear = n; }
}

int dequeue() {
    if (!rear) return printf("Queue empty\n"), -1;
    Node *front = rear->next;
    int x = front->data;
    if (front == rear) rear = NULL;
    else rear->next = front->next;
    free(front);
    return x;
}

void display() {
    if (!rear) return printf("Empty\n");
    Node *p = rear->next;
    do { printf("%d ", p->data); p = p->next; } while (p != rear->next);
    printf("\n");
}

int main() {
    enqueue(10); enqueue(20); enqueue(30); display();
    printf("Deq: %d\n", dequeue()); display();
}
