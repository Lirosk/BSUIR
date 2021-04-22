#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b,c;
	int N;
	std::cout<<"¬ведите последовательно a,b,c и N:\n";
	std::cin>>a>>b>>c>>N;
	
	
	switch(N){
		case 2:{std::cout<<"Y = "<< b*c - powf(a,2) <<"\n";
			break;
		}
		
		case 56:{std::cout<<"Y = "<< b*c <<"\n";
			break;
		}
		
		case 7:{std::cout<<"Y = "<< powf(a,2) +c <<"\n";
			break;
		}
		
		case 3:{std::cout<<"Y = "<< a- b*c <<"\n";
			break;
		}
		
		default:{std::cout<<"Y = "<< powf((a+b),3) <<"\n";
		}
	}
	

getch();	
system ("pause");
return 0;
}

