#include <stdio.h>
#define SIZE 5

int q[SIZE], front = -1, rear = -1;

int isFull()  { return (front == (rear + 1) % SIZE); }
int isEmpty() { return (front == -1); }

void enqueue(int x) {
    if (isFull()) return printf("Queue full\n");
    if (isEmpty()) front = 0;
    rear = (rear + 1) % SIZE;
    q[rear] = x;
}

int dequeue() {
    if (isEmpty()) return printf("Queue empty\n"), -1;
    int x = q[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % SIZE;
    return x;
}

void display() {
    if (isEmpty()) return printf("Empty\n");
    int i = front;
    while (1) {
        printf("%d ", q[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10); enqueue(20); enqueue(30); display();
    printf("Deq: %d\n", dequeue()); display();
}
