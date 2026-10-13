#include <stdio.h>
#include <stdlib.h>

/*
GCD:
gcd(a,b) = 
if (a, b %2 ==0) 2*gcd(a/2, b/2);
if (a%2 != 0, b%2 == 0) gcd(a,b/2);
if (a, b %2 != 0) gcd((a-b)/2, b)
per simmetria:
if (a%2 == 0, b%2 != 1) gcd(a/2, b)
condizione di terminazione: se a o b == 0;


*/

int gcd(int a, int b);




int main(int argc, char *argv[]) {
    int x, y;
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    printf("Massimo comune divisore tra %d e %d: %d", x, y, gcd(x, y));
}    


int gcd(int a, int b) {
    int t;
    if (a < b) {
        t = a;
        a = b;
        b = t;
    }
    if (a == 0) return b;
    if (b == 0) return a;

    if (a % 2 == 0 && b %2 == 0) 
        return 2*gcd(a/2,b/2);
    if (a % 2 == 0 && b % 2 != 0)
        return gcd(a/2, b);
    if (a % 2 != 0 && b % 2 == 0)
        return gcd(a, b/2);
    else
        return gcd((a-b)/2, b);
}
