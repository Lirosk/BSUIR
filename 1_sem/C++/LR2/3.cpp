#include <iostream> 
#include <conio.h>
int main()
{
	
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b;
	bool boolean;
	std::cout<<"Введите последовательно числа a и b, которые надо сравнить: \n";
	std::cin>>a>>b;
	boolean = a>b;
	boolean?std::cout<<"a больше b":std::cout<<"b больше a\n";
	
	
getch();
system ("pause");
return 0;
}

