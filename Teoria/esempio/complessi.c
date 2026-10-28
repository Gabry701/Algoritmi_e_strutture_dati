#include <stdio.h>
#include <stdlib.h>
#include "complessi.h"

struct complex_s { double re, im; };


Complex newComplex(void) {
    Complex c;
    c = malloc(sizeof(*c));
    c->re = 0;
    c->im = 0;
    return c;
}

Complex newComplexWithValues(double re, double im) {
    Complex c;
    c = malloc(sizeof(*c));
    c->re = re;
    c->im = im;
    return c;
}

void deleteComplex(Complex c) {
    free(c);
}

void changeComplex(Complex c, double re, double im) {
    c->re = re;
    c->im = im;
}


double re(Complex c) {
    return c->re;
}
double im(Complex c) {
    return c->im;
}

Complex neg(Complex c) {
    Complex negC; 
    negC = malloc(sizeof(*c));
    negC->re = -c->re;
    negC->im = -c->im;
    return negC;
}

Complex conj(Complex c) {
    Complex conjC = newComplexWithValues(c->re, -c->im);
    return conjC;
}

Complex cprod(Complex c1, Complex c2) {
    Complex c;
    c = newComplex();
    c->re = c1->re*c2->re - c1->im*c2->im;
    c->im = c1->re*c2->im + c1->im*c2->re;
    return c;
}
Complex csub(Complex c1, Complex c2) {
    Complex c = newComplex();
    c->re = c1->re - c2->re;
    c->im = c1->im - c2->im;
    return c;
}

Complex csum(Complex c1, Complex c2) {
    Complex c = newComplex();
    c->re = c1->re + c2->re;
    c->im = c1->im + c2->im;
    return c;
}

Complex cdiv(Complex c1, Complex c2) {
    double a, b, c, d;
    if (c2->im == 0 && c2->re == 0) {
        printf("non si può dividere per 0");
        return newComplex();
    }
Complex quotC = newComplex();
    a = c1->re; b = c1->im;
    c = c2->re; d = c2->im;
    quotC->re = (a*c + b*d)/(c*c + d*d);
    quotC->im = (b*c-a*d)/(c*c + d*d);
    return quotC;
}

void printComplex(Complex c) {
    if (c->im == 0 && c->re == 0)
        printf("%d", 0);
    else if (c->im == 0)
        printf("%g", c->re);
    else if (c->re == 0)
        printf("%gi", c->im);
    else if (c->im > 0)
        printf("%g + %gi", c->re, c->im);
    else if (c->im < 0)
        printf("%g-%gi", c->re, -c->im);
}
