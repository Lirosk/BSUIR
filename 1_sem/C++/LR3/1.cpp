#include <iostream>
#include <conio.h>

int main()
{
	
	int i,N,a,b;
	i=1; 
	N=0;
	while (i<=30)
	
	{   
	
	
		if (i%2==0)
		{
			a = i/2;
			b = i*i*i;
		}
			
		else
		{
			a = i;
			b = i*i;
		}


		N += (a-b)*(a-b);
		i+=1;

	}

	std::cout<<"\nN = "<<N<<'\n';


getch();	
system ("pause");
return 0;	
}
