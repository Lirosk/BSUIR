#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{
	
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	float x1,x2,m,k,L;
	std::cout<<"¬ведите последовательно x1, x2, m\n";
	std::cin>>x1>>x2>>m;
	k=powf(cos(powf(x1,2)),3)+powf(sin(powf(x2,3)),2);
	
	if (k<1)
	{
		L=powf(k,3)+powf(m,0.2);
	}
	
	else
	{
		L=powf(k,2)-exp(m);
	}
	
	//L = (k<1)?powf(k,3)+powf(m,0.2):powf(k,2)-exp(m);
	std::cout<<"L ="<<L<<"\n";
	
getch();	
system ("pause");
return 0;
}

