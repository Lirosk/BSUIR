#include <iostream>

long long int binpowreduced(long long int num, int n, int k)
{
	if((n == 0))
		return 1;
	else if ((n % 2 == 0))
	{
		long int b = binpowreduced(num, n / 2, k) % k;
		return (b * b)%k;
	}
	else //if ((n % 2 == 1))
		return (num * binpowreduced(num, n - 1, k)%k)%k;
}


int main()
{
	int k, n, t;
	for (int step = 1; step++;)
	{
		printf("Enter the k, n ,t:\n");
		std::cin >> k >> n >> t;
		t = (int)pow(10, t);
		std::cout << "Case " << step - 1 << ": " << (long long int)binpowreduced(k, n, t)%t<< "\n\n\n\n\n\n\n";
	}
	return 0;
}