#include <iostream>
#include <conio.h>

int main()
{

	int N, M, supamax, supalen, supastr, doppel;
	int **matrix;

	int max = -999999, len;

	std::cout << "Enter sequentially dimentions of array (strings & columns): \n", std::cin >> N >> M;

	matrix = new int *[N];

	for (int str = 0; str < N; str++)
		matrix[str] = new int[M];

	std::cout << "\n\n";
	for (int str = 0; str < N; str++)
		for (int st = 0; st < M; st++)
			std::cout << "\nElement of array "
					  << "[" << str << "][" << st << "]: ",
				std::cin>>matrix[str][st];
				//matrix[str][st] = getch();

	//--------------------------------------Printing an array
	std::cout << "\nArray:\n";
	for (int str = 0; str < N; str++)
	{

		std::cout << "|\t";
		for (int st = 0; st < M; st++)
		{
			{
				std::cout << matrix[str][st] << "\t";
			}
		}

		std::cout << "|\n\n";
	}

	supamax = -999999, supalen = 90;
	/*
	
	for (int str = 0; str < N; str++)
	{

		len = 1;
		max = -999999;

		for (int st = 0; st < M; st++)
		{

			if (len == 1)
				if (matrix[str][st] > max)
					max = matrix[str][st];
				else if (matrix[str][st] == max)
					len += 1;
				else
					max = -999999;

			else if (len > 1)
				if (matrix[str][st] == max)
					len += 1;
				else
				{
					supamax = max;
					supalen = len;
					supastr = str;
					len = 1;
					max = -999999;
				}
		}

		if (len > 1 | max > supamax)
		{
			supamax = max;
			supalen = len;
			supastr = str;
			len = 1;
			max = -999999;
		}
	}

*/

	for (int str = 0; str < N; str++)
	{
		len = 1;
		for (int st = 0; st < M; st++)
		{
			if (len = 1)
				if (matrix[str][st] > max)
					max = matrix[str][st];
				else if (matrix[str][st] == max)
				{
					len += 1;
					break;
				}
				else
					max = -999999;

			if (len > 1)
				if (matrix[str][st] == max)
					len += 1;
				else if (matrix[str][st] > max)
					max = matrix[str][st];
				else if (len <= supalen & max >= supamax)
				{
					supamax = max;
					supalen = len;
					supastr = str;
					max = -999999;
					len = 1;
				}
		}

		if (len <= supalen & max >= supamax) //(supalen >= len & supamax <= max)
		{
			supamax = max;
			supalen = len;
			supastr = str;
			max = -999999;
			len = 0;
		}
	}

	delete[] matrix;

	if (supalen > 1)
		std::cout << "The minimun lenght of maximum series (consists of " << supamax << ") is " << supalen << " and located in " << supastr + 1 << " string.";
	else
		std::cout << "There aren't any series.";

	std::cin.get();
	return 0;
}
