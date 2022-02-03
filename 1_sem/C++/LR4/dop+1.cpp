#include <iostream>
#include <stdlib.h>

int main()
{

	int M, N = M = 101, doppel, kolvo, len;
	int **matrix = new int *[N];

	while (N<1 | N> 100)
	{
		std::cout << "Enter the number of lines in matrix in range [1;100]: ";
		std::cin >> N;
	}
	while (M<1 | M> 100)
	{
		std::cout << "Enter the number of columns in matrix in range [1;100]: ";
		std::cin >> M;
	}

	for (int str = 0; str < N; str++)
		matrix[str] = new int[M];

	//--------------------------------------Filling up an array
	for (int str = 0; str < N; str++)
		for (int st = 0; st < M; st++)
			std::cin >> matrix[str][st];

	//--------------------------------------Printing an array
	std::cout << "\nArray:\n";
	for (int str = 0; str < N; str++)
	{

		std::cout << "|\t";
		for (int st = 0; st < M; st++)
		{
			std::cout << matrix[str][st] << "\t";
		}

		std::cout << "|\n\n";
	}

	int **newmatrix = new int *[N];
	for (int newstr = 0; newstr < N; newstr++)
		newmatrix[newstr] = new int[M];

	//--------------------------------------Main cycle

	for (int str = 0; str < N; str++)
	{
		kolvo = 0;

		for (int st = 0; st < M; st++)
		{
			for (int stcop = 0; stcop < M; stcop++)
			{
				if (matrix[str][st] == matrix[str][stcop])
					kolvo += 1;
			}

			kolvo /= 2;

			//for (int newstr = 0; newstr < N; newstr++)
			//	newmatrix[newstr] = new int[M];

			for (int stcop = 0; stcop < N; stcop++)
			{

				if (matrix[str][st] == matrix[str][stcop])
				{
					newmatrix[str][stcop] = matrix[str][st];
				}
			}
		}

	}

	/*

	int **newmatrix = new int *[N];
	int len[N];
	for (int str = 0; str < N; str++)
	{
		len[str] = 0;
		for (int st = 0; st < M; st++)
		{
			kolvo = 0;
			for (int stcopy = 0; stcopy < M; stcopy++)
				if (matrix[str][st] == matrix[str][stcopy])
					kolvo += 1;
		}
		*newmatrix[str] = new int[len[str]];
	}

	*/

	//--------------------------------------Printing a new array
	std::cout << "\nNew array:\n";
	for (int str = 0; str < N; str++)
	{

		std::cout << "|\t";
		for (int st = 0; st < M; st++)
		{
			{
				std::cout << newmatrix[str][st] << "\t";
			}
		}

		std::cout << "|\n\n";
	}
	for (int str = 0; str < N; str++)
		delete[] matrix[str];
	delete[] matrix;
	std::cin.get();
	return 0;
}