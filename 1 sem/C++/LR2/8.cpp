#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	int N,k,numd,tst;
	std::cout<<"������� ����� ����� N [1,19] � ����������� ����� k [0,79]:\n";
	
InN:
	std::cout<<"������� N: ";
	std::cin>>N;
	while (N<1 | N>19) {
	std::cout<<"\n\n������� ����� ����� N � ���������� [1,19]\n";
	goto InN;
	}
	
Ink:
	std::cout<<"������� k: ";
	std::cin>>k;
	while (k<0 | k>79) {
	std::cout<<"\n\n������� ����������� ����� k � ���������� [0,79]\n";
	goto Ink;
	}
	
	N += k;
	numd = N/10;

	
	
	switch (N/10)
	{
		case 1:{std::cout<<"���������� "<< N << " ������\n";
				system ("pause");
				return 0;
			break;
		}
	}
	
	
	
	switch (N-numd*10)
	{
		case 1:{std::cout<<"���������� "<< N << " �����\n";
			break;
		}
		
		case 3 :
		
		
		case 4 :
		
		
		case 2 :{std::cout<<"���������� "<< N << " �����\n";
			break;
		}
		
		default:{
			std::cout<<"���������� "<< N << " ������\n";
		}
		
	}
	
	
getch();
system ("pause");
return 0;
}

