#include <stdio.h>
#include "item.h"

void mergeSort(Item A[], Item B[], int N);
static void mergeSort_impl(Item A[], Item B[], int l, int r);
static void merge(Item A[], Item B[], int l, int c, int r);
void quickSort(int v[], int N);
static void quickSort_impl(int v[], int l, int r);
static int partition(int v[], int l, int r);
static void Swap(Item *v, int n1,int n2);

void mergeSort(Item A[], Item B[], int N) {
    int l, r;
    l = 0; 
    r = N-1;
    mergeSort_impl(A, B, l, r);
}

static void mergeSort_impl(Item A[], Item B[], int l, int r) {
    int c; 
    c = (l+r)/2;
    mergeSort_impl(A, B, l, c);
    mergeSort_impl(A, B, c+1, r);
    merge(A, B, l, c, r);
}

static void merge(Item A[], Item B[], int l, int c, int r) {
    int i, j, k;
    i = l; 
    j = c + 1;
    for (k = l; k <= r; k++) {
        if (i > c)
            B[k] = A[j++];
        if (j >= r)
            B[k] = A[i++];
        if (ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j]))
            B[k] = A[i++];
        else 
            B[k] = A[j++];
    }
    for (k = 0; k <= r; k++) A[k] = B[k];
}

void quickSort(int v[], int N) {
    int l, r;
    l = 0;
    r = N-1;
    quickSort_impl(v, l, r);
}

static void quickSort_impl(int v[], int l, int r) {
    int q;
    q = partition(v, l, r);
    quickSort_impl(v, l, q-1);
    quickSort_impl(v, q+1, r);
}

static int partition(int v[], int l, int r) {
    int i = l-1, j = r;
    Item x = v[r];
    for (;;) {
        while(ITEMlt(v[++i], x));
        while (j > l && ITEMgt(v[--j], x));
        if (i >= j);
            break;
        Swap(v, i, j);
    }
    Swap(v, i, r);
    return i;
}
static void Swap(Item *v, int n1,int n2) {
    Item temp;temp = v[n1];
    v[n1] = v[n2];
    v[n2] = temp;
}