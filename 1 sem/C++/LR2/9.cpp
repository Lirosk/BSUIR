#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	int G, T,age,numd;
	std::cout<<"Введите год рождения человека G и текущий год T\n";
	
VvG:	
	std::cout<<"Введите год рождения:\n";
	std::cin>>G;
	while (G<1)
	{
		std::cout<<"\n\nГод рождения G должен быть натуральным числом\n\n";
		goto VvG;
	}
	
VvT:	
	std::cout<<"Введите текущий год:\n";
	std::cin>>T;
	while (T<G)
	{
		std::cout<<"\n\nТеущий год не может превышать год рождения\n\n";
		goto VvT;
	}
	
	age = T-G;
	numd=age/10;
	


		switch ((age%100)/10)
	{
		case 1:{std::cout<<"Получается "<< age << " лет\n";
				system ("pause");
				return 0;
			break;
		}
	}
	
	
	
	switch (age-numd*10)
	{
		case 1:{std::cout<<"Получается "<< age << " год\n";
			break;
		}
		
		case 2 :
			
		
		case 3 :
			
		
		case 4 :{std::cout<<"Получается "<< age << " года\n";
			break;
		}
		
		default:{std::cout<<"Получается "<< age << " лет\n";
		}
		
	}
	
	
	
getch();		
system ("pause");
return 0;
}
	
