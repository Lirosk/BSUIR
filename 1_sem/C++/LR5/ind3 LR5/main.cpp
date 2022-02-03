#include <iostream>
#include <math.h>

/*
unsigned long long binpow(int a, int n)
{
	if (n == 1)
	{
		return a;
	}
	if (n % 2 == 0)
	{
		return binpow(a, n / 2) * binpow(a, n / 2);
	}
	return a * binpow(a, n - 1);
}
*/

long long int binpow(long long int a,long long int n, int k)
{
	if (n == 1)
	{
		return a;
	}
	else if (n % 2 == 1)
	{
		return a * binpow(a, n - 1,k)%k;
	}
	else
	{
		long long int b = binpow(a, n / 2,k)%k;
		return b%k* b%k;
	}
}

int main()
{
	long long int a, n, k;
	printf("Enter the numbers:\n");
	std::cin >> a >> n >>k;
	k = pow(10, k);
	std::cout << binpow(a, n,k)%k;//%(int)pow(10,k);
}
