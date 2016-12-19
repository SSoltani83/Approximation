//This C++ Program demonstrates How some numerical integration methods work.
//It covers the Midpoint rule, the Trapezoidal rule and the Simpson's rule.
//It asks the user to enter the lower and upper bounds of integration and the maximum number of iteration allowed.
//It prints the results of each iteration or mesh.
#include<iostream>
#include<iomanip>
#include"Approximation.h"
#include<cmath>
using namespace std;

double fx(double);// Function prototype for the function to approximate

int main()
{
	//Declaration of variables
	double LowerBound;
	double UpperBound;
	double Tol_err= 5*pow(10,-7); //Tolerance error is fixed to 5*10^-7
	int Max_iteration;
	//Declaration of a pointer to a function
	double(*p)(double);
	
	//pointing the pointer to function that we would like to approximate under the integral
	p = fx;
	
	//input output statements for the user to enter the lower bound , the upper bound and the maximum number of iterations
	cout<<"THIS PROGRAM DEMONSTRATES HOW THE MIDPOINT,THE TRAPEZOIDAL AND SIMPSON'S RULES OF NUMERICAL APPROXIMATION WORK"<<endl;
	cout<<"\nPlease make sure that the function of which you would like to approximate the integral is hard coded in the main_source.cpp file!"<<endl;
	cout<<"Please enter the lower bound of integration: ";
	cin>>LowerBound;
	cout<<"Please enter the upper bound of integration: ";
	cin>>UpperBound;
	cout<<"Please enter the maximum number of iteration allowed: ";
	cin>>Max_iteration;
	cout<<"\n\n"<<endl;
	
	//Calling the functions Midpoint,Trapez and Simpson
	Midpoint(LowerBound,UpperBound,Tol_err,Max_iteration,fx);
	cout<<"\n\n\n"<<endl;
	Trapez(LowerBound,UpperBound,Tol_err,Max_iteration,fx);
	cout<<"\n\n\n"<<endl;
	Simpson(LowerBound,UpperBound,Tol_err,Max_iteration,fx);
	
	system("pause");
	return 0;
};
// This is the function of which I would like to approximate the integral
double fx(double x){

	return exp(-(x*x));
}