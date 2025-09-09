#include <stdio.h>
#define SIZE 100

int q1[SIZE], q2[SIZE], f1=0,r1=-1,f2=0,r2=-1;

int isEmpty1(){ return f1>r1; }
int isEmpty2(){ return f2>r2; }

void enqueue1(int x){ q1[++r1]=x; }
int dequeue1(){ return q1[f1++]; }

void enqueue2(int x){ q2[++r2]=x; }
int dequeue2(){ return q2[f2++]; }

void swapQueues(){
    int tq[SIZE], tf=f1,tr=r1;
    for(int i=f1;i<=r1;i++) tq[i]=q1[i];
    int tqf=f2,tqr=r2;
    for(int i=f2;i<=r2;i++) q1[i]=q2[i];
    f1=f2; r1=r2;
    for(int i=tf;i<=tr;i++) q2[i]=tq[i];
    f2=tf; r2=tr;
}

/* -------- Method 1: Push costly -------- */
void push1(int x){
    enqueue2(x);
    while(!isEmpty1()) enqueue2(dequeue1());
    swapQueues();
}
int pop1(){ return isEmpty1()?printf("Empty\n"),-1:dequeue1(); }

/* -------- Method 2: Pop costly -------- */
void push2(int x){ enqueue1(x); }
int pop2(){
    if(isEmpty1()) return printf("Empty\n"),-1;
    while(f1<r1) enqueue2(dequeue1());
    int val = dequeue1();
    swapQueues();
    return val;
}

int main(){
    int choice, method, x;
    printf("Select method:\n1. Push costly\n2. Pop costly\n");
    scanf("%d", &method);

    while(1){
        printf("\n1.Push  2.Pop  3.Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter value: "); scanf("%d",&x);
                if(method==1) push1(x);
                else push2(x);
                break;
            case 2:
                if(method==1) printf("Popped: %d\n", pop1());
                else printf("Popped: %d\n", pop2());
                break;
            case 3: return 0;
        }
    }
}
