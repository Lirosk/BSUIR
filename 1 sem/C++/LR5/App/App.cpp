#include <iostream>
#include <cmath>

double leftrect(double a, double b, int n)
{
	double h = (b - a) / (n + 1), S = 0;
	for (int x = a; x < b; x += h)
	{
		S += (sqrt(0.5 * x + 2) / (sqrt(2 * x * x + 1) + 0.8));
	}
	return S * h;
}

double rightrect(double a, double b, int n)
{
	double h = (b - a) / (n + 1), S = 0;
	for (int x = a + h; x <= b; x += h)
	{
		S += (sqrt(0.5 * x + 2) / (sqrt(2 * x * x + 1) + 0.8));
	}
	return S * h;
}

double centralrect(double a, double b, int n)
{
	double h = (b - a) / (n + 1), S = 0;
	for (int x = a + h / 2.; x < b; x += h)
	{
		S += (sqrt(0.5 * x + 2) / (sqrt(2 * x * x + 1) + 0.8));
	}
	return S * h;
}

double trap(double a, double b, int n)
{
	double h = (b - a) / (n + 1), S = 0;
	S += ((sqrt(0.5 * a + 2) / (sqrt(2 * a * a + 1) + 0.8)) + (sqrt(0.5 * b + 2) / (sqrt(2 * b * b + 1) + 0.8))) / 2;
	for (int x = a + h + h / 2.; x < b; x += h)
	{
		S += (sqrt(0.5 * x + 2) / (sqrt(2 * x * x + 1) + 0.8));
	}
	return S * h;
}


int main()
{

	int n;
	double a, b;
	printf("Enter a & b: \n");
	std::cin >> a >> b;
	printf("Enter the number of equal steps: ");
	std::cin >> n;

	std::cout << "By left rect metod: " << leftrect(a, b, n);
	std::cout << "By left right metod: " << rightrect(a, b, n);
	std::cout << "By central rect metod: " << centralrect(a, b, n);
	std::cout << "By trap metod: " << trap(a, b, n);


	return 0;
}
