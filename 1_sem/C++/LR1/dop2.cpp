#include <iostream>
#include <conio.h>
using namespace std;
int main(){
	
	int a,b;
	setlocale(0,"");
	
	cout<<"Hello, World!\n";
TryAgain:
	cout<<"����� ����������� ����� ���� ��������?\n";
	cout<<"a= ";
	cin>>a;
	cout<<"b= ";
	cin>>b;
	
	while (a<=0 | b<=0)
		{
		cout<<"\n����� ������ ���� ������������ (n>0)\n\n\n��� ���:\n";
		goto TryAgain;
		}



	// ������ 1
{
	/*
				{
	
	while (a > b)
		{
		cout<<"a ������ b";
		system("pause");
		getch();
		return 0;
		}
		
		
	while (b > a)
		{
		cout<<"b ������ a";
		getch();
		system("pause");
		return 0;
		}
		
	cout<<"a � b �����";					
								
				}
	*/			
}
	
	// ������ 2  
				{ 
	(a==b)?cout<<"� � b �����":((a>b)?cout<<"a ������ b":cout<<"b ������ a");
				}
		
		
		
getch();
system ("pause");	
return 0;	
}


