#include <stdio.h>
#include <item.h>

void merge(Item A[], Item B[], int l, int c, int r) {
    int i, j, k;
    i = l; //0
    j = c+1; // 1
    for (k = l; k <=r; k++) {
        if (i > c) 
            B[k] = A[j++];
        else if (j > r) 
            B[k] = A[i++];
        else if (ITEMlt(A[i], A[j] || ITEMeq(A[i], A[j])))
            B[k] = A[i++];
        else
            B[k] = A[j++];
    }
    for (k = l; k <= r; k++)
        A[k] = B[k];
}


void mergeSort(Item A[], Item B[], int N) {
    int l = 0, r = N-1;
    mergeSortRecursive(A, B, l, r);
}

static void mergeSortRecursive_impl(Item A[], Item B[], int l, int r) {
    int c;
    if (l>=r) return;
    c = (l+r)/2;
    mergeSortRecursive_impl(A, B, l, c);
    mergeSortRecursive_impl(A, B, c+1, r);
    merge(A, B, l, c, r);
}



