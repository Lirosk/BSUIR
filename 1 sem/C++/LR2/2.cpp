#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	float d,a,b;
	char zn,ch;
	
	
	std::cout<<"Hello, World!\n";
	std::cout<<"����� ����� ��� �������� ����� ��������� ��������:\n������ �����:\n";
	std::cin>>a;
	std::cout<<"������ �����:\n";
	std::cin>>b;
	
	
TryAgain:
	std::cout<<"������� ���� �������� (+,-,*,/): ";
	std::cin>>zn;
	
	
	switch(zn)
{

	case '+':	{d=a+b;
		break;
			}
	case '-':	{d=a-b;
		break;
			}
	case '*':	{d=a*b;
		break;
			}		
	case '/':	{d=a/b;
		break;
			}		
	default:	{std::cout<<"������������ ����\n\n��� ���:\n";
		goto TryAgain;;
			}			
}
	
	
	std::cout<<"������� ���� �������� ��� ���? ('y' - ���� ��)\n";
	ch = getch();
	if (ch=='y' | ch == '�')
	{
		goto TryAgain;
	}

	std::cout<<"d= "<<d<<'\n';

getch();	
return 0;
}





