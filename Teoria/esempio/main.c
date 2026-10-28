#include <stdio.h>
#include "complessi.h"


int main() {
    Complex a, b, sum;
    a = newComplexWithValues(5, 6);
    b = newComplex();
    printComplex(a);
    printf("\n");
    printComplex(b);
    printf("\n");
    changeComplex(b, 4, 5);
    sum = csum(a,b);
    printf("\n");
    printComplex(sum);
    deleteComplex(a);
    deleteComplex(b);
    deleteComplex(sum);
}