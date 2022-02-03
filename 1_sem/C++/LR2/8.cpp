#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	int N,k,numd,tst;
	std::cout<<"Введите сумму денег N [1,19] и добавляемую сумму k [0,79]:\n";
	
InN:
	std::cout<<"Введите N: ";
	std::cin>>N;
	while (N<1 | N>19) {
	std::cout<<"\n\nВведите сумму денег N в промежутке [1,19]\n";
	goto InN;
	}
	
Ink:
	std::cout<<"Введите k: ";
	std::cin>>k;
	while (k<0 | k>79) {
	std::cout<<"\n\nВведите добавляемую сумму k в промежутке [0,79]\n";
	goto Ink;
	}
	
	N += k;
	numd = N/10;

	
	
	switch (N/10)
	{
		case 1:{std::cout<<"Получается "<< N << " рублей\n";
				system ("pause");
				return 0;
			break;
		}
	}
	
	
	
	switch (N-numd*10)
	{
		case 1:{std::cout<<"Получается "<< N << " рубль\n";
			break;
		}
		
		case 3 :
		
		
		case 4 :
		
		
		case 2 :{std::cout<<"Получается "<< N << " рубля\n";
			break;
		}
		
		default:{
			std::cout<<"Получается "<< N << " рублей\n";
		}
		
	}
	
	
getch();
system ("pause");
return 0;
}

