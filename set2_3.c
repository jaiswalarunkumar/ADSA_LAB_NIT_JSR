#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    int i, j, n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[MAX], temp[MAX];

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("\nOriginal array:\n");
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // -------- (i) Insertion Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        for (i = 1; i < n; i++) {
            int key = a[i];
            j = i - 1;
            while (j >= 0 && a[j] > key) {
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = key;
        }
        printf("\nInsertion Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (ii) Bubble Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        for (i = 0; i < n-1; i++) {
            for (j = 0; j < n-i-1; j++) {
                if (a[j] > a[j+1]) {
                    int t = a[j]; a[j] = a[j+1]; a[j+1] = t;
                }
            }
        }
        printf("\nBubble Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (iii) Selection Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        for (i = 0; i < n-1; i++) {
            int min = i;
            for (j = i+1; j < n; j++)
                if (a[j] < a[min]) min = j;
            int t = a[min]; a[min] = a[i]; a[i] = t;
        }
        printf("\nSelection Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (iv) Shell Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        for (int gap = n/2; gap > 0; gap /= 2) {
            for (i = gap; i < n; i++) {
                int temp = a[i];
                j = i;
                while (j >= gap && a[j-gap] > temp) {
                    a[j] = a[j-gap];
                    j -= gap;
                }
                a[j] = temp;
            }
        }
        printf("\nShell Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (v) Quick Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int stack[MAX], top = -1;
        stack[++top] = 0; stack[++top] = n-1;
        while (top >= 0) {
            int high = stack[top--];
            int low = stack[top--];
            int pivot = a[high], p = low-1;
            for (i = low; i < high; i++) {
                if (a[i] <= pivot) {
                    p++;
                    int t=a[p]; a[p]=a[i]; a[i]=t;
                }
            }
            int t=a[p+1]; a[p+1]=a[high]; a[high]=t;
            int pi = p+1;
            if (pi-1 > low) { stack[++top]=low; stack[++top]=pi-1; }
            if (pi+1 < high){ stack[++top]=pi+1; stack[++top]=high;}
        }
        printf("\nQuick Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (vi) Merge Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        for (int size=1; size<n; size*=2) {
            for (int left=0; left<n-1; left+=2*size) {
                int mid = left+size-1;
                if (mid >= n-1) continue;
                int right = (left+2*size-1 < n-1)? left+2*size-1 : n-1;
                int l=left, r=mid+1, k=left;
                while (l<=mid && r<=right) temp[k++] = (a[l]<=a[r])? a[l++]:a[r++];
                while (l<=mid) temp[k++]=a[l++];
                while (r<=right) temp[k++]=a[r++];
                for (i=left;i<=right;i++) a[i]=temp[i];
            }
        }
        printf("\nMerge Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (vii) Heap Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        // Build heap
        for (i=n/2-1;i>=0;i--){
            int root=i;
            while(2*root+1<n){
                int child=2*root+1;
                if(child+1<n && a[child]<a[child+1]) child++;
                if(a[root]<a[child]){
                    int t=a[root];a[root]=a[child];a[child]=t;
                    root=child;
                }else break;
            }
        }
        // Extract
        for(i=n-1;i>0;i--){
            int t=a[0];a[0]=a[i];a[i]=t;
            int root=0;
            while(2*root+1<i){
                int child=2*root+1;
                if(child+1<i && a[child]<a[child+1]) child++;
                if(a[root]<a[child]){
                    int t=a[root];a[root]=a[child];a[child]=t;
                    root=child;
                }else break;
            }
        }
        printf("\nHeap Sort:\n");
        for (i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (viii) Radix Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int max=a[0]; for(i=1;i<n;i++) if(a[i]>max) max=a[i];
        for(int exp=1; max/exp>0; exp*=10){
            int output[MAX]={0}, count[10]={0};
            for(i=0;i<n;i++) count[(a[i]/exp)%10]++;
            for(i=1;i<10;i++) count[i]+=count[i-1];
            for(i=n-1;i>=0;i--) output[--count[(a[i]/exp)%10]]=a[i];
            for(i=0;i<n;i++) a[i]=output[i];
        }
        printf("\nRadix Sort:\n");
        for(i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (ix) Counting Sort --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int max=a[0]; for(i=1;i<n;i++) if(a[i]>max) max=a[i];
        int min=a[0]; for(i=1;i<n;i++) if(a[i]<min) min=a[i];
        int range=max-min+1;
        int *count=(int*)calloc(range,sizeof(int));
        for(i=0;i<n;i++) count[a[i]-min]++;
        int idx=0;
        for(i=0;i<range;i++) while(count[i]--) a[idx++]=i+min;
        free(count);
        printf("\nCounting Sort:\n");
        for(i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (x) Bucket Sort -------- (simple, for non-negative small range)
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int max=a[0]; for(i=1;i<n;i++) if(a[i]>max) max=a[i];
        int bucket[MAX+1]={0};
        for(i=0;i<n;i++) bucket[a[i]]++;
        int idx=0;
        for(i=0;i<=max;i++) while(bucket[i]--) a[idx++]=i;
        printf("\nBucket Sort:\n");
        for(i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (xi) Radix Exchange Sort (binary quicksort) --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int max=a[0]; for(i=1;i<n;i++) if(a[i]>max) max=a[i];
        int bit=0; while((1<<bit)<=max) bit++;
        int stack[2*MAX], top=-1;
        stack[++top]=0; stack[++top]=n-1; stack[++top]=bit-1;
        while(top>=0){
            int b=stack[top--];
            int high=stack[top--];
            int low=stack[top--];
            if(low>=high || b<0) continue;
            int i=low,j=high;
            while(i<=j){
                while(i<=j && ((a[i]>>b)&1)==0) i++;
                while(i<=j && ((a[j]>>b)&1)==1) j--;
                if(i<j){int t=a[i];a[i]=a[j];a[j]=t;}
            }
            stack[++top]=low; stack[++top]=j; stack[++top]=b-1;
            stack[++top]=j+1; stack[++top]=high; stack[++top]=b-1;
        }
        printf("\nRadix Exchange Sort:\n");
        for(i=0;i<n;i++) printf("%d ", a[i]);
        printf("\n");
    }

    // -------- (xii) Address Calculation Sort (scatter sort, simple hash) --------
    {
        int a[MAX]; memcpy(a, arr, n*sizeof(int));
        int max=a[0]; for(i=1;i<n;i++) if(a[i]>max) max=a[i];
        int addr[MAX+1]; for(i=0;i<=max;i++) addr[i]=-1;
        for(i=0;i<n;i++) addr[a[i]]=a[i];
        printf("\nAddress Calculation Sort:\n");
        for(i=0;i<=max;i++) if(addr[i]!=-1) printf("%d ", addr[i]);
        printf("\n");
    }

    return 0;
}
