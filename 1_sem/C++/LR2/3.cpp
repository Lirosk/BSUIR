#include <iostream> 
#include <conio.h>
int main()
{
	
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b;
	bool boolean;
	std::cout<<"������� ��������������� ����� a � b, ������� ���� ��������: \n";
	std::cin>>a>>b;
	boolean = a>b;
	boolean?std::cout<<"a ������ b":std::cout<<"b ������ a\n";
	
	
getch();
system ("pause");
return 0;
}

