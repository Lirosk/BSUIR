#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	int G, T,age,numd;
	std::cout<<"������� ��� �������� �������� G � ������� ��� T\n";
	
VvG:	
	std::cout<<"������� ��� ��������:\n";
	std::cin>>G;
	while (G<1)
	{
		std::cout<<"\n\n��� �������� G ������ ���� ����������� ������\n\n";
		goto VvG;
	}
	
VvT:	
	std::cout<<"������� ������� ���:\n";
	std::cin>>T;
	while (T<G)
	{
		std::cout<<"\n\n������ ��� �� ����� ��������� ��� ��������\n\n";
		goto VvT;
	}
	
	age = T-G;
	numd=age/10;
	


		switch ((age%100)/10)
	{
		case 1:{std::cout<<"���������� "<< age << " ���\n";
				system ("pause");
				return 0;
			break;
		}
	}
	
	
	
	switch (age-numd*10)
	{
		case 1:{std::cout<<"���������� "<< age << " ���\n";
			break;
		}
		
		case 2 :
			
		
		case 3 :
			
		
		case 4 :{std::cout<<"���������� "<< age << " ����\n";
			break;
		}
		
		default:{std::cout<<"���������� "<< age << " ���\n";
		}
		
	}
	
	
	
getch();		
system ("pause");
return 0;
}
	
