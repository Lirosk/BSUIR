#include <iostream>
#include <conio.h>

using namespace std;
int main(){
	
	setlocale(0, "");
	cout<<"Hello, World!\n";
	int a, b;
	cout<<"a= ";
	cin>>a;
	cout<<"b= ";
	cin>>b;
	a+=b;
	b=a-b;
	a-=b;
	cout<<"Теперь a= "<<a<<"\nb= "<<b<<"\n";
	
system ("pause");
return 0;
}
