#include <stdio.h>
#define SIZE 100

int s1[SIZE], s2[SIZE], top1=-1, top2=-1;

void push1(int x){ s1[++top1]=x; }
int pop1(){ return s1[top1--]; }
void push2(int x){ s2[++top2]=x; }
int pop2(){ return s2[top2--]; }

void enqueue(int x){               // O(1)
    push1(x);
}

int dequeue(){                     // O(n)
    if(top1==-1) return printf("Empty\n"), -1;
    while(top1!=-1) push2(pop1());
    int val = pop2();
    while(top2!=-1) push1(pop2());
    return val;
}

int main(){
    enqueue(10); enqueue(20); enqueue(30);
    printf("%d ", dequeue());
    printf("%d ", dequeue());
    return 0;
}
