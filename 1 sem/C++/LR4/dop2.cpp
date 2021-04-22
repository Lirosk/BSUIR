#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{
	
	srand(time(0));
	
	int N, M, supastr, len, supalen, supamax;
	std::cin>>N>>M;
	
	int matrix[10][10];
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//std::cin>>matrix[i][j];
			matrix[i][j] = rand()%10 + 1;
		}
	}
	
	for (int i = 0; i < N; i++)
	{
		printf("|\t");
		for (int j = 0; j < M; j ++)
		{
			std::cout<<*(*(matrix + i) + j)<<"\t";
		}
		printf("|\n\n");
	}
	
	supamax = -999999999;
	supalen = 0;
	
	for (int i = 0; i < N; i ++)	//Main cycle
	{
		len = 0;
		for (int j = 0; j < M; j ++)
		{
			
		}
	
	printf("\n");
	
	for (int j = 0; j < M; j++)
	{
		std::cout<<"\t"<<*(*(matrix + supastr) + j);
	}
	std::cout<<"\n\n"<<supamax<<"\t"<<supalen<<" ";
	
	
	
	
	
	
	
	return 0;
}
