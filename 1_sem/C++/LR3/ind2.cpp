#include <iostream>
#include <math.h>
#include <conio.h>

int main()
	{
		setlocale(0,"");
		
		int parts;
		std::cout<<"На сколько целых частей разделить отрезок [2 ; 4]?\n";
		std::cin>>parts;
		float step = 2./parts;
		float min,minx,y,x;
		
		min = 999999;
		for (int i = 0; i <= parts; i++)
		
			{
				
				std::cout<<"i = "<<i;
				std::cout<<"\tstep = "<<step;
		 		x = 2. + step*i;
		 		y = log(x) + 3*tan(x) + sqrt(x);
		 		std::cout<<"\ty = "<<y<<"\tпри x = \t"<<x<<'\n';
		 		y = fabs(y);
				if (y < min)
				
		 			{
		 				min = y;
		 				minx = x;
		 			}
		 			
			}
		
		std::cout<<"\nНаименьшее значение y (по модулю) =\t"<<min<<"\t при x = \t"<<minx;
		
		getch();
		return 0;		
	}

