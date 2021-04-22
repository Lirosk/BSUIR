#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{

	setlocale (0,"");
	std::cout<<"Hello, World!\n";
	
	float R;
	std::cout<<"¬ведите R\n";
	std::cin>>R;


	int k = round(R*sin(3*R));
	
	switch (k%5)
	{
		case 0:
			{
				std::cout<<"z = "<<R  + sin(R/3)<<'\n';
				break;
			}
			
		case 1:
			{
				std::cout<<"z = "<<tan(R+2)<<'\n';
				break;
			}
			
		case 3:
			{
				std::cout<<"z = "<<log(R+5)/3.7<<'\n';
				break;
			}		
		default:
			{
				std::cout<<"z = "<<exp(R-1)+atan(R)<<'\n';
			}
				
	}



system ("pause");
return 0;
}
