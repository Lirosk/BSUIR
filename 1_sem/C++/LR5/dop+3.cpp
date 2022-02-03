#include <iostream>

int sum (int n);
int del (int n);

int main()
{
	int n;
	while (1)
	{
	std::cin>>n;
	std::cout<<"\n"<<sum(n)<<"\n\n\n";
	}
	
	std::cin.get();
	return 0;
}

int sum (int n)
{	
	int S = 0;
	while (n > 0)
	{
		S += del (n);
		n -= 1;
	}	
	return S;
}
	
int del (int n)	
{	
	int sum = 0;
	if (n <= 2 | n&2 == 0) return 1;
	int max = 1;
	for (int i = 1; i <= n; i += 2)
	{
		if (n%i == 0)
			if (max < i)
				max = i;
	}
	return max;
	
}
