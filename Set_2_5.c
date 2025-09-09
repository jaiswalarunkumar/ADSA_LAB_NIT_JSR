#include <stdio.h>

// Merge two sorted subarrays arr[l..m] and arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Bottom-up iterative merge sort
void mergeSort(int arr[], int n) {
    for (int size = 1; size < n; size *= 2) {              // subarray size
        for (int left = 0; left < n - size; left += 2*size) {
            int mid = left + size - 1;
            int right = (left + 2*size - 1 < n-1) ? left + 2*size - 1 : n-1;
            merge(arr, left, mid, right);
        }
    }
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    mergeSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);
    return 0;
}
