#include <iostream> 
#include <conio.h>
int main(){
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	std::cout<<"¬ведите последовательно a и b\n";
	int a,b;
	float c,d,e;
	std::cin>>a>>b;
	
	
	if (a>b) {
		b=0;
	}
	else if (a<b){
		a=0;
	}
	else{
		a=b=0;
	}
	std::cout<<"a= "<<a<<"\nb= "<<b<<"\n\nч2\n\n";
	
	
TryAgain:	
	std::cout<<"¬ведите последовательно различные c,d и e\n";
	std::cin>>c>>d>>e;
	
	if (c==d|e==d|c==e)
	{
	std::cout<<"\n„исла должны быть разные\n\n\n≈ще раз:\n";
	goto TryAgain;
	}
	
	c = (c>d & c>e)?c-0.3:c;
	d = (d>c & d>e)?d-0.3:d;
	e = (e>c & e>d)?e-0.3:e;
	std::cout<<"c= "<<c<<"\nd= "<<d<<"\ne="<<e<<"\n";

getch();	
system ("pause");
return 0;
}
