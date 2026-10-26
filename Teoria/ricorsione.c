#include <stdio.h>


void mark(int m, int h);
int fattoriale(int n);
int fibonacci(int n);
int gcd1(int x, int y);
int gcd2(int x, int y);
long prod(int *x, int lx, int rx, int *y, int ly, int ry, int n);
long long power10(int exp);
int BinSearch(int v[], int l, int r, int k);
void reverse_print(char *s);
void Hanoi(int n, int src, int dest);
void ruler(int l, int r, int h);


int main() {
    printf("%d", fattoriale(5));
}


int fattoriale(int n) {
    if (n == 0)
        return 1;
    return n * fattoriale(n-1);
}

int fibonacci(int n) {
    if (n == 0)
        return n;
    return fibonacci(n-2) + fibonacci(n-1);
}

int gcd1(int x, int y) {
    if(x == y)
        return x;
    if (x > y)
        return gcd1(x-y, y);
    return gcd1(x, y-x);
}

int gcd2(int x, int y) {
    int t;
    if (x < y) {
        t = x;
        x = y; 
        y = t;
    }
    if(y == 0)
        return x;
    return gcd2(y, x % y);
}


long prod(int *x,int lx,int rx,int *y,int ly,int ry,int n) {long t1, t2, t3;
    if (n == 1)
        return (x[lx]*y[ly]);
    t1 = prod(x, lx, (lx+rx)/2, y, ly, (ly+ry)/2, n/2);
    t2 = prod(x, lx, (lx+rx)/2, y, ly+n/2, ry, n/2)
            + prod(x, lx+n/2, rx, y, ly, (ly+ry)/2, n/2);
    //con Karatsuba: xs*yd + xd*ys = xs*ys + xd*yd – (xs-xd)*(ys-yd) = t1 + t3 - (xs-xd)*(ys-yd)
    t3 = prod(x, lx+n/2, rx, y, ly + n/2, ry, n/2);
    return t1 * power10(n) + t2 * power10(n/2) + t3;
}
//HELPER
long long power10(int exp) {
    if (exp <= 0) return 1;
    return 10 * power10(exp - 1);
}


int BinSearch(int v[], int l, int r, int k) {
    int m;
    if (l > r)
        return -1;
    m = (l + r)/2;
    if (k == v[m])
        return (m);
    if (k < v[m])
        return BinSearch(v, l, m-1, k);
    return BinSearch(v, m+1, r, k);
}

void reverse_print(char *s) {
    if(*s == '\0')
        return;
    reverse_print(s+1);
    putchar(*s);
}


void Hanoi(int n, int src, int dest) {
    int aux;
    if (n == 1) {
        printf("src %d -> dest %d \n", src,dest);
        return;
    }
    aux = 3 - (src + dest);
    Hanoi(n-1, src, aux);
    printf("src %d -> dest %d \n", src, dest);
    Hanoi(n-1, aux, dest);
}


void ruler(int l, int r, int h) {
    int m, i;
    if (h == 0)
        return;
    m = (l + r)/2;
    ruler(l, m, h-1);
    mark(m, h);
    ruler(m, r, h-1);
}
//HELPER
void mark(int m, int h) {
    int i;
    printf("%d \t", m);
    for (i = 0; i < h; i++)
        printf("*");
        printf("\n");
}
