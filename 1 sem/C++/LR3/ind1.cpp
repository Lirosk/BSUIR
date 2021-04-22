#include <iostream>
#include <conio.h>
#include <math.h>

int main()
{
	
	setlocale (0,"");
	
	int n;
	float x;
	int fact;
	float Y,S = 1;
	
	std::cout<<"\nВведите кол-во элементов ряда n: ", std::cin>>n;

	x = 0;
while (x != 1)

	{

TryAgain:
		std::cout<<"\nВведите x на отрезке [0.1 ; 1]: ", std::cin>>x;
		if (x<0.1 | x>1) goto TryAgain;
	
		for (int i = 1; i <= n-1; i++)
			{
		
				fact = 1;
				for (int f = 1; f <= i; f++)
					{
				
						fact *= f;
		
					}
					
				S += powf(x, 2*i)/fact/pow(2,i);
		
			}

		Y = (exp(x)+exp(-x))/2;
		std::cout<<"S = "<<S<<"\nY = "<<Y<<"\nY отличается от S на "<<fabs(Y-S)/Y*100<<"% ("<<Y-S<<")\n";

	}


getch();

return 0;
}

