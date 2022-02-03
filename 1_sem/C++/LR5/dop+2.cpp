#include <iostream>
#include <cmath>

int f(int a, int b, int k);

int main()
{ 
	int qqq = 1;
	
	while(1)
	{
		unsigned long long k, n, x = 0, dec;
		int t;
		k = n = t = -1;
		printf("\nEnter k (>0),n (>0), t[1,10]\n");
		std::cin >> k >> n >> t;
				dec = pow(10, t);

		
		if (k<1 | n < 1| t < 1 | t > 10)
		{
			k = n = t = -1;			
			continue;
		}
		
			
			
		
		if (n > 7 | k > 7)
		{
			x = pow(k,n);
			//x %= dec;
			std::cout << "\nCase "<<qqq<<": " << x%dec << "\n\n";
			qqq += 1;
			continue;
		}
		
		
		
		for (int i = 0; i <= n * (k - 1); i++)
		{
			x += f(n, i, k);
		}
		dec = pow(10, t);
		x %= dec;
		std::cout << "\nCase "<<qqq<<": " << x << "\n\n";
		qqq += 1;
	}
	std::cin.get();
	return 0;

}

int f(int n, int r, int k)
{
	int S = 0;
	if ((n == 0) & (r == 0)) return 1;
	if ((n > 0)& ((r >= 0) & (r < (n * (k - 1) + 1)))) {
		for (int i = 0; i <= k - 1; i++)
		{
			S += f(n - 1, r - i, k);
		}
		return S;
	}
	return 0;
}
