#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int l, r, state;
} Frame;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortIterative(int arr[], int n) {
    Frame stack[MAX];
    int top = -1;

    // push initial frame
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame f = stack[top--];

        if (f.l >= f.r) continue;

        if (f.state == 0) {
            // push current frame back with state=1 (after children processed)
            stack[++top] = (Frame){f.l, f.r, 1};
            int m = (f.l + f.r) / 2;
            // push right and left halves
            stack[++top] = (Frame){m + 1, f.r, 0};
            stack[++top] = (Frame){f.l, m, 0};
        } 
        else {
            int m = (f.l + f.r) / 2;
            merge(arr, f.l, m, f.r);
        }
    }
}

int main() {
    int n, arr[MAX];
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    mergeSortIterative(arr, n);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
