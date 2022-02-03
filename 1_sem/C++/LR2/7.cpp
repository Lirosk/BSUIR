#include <iostream> 
#include <math.h>
#include <conio.h>
int main()
{
	setlocale(0,"");
	std::cout<<"Hello, World!\n";
	
	std::cout<<"Решение уравнения a*x^4 + b*x^3 + c*x^2 + b*x a = 0\n";
	float a,b,c,D1,D2,D3,t1,t2,x1,x2,x3,x4;
	std::cout<<"Введите последовательно коэффициенты a,b,c\n";
	std::cin>>a>>b>>c;
	D1 = powf(b,2) - 8*a*a*c;
	
	if (D1<0){
		std::cout<<"Корней нет\n";
	}
	else
	{
	
		t1=(-b+sqrt(D1))/(2*a);
		t2=(-b-sqrt(D1))/(2*a);
	
		D2 = powf(t1,2)-4;
		if (D2>=0){
			x1=(t1-sqrt(D2)/2);
			x2=(t1+sqrt(D2)/2);
		}
	
		D3 = powf(t2,2)-4;
		if (D3>=0){
			x3=(t2-sqrt(D3)/2);
			x4=(t2+sqrt(D3)/2);
		}
	
	
	if (x1!=0) {std::cout<<"x1= "<<x1<<"\n";}
	
	if (x2!=0) {std::cout<<"x2= "<<x2<<"\n";}
	
	if (x3!=0) {std::cout<<"x3= "<<x3<<"\n";}
	
	if (x4!=0) {std::cout<<"x4= "<<x4<<"\n";}
	
	
	}
	

getch();	
system ("pause");
return 0;
}

