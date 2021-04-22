#include <iostream>


int main()
{
	char ch = 'B';
	
	std::cout<<(int(toupper(ch)) - 55);//A to 10
	std::cout<<char(10 + 55);//10 to A
	
	return 0;
}

