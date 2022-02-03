#include <iostream>
#include <math.h>
#include <conio.h>

int main()
	{
		
		setlocale (0,"");
		
		float x, h=0.1;
		int i=0;
		
		while (x < 1) 
		{
			
			x = 0.4 + i*h;
			std::cout<<"f(x) = "<<1+log(x)*log(x)<<"\tпри x =\t"<<x<<'\n';
			i += 1;
				
		}
				
		getch();
		return 0;		
	}

