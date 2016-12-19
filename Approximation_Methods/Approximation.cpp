//Functions used to approximate the area under the curve of a mathematical function
//The use of these functions require you to set a function pointer and point it to the function you would like to evaluate in the main source file.
//the inputs of these function are:
//a=the left end point of the interval(lower bound of integration)
//b=the right end point of the interval (upper bound of integration)
//tol=the tollerance level of an error between two consecutive iterations
//Max_Iter a safety feature designed to exit the loop if a certain number of iteration is reached
//(*functocall)=this is a pointer function pointing to the function you would like to evaluate
#include<iostream>
#include<cstdlib>
#include<cmath>
#include"Approximation.h"
#include<iomanip>


using namespace std;


//Implementation of the Midpoint rule approximation
//we will calculate the aspproximation with 4 intervals first, and store the value in I_midold, then we will double the number of intervals (n=8) and store the new value in I_midnew.
//if the level of tolerance is met |I_midnew-I_midold|<tolerance err we stop. If not, we set I_midold=I_midnew; I_midnew=0 and double the number of partitions n=2*n;calculate the new value of I_midnew.
//we repeat the same process until either the tolerance level is met or we reach the maximum number of Iterations allowed by the user. 
void Midpoint(double a, double b, double tol,int Max_Iter, double(*functocall)(double))
{
	//Declaration of variables
	int n = 4;// We start by spliting the interval [a,b] to 4 partitions only
	double h = (b - a) / n;// h determines the width of each partition n
	double I_midOld = 0;
	double I_midNew = 0;
	int Number_of_iterations=0;
	double Err;// This double variable will be used to store the absolute value of (I_midnew-I_midold)

	//Output statements of the header
	cout << left << setw(15) << setfill(' ') << "# of part n";
	cout << left << setw(25) << setfill(' ') << "Approx Value";
	cout << left << setw(25) << setfill(' ') << "Toll Err" << endl;

	
	//Implementation of the Midpoint rule I_Midpoint= h* Σf(xi) 
	// This loop calculates the sum of all F(xi) where xi is the x coordinate of the midpoint of each partition n. xi=a+h*(i-0.5) and F() is the function under the integral
	for (int i = 1; i <= n; i++)
	{
		I_midOld = I_midOld + (*functocall)(a + (i - 0.5)*h);
	}
	I_midOld = I_midOld * h;// Final result for the midopoint approximation with 4 intervals
	Number_of_iterations++;// incrementing the number of iteration by 1
	
	
	//Output statements of the first I_midpoint approximation results when n=4
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << fixed << setprecision(15) << setw(25) << I_midOld;
	cout << left << setw(25) << setfill(' ') << "N/A" << endl;
	
	//Calclculation of I_midnew using the same logic as above but n=8  partitions instead of 4
	n = n*2; 
	h = (b - a) / n; // we need to redefine the width of each partition h since the number of partition n has changed
	
	//Implementation of the Midpoint rule I_Midpoint= h* Σf(xi) with n=8 
	// This loop calculates the sum of all F(xi) where xi is the x coordinate of the midpoint of each partition n. xi=a+h*(i-0.5) and F() is the function under the integral
	for (int i = 1; i <= n; i++)
	{
		I_midNew = I_midNew + (*functocall)(a + (i - 0.5)*h);
	}
	I_midNew = h*I_midNew;// Final result for midpoint approximation with n=8
	//Calculating the error between I_midNew and I_midOld for n=4 and 8
	Err = abs(I_midNew - I_midOld);
	Number_of_iterations++;//incrementing the number of iteration by 1
	
	//Output statements of the second I_midpoint approximation results when n=8
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << setprecision(15) << setw(25) << setfill(' ') << I_midNew;
	cout << left << setprecision(15) << Err << endl;

	//We follow the same logic as above but we use a while loop to double the number of intervals each time until |I_midnew-Imidold| is less than or equal our tolerance level.
	while (Err > tol)
	{  
		// If the number of iteration reaches the number of maximum allowed iteration by user, a statement is printed and we break from the loop
		if (Number_of_iterations==Max_Iter)
		{
			cout<<"\n\nThe midpoint integration method converges to "<<I_midNew<<" by reaching the maximum number of iteration allowed by the user!\a\n"<<endl;
			break;
		}
		I_midOld = I_midNew;// we assign I_midnew to I_midold
		I_midNew = 0;//we set I_midnew=0
		n = 2 * n;// double the number of partitions
		h = (b - a) / n;//redefine the width of each interval
		// This loop calculates the sum of all F(xi) where xi is the x coordinate of the midpoint of each partition n. xi=a+h*(i-0.5) and F() is the function under the integral
		for (int i = 1; i <= n; i++)
		{
			I_midNew = I_midNew + (*functocall)(a + (i - 0.5)*h);
		}
		
		I_midNew = I_midNew*h;// Final result for midpoint approximation with n partitions
		Err = abs(I_midNew - I_midOld);//redefining the new error between the las two iterations
		Number_of_iterations++;//Incrementing the number of iteration
		
		// Output statements of the last iteration
		cout << left << fixed << setw(15) << setfill(' ') << n;
		cout << left <<setprecision(15) << setw(25) << I_midNew;
		cout << left <<setprecision(15) <<setfill(' ') << Err << endl;
	}
	//Output of the result if number of iterations is less than Max_iter or (number of iteration equal to Max_iter and the error is less than tolerance error allowed)
	if((Number_of_iterations< Max_Iter)||(Number_of_iterations==Max_Iter && Err<tol ))
	{
	cout<<"\n\nThe midpoint approximation method converges to "<<I_midNew<<" after "<<Number_of_iterations<<" mesh refinements for "<<n<<" intervals and an error of "<<Err<<" between two consecutive iterations!\n"<<endl;
	}
	
}


//Implementation of the Trapezoidal rule approximation
//we will calculate the aspproximation with 4 intervals first, and store the value in I_trapezOld, then we will double the number of intervals (n=8) run the calculations and store the new value in I_trapezNew.
//if the level of tolerance is met |I_trapezNew-I_trapezOld|<tolerance err we stop. If not, we set I_trapezOld=I_trapezNew; I_trapezNew=0 and double the number of partitions n=2*n;calculate new value of I_trapezNew.
//we repeat the same process until either the tolerance level is met or we reach the maximum number of Iterations allowed by the user. 

void Trapez(double a, double b, double tol,int Max_Iter, double(*functocall)(double)){
	
	//Declaration of variables
	int n = 4;// We start by spliting the interval [a,b] to 4 partitions only
	double h = (b - a) / n;// h determines the width of each partition n
	double I_trapezOld = 0;
	double I_trapezNew = 0;
	int Number_of_iterations=0;
	double Err;

	//Output statements for the header
	cout << left << setw(15) << setfill(' ') << "# of part n";
	cout << left << setw(25) << setfill(' ') << "Approx Value";
	cout << left << setw(25) << setfill(' ') << "Toll Err"<<endl;
	
	//Implementation of the Trapezoidal rule I_Trapez= h/2* (F(a)+F(b)) + h * Σ F(a+i*h) . The last sum is from i=1 to i=n-1.
	// This loop calculates the sum of all F(ai) where ai=a+i*h and F() is the function under the integral
	for (int i = 1; i <= (n - 1); i++)
	{
		I_trapezOld = I_trapezOld + (*functocall)(a + i*h);
	}
	I_trapezOld = I_trapezOld*h + ((*functocall)(a)+(*functocall)(b))*(h / 2);// final result for Trapezoidal approximation for n=4
	Number_of_iterations++;//Incrementing the number of iteration by 1
	
	//Output of the first Trapezoidal approximation result for n=4
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << setprecision(15) << setw(25) << setfill(' ') << I_trapezOld;
	cout << left << setw(25) << setfill(' ') << "N/A" << endl;
	
	//Calclculation of I_Trapez using the same logic as above but n=8 partitions instead of 4
	n = 2 * n;// doubling the number of partitions
	h = (b - a) / n;// redefining the width of each partition
	
	//Implementation of the Trapezoidal rule I_Trapez= h/2* (F(a)+F(b)) + h * Σ F(a+i*h) . The last sum is from i=1 to i=n-1 for n=8.
	// This loop calculates the sum of all F(ai) where ai=a+i*h and F() is the function under the integral
	for (int i = 1; i <= (n - 1); i++)
	{
		I_trapezNew = I_trapezNew + (*functocall)(a + i*h);
	}
	I_trapezNew = I_trapezNew*h + ((*functocall)(a)+(*functocall)(b))*(h / 2);// Final result for Trapezoidal approximation for n=8 intervals
	Number_of_iterations++;//Incrementing the number of iterations by 1
	
	//Calculating the error between I_trapezOld and I_trapezNew for n=4 and 8
	Err = abs(I_trapezNew - I_trapezOld);
	
	//Output statements of the second Trapezoidal approximation results when n=8
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << setprecision(15) << setw(25) << setfill(' ') << I_trapezNew;
	cout << left << setprecision(15) << setfill(' ') << Err << endl;
	
	// Using the while loop to keep calculating the approximation untill Error is less than or equal our tolerance level or we reach the maximum number of iteration allowed by the user
	while (Err > tol)
	{
		// If the number of iteration reaches the number of maximum allowed iteration by user, a statement is printed and we break from the loop
		if (Number_of_iterations==Max_Iter)
		{
			cout<<"\n\nThe Trapezoidal integration method converges to "<<I_trapezNew<<" by reaching the maximum number of iteration allowed by the user!\a\n"<<endl;
			break;
		}
		n = 2 * n;// double the number of partitions
		h = (b - a) / n;//redefine the width of each partition
		I_trapezOld = I_trapezNew;// set I_trapezold equal to the new Trapezoidal approximation I_trapeznew
		I_trapezNew = 0;// set I_trapeznew=0;
		
		//Implementation of the Trapezoidal rule I_Trapez= h/2* (F(a)+F(b)) + h * Σ F(a+i*h) . The last sum is from i=1 to i=n-1 
		// This loop calculates the sum of all F(ai) where ai=a+i*h and F() is the function under the integral
		for (int i = 1; i <= (n - 1); i++)
		{
			I_trapezNew = I_trapezNew + (*functocall)(a + i*h);
		}
		I_trapezNew = I_trapezNew*h + ((*functocall)(a)+(*functocall)(b))*(h / 2);// Final result of the ith iteration
		
		Err = abs(I_trapezNew - I_trapezOld);//redefining the new error between two consecutive iterations
		Number_of_iterations++;// Incrementing the number of iteration by 1
		//Output statements for the last iteration
		cout << left << fixed << setw(15) << setfill(' ') << n;
		cout << left << setprecision(15) << setw(25) << I_trapezNew;
		cout << left << setprecision(15) << setfill(' ') << Err << endl;
	}
	//Output of the result if number of iterations is less than Max_iter or (number of iteration equal to Max_iter and the error is less than tolerance error allowed)
	if((Number_of_iterations< Max_Iter)||(Number_of_iterations==Max_Iter && Err<tol))
	{
	cout<<"\n\nThe Trapezoidal approximation method converges to "<<I_trapezNew<<" after "<<Number_of_iterations<<" mesh refinements for "<<n<<" intervals and an error of "<<Err<<" between two consecutive iterations!\n"<<endl;
	}
	
}


//Implementation of the Simpson's rule of approximation
//we will calculate the aspproximation with 4 intervals first, and store the value in IsimpOld, then we will double the number of intervals (n=8) and store the new value in I_simpNew.
//if the level of tolerance is met |I_midnew-I_midold|<tolerance err we stop. If not, we set I_simpOld=I_simpNew double; I_simpNew=0 and double the number of partitions n=2*n;calculate new value of I_simpNew.
//we repeat the same process until either the tolerance level is met or we reach the maximum number of Iterations allowed by the user. 

void Simpson(double a, double b, double tol,int Max_Iter, double(*functocall)(double))
{
	//Deaclaration of variables
	int n = 4;// We start by spliting the interval [a,b] to 4 partitions only
	double h=(b-a)/n;// h determines the width of each partition n
	double I_simpOld = 0;
	double I_simpNew = 0;
	int Number_of_iterations=0;
	double Err; //Error

	//Output of the header
	cout << left << setw(15) << setfill(' ') << "# of part n";
	cout << left << setw(25) << setfill(' ') << "Approx Value";
	cout << left << setw(25) << setfill(' ') << "Toll Err" << endl;
	
	//Implementation of the simpson's rule of approximation. I_simp= [(F(a)+F(b))*(h/6)]+ [(h/3)* ΣF(ai)] + [(2/3*h)*Σf(xi)]. where ΣF(ai) goes from 1 to n-1 and ΣF(xi) goes from i=1 to i=n
	// and xi=a+(i-0.5)*h.
	for (int i = 1; i <= n; i++)
	{
		I_simpOld = I_simpOld + ((*functocall)(a + (i - 0.5)*h))*(2 * h / 3) + (h / 3)*((*functocall)(a + i*h));
	}
	I_simpOld = I_simpOld + ((*functocall)(a)+(*functocall)(b))*(h / 6) - (h / 3)*(*functocall)(b);// I substracted F(b) at the end to avoid making a double loop. WE made 1 loop from n=1 to n and not n-1
	Number_of_iterations++;//Incrementing the number of iteration by 1
	//Output of the first simpson's rule approximation result for n=4
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << setprecision(15) << setw(25) << I_simpOld;
	cout << left << setw(25) << setfill(' ') << "N/A" << endl;
	
	//Calclculation of I_simp using the same logic as above but n=8 partitions instead of 4
	n = 2 * n;//doubling the number of intervals n=8 now
	h = (b - a) / n;//redefining h the width of each interval 
	
	//Implementation of the simpson's rule of approximation. I_simp= [(F(a)+F(b))*(h/6)]+ [(h/3)* ΣF(ai)] + [(2/3*h)*Σf(xi)]. where ΣF(ai) goes from 1 to n-1 and ΣF(xi) goes from i=1 to i=n
	// and xi=a+(i-0.5)*h. for n=8
	for (int i = 1; i <= n; i++)
	{
		I_simpNew = I_simpNew + (2 * h / 3)*((*functocall)(a + (i-0.5)*h)) + (h / 3)*((*functocall)(a + i*h));
	}

	I_simpNew = I_simpNew + ((*functocall)(a)+(*functocall)(b))*(h / 6) - (h / 3)*(*functocall)(b);// I substracted F(b) at the end to avoid making a double loop. WE made 1 loop from n=1 to n and not n-1
	Number_of_iterations++;//incrementing the number of iteration by 1
	//Calculating the error between I_simpNew and I_simpOld for n=4 and 8
	Err = abs(I_simpOld - I_simpNew);
	//Output of the second result of simpson's rule of approximation method for n=8
	cout << left << fixed << setw(15) << setfill(' ') << n;
	cout << left << setprecision(15) << setw(25) << I_simpNew;
	cout << left << setprecision(15) << setfill(' ') << Err << endl;
	
	// Using the while loop to keep calculating the approximation untill Error< our tollerance level or we reach the maximum number of iteration allowed by the user
	while (Err > tol)
	{
		if(Number_of_iterations==Max_Iter)
		{
			cout<<"\n\nThe Simpson's integration method converges to "<<I_simpNew<<" by reaching the maximum number of iteration allowed by the user!\a\n"<<endl;
			break;
		}
		n = 2 * n;//doubling the number of partitions	
		h = (b - a) / n;//Redefining h which is the wdth of each partition
		I_simpOld = I_simpNew;// set I_simpOld=I_simpNew
		I_simpNew = 0;// set I_simpNew mequal to 0
		
		
		//Implementation of the simpson's rule of approximation. I_simp= [(F(a)+F(b))*(h/6)]+ [(h/3)* ΣF(ai)] + [(2/3*h)*Σf(xi)]. where ΣF(ai) goes from 1 to n-1 and ΣF(xi) goes from i=1 to i=n
		// and xi=a+(i-0.5)*h. for n=8
		for (int i = 1; i <= n; i++)
		{
			I_simpNew = I_simpNew + (2 * h / 3)*((*functocall)(a + (i - 0.5)*h)) + (h / 3)*((*functocall)(a + h*i));
		}
		I_simpNew = I_simpNew + ((*functocall)(a)+(*functocall)(b))*(h / 6) - (h / 3)*(*functocall)(b);// I substracted F(b) at the end to avoid making a double loop. WE made 1 loop from n=1 to n and not n-1
		
		Err = abs(I_simpOld - I_simpNew);// redefining the error between two consecutive iterations
		Number_of_iterations++;// Incrementing the number of iteration by 1
		//Outputing the result of the last Iteration
		cout << left << fixed << setw(15) << setfill(' ') << n;
		cout << left << setprecision(15) << setw(25) << I_simpNew;
		cout << left << setprecision(15) << setfill(' ') << Err << endl;
	}
	
	//Output of the result if number of iterations is less than Max_iter or (number of iteration equal to Max_iter and the error is less than tolerance error allowed)
	if((Number_of_iterations< Max_Iter)||(Number_of_iterations==Max_Iter && Err<tol))
	{
	cout<<"\n\nSimpson's approximation method converges to "<<I_simpNew<<" after "<<Number_of_iterations<<" mesh refinements for "<<n<<" intervals and an error of "<<Err<<" between two consecutive iterations!\n"<<endl;
	}
	
}


