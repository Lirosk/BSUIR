#include <iostream>

int F(int n);
int S(int p , int q);

int main()
{
	int p,q;
	printf ("Enter p & q:\n");
	std::cin>>p>>q;
	std::cout<<S(p,q);
	
	
	std::cin.get();
	return 0;
}

int S (int p, int q)
{
	if (p < 0 | q < 0) return NULL;
	int S = 0;
	for (int i = p; i <= q; i++)
	{
		S += F(i);
	}
	return S;
}

int F(int n)
{
	if (n%10 > 0) return n%10;
	return F(n/10);
}

