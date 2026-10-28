#ifndef COMPLESSI_H
#define COMPLESSI_H


typedef struct complex_s *Complex;

Complex newComplex(void);
Complex newComplexWithValues(double re, double im);
void deleteComplex(Complex c);
void changeComplex(Complex c, double re, double im);


double re(Complex c);
double im(Complex c);

Complex neg(Complex c);
Complex conj(Complex c);

Complex csum(Complex c1, Complex c2);
Complex csub(Complex c1, Complex c2);
Complex cprod(Complex c1, Complex c2);
Complex cdiv(Complex c1, Complex c2);

void printComplex(Complex c);



#endif