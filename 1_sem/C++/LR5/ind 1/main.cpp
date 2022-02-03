#include <iostream>
#include "staticlib.h"


int main()
{
		
	int N;
	printf("Enter the number of lines & columns:\n");
	std::cin>>N;
	int summaina,summainb,sumsidea,sumsideb;
	summaina = summainb = sumsidea = sumsideb = 0;
	
	int ** matrix = new int * [N];
	int ** array = new int * [N];
	for (int i = 0; i < N; i ++)
	{
		matrix[i] = new int [N];
		array[i] = new int [N];
	}
	
		
	for (int i =0; i < N; i ++)
		for (int j = 0; j < N; j ++)
		{
			matrix[i][j] = fill_a(i,j);
			array[i][j] = fill_b(i,j);
			if (i == j)
			{
				summaina += matrix[i][j];
				summainb += array[i][j];
			}
			else if (i + j < N - 1)
			{
				sumsidea += matrix[i][j];
				sumsideb += array[i][j];
			}
		}
			
			
			
	printf("\n\n\nMatrix A\n");
	for (int i = 0; i < N; i ++)
	{
		std::cout<<"|\t";
		for (int j = 0; j < N; j ++)
		{
			if (i == j) std::cout<<"["<<*(*(matrix + i) + j)<<"]\t";
			else if (i == N-1-j) std::cout<<"("<<*(*(matrix+i)+j)<<")\t";
			else std::cout<<*(*(matrix + i) + j)<<"\t";
		}
		std::cout<<"|\n\n";
	}
	std::cout<<"Sum of main diag's elements: "<<summaina<<"\nSum of side diag's elements: "<<sumsidea;


	printf("\nMatrix B\n");
	for (int i = 0; i < N; i ++)
	{
		std::cout<<"|\t";
		for (int j = 0; j < N; j ++)
		{
			if (i == j) std::cout<<"["<<*(*(array + i) + j)<<"]\t";
			else if (i == N-1-j) std::cout<<"("<<*(*(array+i)+j)<<")\t";
			else std::cout<<*(*(array + i) + j)<<"\t";
		}
		std::cout<<"|\n\n";
	}
	std::cout<<"Sum of main diag's elements: "<<summainb<<"\nSum of side diag's elements: "<<sumsideb;
	
	std::cin.get();
	std::cin.get();
	return 0;
}
