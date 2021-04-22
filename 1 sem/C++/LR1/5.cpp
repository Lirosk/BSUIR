#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;
int main(){
	
	setlocale(0,"");
	
	float K,x,p,D,C,y;
	
	cout<<"Hello, World!\n";
	cout<<"K= ";
	cin>>K;
	cout<<"x= ";
	cin>>x;
	cout<<"p= (гр) ";
	cin>>p;
	p = p*M_PI/180;
	cout<<"D= ";
	cin>>D;
	cout<<"C= ";
	cin>>C;
	
	y=1+(powf(K,2)/(2*(x+sin(p) )*exp(K) ) - exp(K) + D*C );
	cout<<"y= "<< y <<"\n";
	
	
system ("pause");
return 0;
}










