#include <math.h>
#include <iostream>
#include <conio.h>
int main(){
	
	setlocale (0,"");
	std::cout<<"Hello, World!\n";
	
	float x,y,s;
	std::cout<<"Введите последовательно x, y\n";
	std::cin>>x>>y;
	
	
	if (x/y>0)
	{
		s = log(x) + powf(fabs(y),(1./3));
		std::cout<<"\ns = "<<s;
		std::cout<<"\nВычесления произвелись по формуле s = ln(x) + (|y|)^1/3\n";
	}
	
	else if (x/y<0)
	{
		s = log(fabs(x/y))*powf((x+y),3);
		std::cout<<"\ns = "<<s;
		std::cout<<"\nВычесления произвелись по формуле s = ln(|x/y|)*(x+y)^3\n";
	}
	
	else
	{
		s = powf((x*x + y),3);
		std::cout<<"\ns = "<<s;
		std::cout<<"\nВычесления произвелись по формуле s = (x*x + y)^3)\n";
	}
	
	

	
	
	
	
getch();
system ("pause");
return 0;
}










