#include <math.h>
#include <iostream>
#include <conio.h>
int main(){
	
	setlocale (0,"");
	std::cout<<"Hello, World!\n";
	
	float x,y,s;
	std::cout<<"������� ��������������� x, y\n";
	std::cin>>x>>y;
	
	
	if (x/y>0)
	{
		s = log(x) + powf(fabs(y),(1./3));
		std::cout<<"\ns = "<<s;
		std::cout<<"\n���������� ����������� �� ������� s = ln(x) + (|y|)^1/3\n";
	}
	
	else if (x/y<0)
	{
		s = log(fabs(x/y))*powf((x+y),3);
		std::cout<<"\ns = "<<s;
		std::cout<<"\n���������� ����������� �� ������� s = ln(|x/y|)*(x+y)^3\n";
	}
	
	else
	{
		s = powf((x*x + y),3);
		std::cout<<"\ns = "<<s;
		std::cout<<"\n���������� ����������� �� ������� s = (x*x + y)^3)\n";
	}
	
	

	
	
	
	
getch();
system ("pause");
return 0;
}










