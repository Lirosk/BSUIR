#include <iostream>
#include <cmath>
#include <conio.h>

int main(){
	
	setlocale(0, "");
	std::cout<<"Hello, World!\n";
	
	float f,b,a,z;
	
	
	std::cout<<"\nВведите последовательно значения коэффициентов a, b, z\n";
	std::cin>>a>>b>>z;
	float x = (z<1)?(2+z):(powf(sin(z),2));
	(z<1)?std::cout<<"\nт.к. z < 1 — x = 2 + z\n":std::cout<<"\nт.к. z >= 1 — x = sin^2(z)\n";
	
	
	
Vvf:
	std::cout<<"""\nВыберите функцию f(x) \n1) f(x) = 2x\n2) f(x) = x^2\n3) f(x) = x/3\nВведите номер (1,2,3)\n""";
	char i = getch ();
	
	
	
	switch (i)
	{
		case '1':{ f=2*x;
			break;
		}
			
		case '2':{ f=x*x;
			break;
		}
			
		case '3':{ f=x/3;
			break;
		}
			
		default:{ std::cout<<"\n\nВыберите одну из предложенных функций\n";
			goto Vvf;
		}
			
	}
	
	
	
	float y = (2*a*f+b*cos(sqrt(fabs(x))))/(x*x+5);
	std::cout<<"y = "<<y<<'\n';
	
	
	if (i=='1')
	{
		std::cout<<"\nВычесления произвелись при f(x) = 2*x ";
	}
	
	else if (i=='2')
	{
		std::cout<<"\nВычесления произвелись при f(x) = x^2 ";
	}
	
	else
	{
		std::cout<<"\nВычесления произвелись при f(x) = x/3 ";
	}
	
	(z<1)?std::cout<<"\nи при x = 2 + z\n":std::cout<<"\nи при x = sin^2(z)\n";
	
	
	

getch();	
system("pause");
return 0;
}

