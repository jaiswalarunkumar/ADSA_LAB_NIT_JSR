#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void merge(int arr[], int l, int m, int r, int temp[]) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (i = l; i <= r; i++) arr[i] = temp[i];
}

void mergeSortBottomUp(int arr[], int n) {
    int temp[MAX];

    // size = current size of subarrays to merge
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1) continue; // no right half
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            merge(arr, left, mid, right, temp);
        }
    }
}

int main() {
    int n, arr[MAX];
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    mergeSortBottomUp(arr, n);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
