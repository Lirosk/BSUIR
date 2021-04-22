#include <iostream>
#include <conio.h>
#include <math.h>

int main()
{
	
	setlocale (0,"");
	
	float B,A;
	int M = 20;
	A = 0;
	B = 3.14159/2.;

	std::cout<<"\n\t 	x | y\n";
	
	for (float x = A; x >= A & x <= B; x += (B-A)/M)
		std::cout<<x<<"  \t|\t"<<sin(x)-cos(x)<<"\n";

	
	
	
getch();

return 0;
}



/*


int main()
{
	
	setlocale (0,"");
	
	float B,x,pi,y,A;
	int M = 20;
	A = 0;
	B = 3.14159/2;

	std::cout<<"\n 	x | y\n";
	
	for (int x = A;x>=A & x<=B; x+=(B-A)/M)
	{
		std::cout<<sin(x)-cos(x)<<" | "<<x<<'\n';
		
		
		
		
	}
	
	
	
	
	
	
	
	
getch();

return 0;
}


*/
