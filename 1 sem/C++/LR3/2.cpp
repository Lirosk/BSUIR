#include <iostream>
#include <conio.h>
#include <math.h>

int main()
{
	float dn,Sum,e;
	e = 0.001;
	Sum = 0;
	int n = 1;
	
	do 	
	{
		
		Sum += dn = 1./pow(2,n) + 1./pow(3,n);
		n+=1;
		
	} while (dn >= e);
	
	
	std::cout<<"\nSum(dn) = "<<Sum<<'\n';
	
	
	
	

getch();	
system ("pause");
return 0;	
}
