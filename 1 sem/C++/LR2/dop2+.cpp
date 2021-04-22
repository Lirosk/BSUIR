#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{

	setlocale (0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b,c,x,y;
	std::cout<<"Введите последовательно размеры отверстия x и y\n";
	std::cin>>x>>y;
	std::cout<<"Введите последовательно измерения кирпича a, b и c\n";
	std::cin>>a>>b>>c;
	
	
	if ((x > a & y > b) | (x > b & y > a))
	{
		std::cout<<"Кирпич проходит через отверстие сторонами a и b\n";
	}
	
	else if ((x > c & y > a) | (x > a & y > c))
	{
		std::cout<<"Кирпич проходит через отверстие сторонами a и c\n";
	}
	
	else if ((x > c & y > b) | ( x > b & y > c))
	{
		std::cout<<"Кирпич проходит через отверстие сторонами c и b\n";
	}
	
	else
	{
		std::cout<<"Кирпич не пролезет через отверстие с данными сторонами\n";
	}
	
	

system ("pause");
return 0;
}
