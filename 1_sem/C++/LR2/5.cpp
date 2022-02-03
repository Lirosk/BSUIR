#include <iostream> 
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	float a,b,c,d;
	std::cout<<"¬ведите последовательно a,b,c и d:\n";
	std::cin>>a>>b>>c>>d;
	
	if (c>=d & a<d){
		std::cout<<"Z= "<<a+b/c<<"\n";
	}
	
	else if (c<d & a>=d){  //условие невыполнимо
		std::cout<<"Z= "<<a-b/c<<"\n";
	}
	
	else{
		std::cout<<"Z= 0"<<"\n";
	}
	
	
getch();	
system ("pause");
return 0;
}

