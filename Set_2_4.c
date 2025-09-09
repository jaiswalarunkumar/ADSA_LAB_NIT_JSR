#include <stdio.h>
#include <stdlib.h>

// Merge function
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

// Iterative merge sort (bottom-up)
void mergeSort(int arr[], int n) {
    for (int curr = 1; curr < n; curr *= 2) {
        for (int left = 0; left < n - 1; left += 2 * curr) {
            int mid = left + curr - 1;
            int right = (left + 2 * curr - 1 < n - 1) ? left + 2 * curr - 1 : n - 1;
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

// Print array
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
