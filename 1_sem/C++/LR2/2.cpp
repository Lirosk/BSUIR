#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	float d,a,b;
	char zn,ch;
	
	
	std::cout<<"Hello, World!\n";
	std::cout<<"Введи числа над которыми нужно совершить операцию:\nПерове число:\n";
	std::cin>>a;
	std::cout<<"Второе число:\n";
	std::cin>>b;
	
	
TryAgain:
	std::cout<<"Введите знак операции (+,-,*,/): ";
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
	default:	{std::cout<<"Неправильный ввод\n\nЕще раз:\n";
		goto TryAgain;;
			}			
}
	
	
	std::cout<<"Выбрать знак операции еще раз? ('y' - если да)\n";
	ch = getch();
	if (ch=='y' | ch == 'у')
	{
		goto TryAgain;
	}

	std::cout<<"d= "<<d<<'\n';

getch();	
return 0;
}





