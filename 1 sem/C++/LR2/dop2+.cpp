#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{

	setlocale (0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b,c,x,y;
	std::cout<<"������� ��������������� ������� ��������� x � y\n";
	std::cin>>x>>y;
	std::cout<<"������� ��������������� ��������� ������� a, b � c\n";
	std::cin>>a>>b>>c;
	
	
	if ((x > a & y > b) | (x > b & y > a))
	{
		std::cout<<"������ �������� ����� ��������� ��������� a � b\n";
	}
	
	else if ((x > c & y > a) | (x > a & y > c))
	{
		std::cout<<"������ �������� ����� ��������� ��������� a � c\n";
	}
	
	else if ((x > c & y > b) | ( x > b & y > c))
	{
		std::cout<<"������ �������� ����� ��������� ��������� c � b\n";
	}
	
	else
	{
		std::cout<<"������ �� �������� ����� ��������� � ������� ���������\n";
	}
	
	

system ("pause");
return 0;
}
