//This is a header file named Approximation.h that contains the three function prototypes: Midpoint, Trapezoidal and Simpson
//Conditional Compilation to avoid infinite inclusion of the header file
#ifndef APPROXIMATION_H
#define APPROXIMATION_H
//Function's prototypes for the approximation methods: each function is a void function that takes three doubles, one integer and one function pointer as argument.
void Midpoint(double, double, double,int,double(*functocall)(double));
void Trapez(double, double, double,int, double(*functocall)(double));
void Simpson(double, double, double,int, double(*functocall)(double));

#endif