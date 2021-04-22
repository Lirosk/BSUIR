#include <iostream>
#include <ctime>
#include <stdlib.h>

void fill_and_print (float ** array, int N, int M, bool fill)
{
	for (int i = 0; i < N; i ++)
	{
		printf("|");
		for (int j = 0; j < M; j ++)
		{
			if (fill) array[i][j] = rand()%11-5;
			std::cout<<"\t"<<array[i][j];
		}
		printf("\t|\n\n");
	}
	
	return;
}

void prov (float ** array, int N, int M)
{
	int kolvo = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j ++)
		{
			if (*(*(array + i) + j) == 0)
			{
				std::cout<<"zero on ("<<i<<";"<<j<<")\n";
				kolvo += 1;
			}
		}
	}
	
	std::cout<<"The number of zero elements is "<<kolvo<<"\n\n";
	return;
}

void change (float ** array, int N, int M)
{
	if (N%2==0 | (N%2==1 & M%2==1))
	{
		for (int i = 0; i < N/2; i ++)
		{
			for (int j = 0; j < M; j ++)
			{
				if (i==N-1-i & j==M-1-j) return;
				array[i][j] += array[N-1-i][M-1-j];
				array[N-1-i][M-1-j] = array[i][j] - array[N-1-i][M-1-j];
				array[i][j] -= array[N-1-i][M-1-j];
			}
		}
	}
	else // if (N%2==1 & M%2==0)
	{
		for (int i = 0; i < N/2; i ++)
		{
			for (int j = 0; j < M; j ++)
			{
				if (i==(N-1)/2 & j==(M-1)/2) return;
				array[i][j] += array[N-1-i][M-1-j];
				array[N-1-i][M-1-j] = array[i][j] - array[N-1-i][M-1-j];
				array[i][j] -= array[N-1-i][M-1-j];
			}
		}
	}
	
	return;
}

int main()
{
	srand(time(0));
	int N, M;
	printf("Enter the size of array:\n");
	std::cin>>N>>M;
	
	float ** array = new float * [N];	
	for (int i = 0; i< N; i++)
		array[i] = new float [M];


	fill_and_print (array, N, M, 1);	
	prov (array, N, M);
	change(array, N, M);
	fill_and_print (array, N, M, 0);
	
	
	
	
	
	
	
	return 0;
}
