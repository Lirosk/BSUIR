#include <iostream>




int main()
{
	int N, M, len, max, supastr = 90, supamax = 80, supalen = 80;
	printf("Enter the size of array NxM:\n");
	std::cin >> N >> M;
	
	
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++)
	{
		matrix[i] = new int[M];
	}
	
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cout << "\nEnter the element ["<<i<<"]["<<j<<"]:", std::cin >> matrix[i][j];
		}
	}
	
	
	//max = matrix[0][0];

	printf("The array:\n");
	for (int i = 0; i < N; i++)
	{
		printf("|\t\t");
		for (int j = 0; j < M; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		printf("|\n\n");
	}

	for (int i = 0; i < N; i++)
	{
		max = matrix[i][0];
		len = 0;
		for (int j = 0; j < M; j++)
		{
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
				len = 0;
			}

			if (matrix[i][j] == max)
			{
				len += 1;
			}

			if ((matrix[i][j] < max) & (len > 1) & (supalen > len) & (supamax > max))
			{	
				supalen = len;
				supastr = i;
				supamax = max;
			}

			if ((j + 1 == N) & (len > 1) & (supamax < max) & (supalen > len))
			{
				supalen = len;
				supastr = i;
				supamax = max;
			}
		}
		
	}


	
	//(supastr == 90) ? (std::cout << "\nThere aren't any sequences\n") : 
	if (supastr != 90)
		(std::cout << "The line: " << supastr + 1);
	else
		std::cout << "There aren't any series";
	return 0;
}

