#include <iostream>
#include <conio.h>
using namespace std;
int main(){
	
	int a,b;
	setlocale(0,"");
	
	cout<<"Hello, World!\n";
TryAgain:
	cout<<"Какие натуральные числа надо сравнить?\n";
	cout<<"a= ";
	cin>>a;
	cout<<"b= ";
	cin>>b;
	
	while (a<=0 | b<=0)
		{
		cout<<"\nЧисла должны быть натруальными (n>0)\n\n\nЕще раз:\n";
		goto TryAgain;
		}



	// Способ 1
{
	/*
				{
	
	while (a > b)
		{
		cout<<"a больше b";
		system("pause");
		getch();
		return 0;
		}
		
		
	while (b > a)
		{
		cout<<"b больше a";
		getch();
		system("pause");
		return 0;
		}
		
	cout<<"a и b равны";					
								
				}
	*/			
}
	
	// Способ 2  
				{ 
	(a==b)?cout<<"а и b равны":((a>b)?cout<<"a больше b":cout<<"b больше a");
				}
		
		
		
getch();
system ("pause");	
return 0;	
}


