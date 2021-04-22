#include <iostream>
#include <cmath>

/*
float leftrect(float a, float b, int n)
{
	float h = (b - a)/(n+1), S = 0;
	for (double x = a; x < b; x += h)
	{
		S += (sqrt(0.5*x + 2) / (sqrt(2*x*x + 1) + 0.8) );
	}
	return S*h;
}


float rightrect(float a, float b, int n)
{
	float h = (b - a)/(n+1), S = 0;
	for (double x = a + h; x <= b; x += h)
	{
		S += (sqrt(0.5*x + 2)/ (sqrt(2*x*x + 1) + 0.8) );
	}
	return S*h;
}


double centralrect(double a, float b, int n)
{
	double h = (b - a)/(n+1), S = 0;
	for (double x = a + h/2. ; x < b; x += h)
	{
		S += (sqrt(0.5*x + 2)/ (sqrt(2*x*x + 1) + 0.8) );
	}
	return S*h;
}


double trap(double a, double b, int n)
{
	double h = (b - a)/(n+1), S = 0;
	S += ((sqrt(0.5*a + 2)/ (sqrt(2*a*a + 1) + 0.8) ) + (sqrt(0.5*b + 2)/ (sqrt(2*b*b + 1) + 0.8) ))/2;
	for (double x = a + h + h/2. ; x < b; x += h)
	{
		S += (sqrt(0.5*x + 2)/ (sqrt(2*x*x + 1) + 0.8) );
	}
	return S*h;
}
*/

double f1(double x)
{
	return sqrt(0.5*x + 2)/(sqrt(2*x*x + 1) + 0.8) ;
}

double f2(double x)
{
	return cos(0.8*x + 1.2)/(1.5+sin(x*x + 0.6));
}

double f3(double x)
{
	return 1/sqrt(x*x + 3.2);
}

double f4(double x)
{
	return (x+1)*sin(x);
}

double leftrect(double a, double b, int n, double (*func)(double))
{
	double h = fabs(a-b)/(n+1), S = 0, x;
	for (int i = 0; i < n; i++)
	{
		x = a + i*h;
		S += func(x);
	}
	return fabs(S*h);
}

double rightrect (double a, double b, int n, double (*func)(double))
{
	double h = fabs(a-b)/(n+1), S = 0, x;
	for (int i = 1; i <= n; i++)
	{
		x = a + i*h;
		S += func(x);
	}
	return fabs(S*h);
}

double centralrect (double a, double b, int n, double (*func)(double))
{
	double h = fabs(a-b)/(n+1), S = 0, x;
	for (int i = 0; i < n; i++)
	{
		x = a + i*h +h/2;
		S += func(x);
	}
	return fabs(S*h);
}

double trap (double a, double b, int n, double (*func)(double))
{
	double h = fabs(a-b)/(n+1), S = 0, x;
	S += (func(a) + func(b))/2;	
	for (int i = 1; i < n; i++)
	{
		x = a + i*h;
		S += func(x);
	}
	return fabs(S*h);
}



int main()
{
	
	int n;
	float a, b;
	printf("Enter a & b for 1st func: \n");
	std::cin>>a>>b;
	printf("Enter the number of equal steps: ");
	std::cin>>n;
		
	printf("\n\nFor 1st func: \n");
	std::cout<<"\nBy left rect metod: "<<leftrect(a,b,n,f1);
	std::cout<<"\nBy right rect metod: "<<rightrect(a,b,n,f1);
	std::cout<<"\nBy central rect metod: "<<centralrect(a,b,n,f1);
	std::cout<<"\nBy trap metod: "<<trap(a,b,n,f1);	
	
	printf("\n\nEnter a & b for 2nd func: \n");
	std::cin>>a>>b;
	printf("Enter the number of equal steps: ");
	std::cin>>n;
	
	printf("\n\nFor 2nd func: \n");
	std::cout<<"\nBy left rect metod: "<<leftrect(a,b,n,f2);
	std::cout<<"\nBy right rect metod: "<<rightrect(a,b,n,f2);
	std::cout<<"\nBy central rect metod: "<<centralrect(a,b,n,f2);
	std::cout<<"\nBy trap metod: "<<trap(a,b,n,f2);
	
	printf("\n\nEnter a & b for 3rd func: \n");
	std::cin>>a>>b;
	printf("Enter the number of equal steps: ");
	std::cin>>n;
	
	printf("\n\nFor 3rd func: \n");
	std::cout<<"\nBy left rect metod: "<<leftrect(a,b,n,f3);
	std::cout<<"\nBy right rect metod: "<<rightrect(a,b,n,f3);
	std::cout<<"\nBy central rect metod: "<<centralrect(a,b,n,f3);
	std::cout<<"\nBy trap metod: "<<trap(a,b,n,f3);
	
	printf("\n\nEnter a & b for 4th func: \n");
	std::cin>>a>>b;
	printf("Enter the number of equal steps: ");
	std::cin>>n;
	
	printf("\n\nFor 4th func: \n");
	std::cout<<"\nBy left rect metod: "<<leftrect(a,b,n,f4);
	std::cout<<"\nBy right rect metod: "<<rightrect(a,b,n,f4);
	std::cout<<"\nBy central rect metod: "<<centralrect(a,b,n,f4);
	std::cout<<"\nBy trap metod: "<<trap(a,b,n,f4);
	
	
	return 0;
}
