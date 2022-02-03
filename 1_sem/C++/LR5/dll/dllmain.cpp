/* Replace "dll.h" with the name of your header */
#include <iostream>
#include "dll.h"


__declspec (dllexport) int fib(int a)
{
	if (a<=2)
		return 1;
	return fib(a-1) + fib(a-2);
}

__declspec (dllexport) void prov (int matrix[], int i, int N)
{

	if (i >= N)
	{
		return;
	}
	
	if (matrix[i]*matrix[i]*matrix[i] > -10 && matrix[i]*matrix[i]*matrix[i] < 20)
		std::cout<<"\t"<<matrix[i];
		
	prov (matrix, i+1,N);
	return;
}
