#include <stdio.h>

int fattoriale(int n) {
    if (n == 0)
        return 1;
    return n * fattoriale(n-1);
}

int fibonacci(int n) {
    if (n == 0)
        return n;
    return fibonacci(n-2) + fibonacci(n-1)
}

int main() {
    printf("%d", fattoriale(5));
}