#include <stdio.h>
#include "item.h"

void mergeSort(Item A[], Item B[], int N);
static void mergeSortRecursive_impl(Item A[], Item B[], int l, int r);
static void merge(Item A[], Item B[], int l, int c, int r);
void QuickSort(Item A[], int N);
static void quicksort_impl(Item A[], int l, int r);
static int partition (Item A[], int l, int r );
static void Swap(Item *v, int n1, int n2);

int main() {

}


//MERGESORT WRAPPER
void mergeSort(Item A[], Item B[], int N) {
    int l = 0, r = N-1;
    mergeSortRecursive_impl(A, B, l, r);
}

//MERGESORT IMPLEMENTATION
static void mergeSortRecursive_impl(Item A[], Item B[], int l, int r) {
    int c;
    if (l>=r) return;
    c = (l+r)/2;
    mergeSortRecursive_impl(A, B, l, c);
    mergeSortRecursive_impl(A, B, c+1, r);
    merge(A, B, l, c, r);
}

//MERGE FUNCTION
static void merge(Item A[], Item B[], int l, int c, int r) {
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



//QUICKSORT WRAPPER
void QuickSort(Item A[], int N) {
    int l=0, r=N-1;
    quicksort_impl(A, l, r);
}

//QUICKSORT IMPLEMENTATION
static void quicksort_impl(Item A[], int l, int r) {
    int q;
    if (l >= r)
        return;
    q = partition(A, l, r);
    quicksort_impl(A, l, q-1);
    quicksort_impl(A, q+1, r);
    return;
}

//PARTITION FUNCTION
static int partition (Item A[], int l, int r ) {
    int i = l-1, j = r;
    Item x = A[r];
    for ( ; ; ) {
        while(ITEMlt(A[++i], x));
        while(j > l && ITEMgt(A[--j], x));
        if (i >= j)
            break;
        Swap(A, i, j);
    }
    Swap(A, i, r);
    return i;
}

//SWAP HELPER FUNCTION
static void Swap(Item *v, int n1, int n2) {
    Item temp;
    temp = v[n1];
    v[n1] = v[n2];
    v[n2] = temp;
    return;
}