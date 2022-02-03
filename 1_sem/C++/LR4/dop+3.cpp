#include <iostream>
#include <ctime>

int main()
{
	//srand(time(NULL));
	
	int N, num, str,st;
	printf("Enter the number of lines & columns: ");
	std::cin>>N;
	
	int ** matrix = new int * [N];
	for (int str = 0; str < N; str++)
		matrix[str] = new int [N];
		
	for (str = 0; str < N; str ++)
		for (st = 0; st < N; st ++)
			matrix[str][st] = 0;
	
	str = st = num = 0;
	for (int processing = 1; processing <= N*N; str++)
	{
		for (;;)	//right
		{
			matrix[str][st] = num += 1;
			if (matrix[str][st + 1] == 0 & st + 1 < N)
			{
				st += 1;
			}
			else
			{
				str += 1;
				break;
			}
		}
		
		
		for (;;)	//down
		{
			matrix[str][st] = num += 1;
			if (matrix[str + 1][st] == 0 & str + 1 < N)
			{
				str += 1;
			}
			else
			{
				st -= 1;
				break;
			}
		}
		
		
		for (;;)	//left
		{
			matrix[str][st] = num+=1;
			if (matrix[str][st - 1] & st - 1 >= 0)
			{
				st -= 1;
			}
			else 
			{
				str -= 1;
				break;
			}
		}
		
		
		for (;;)	//up
		{
			matrix[str][st] = num += 1;
			if (matrix[str - 1][st] == 0)
			{
				str -= 1;
			}
			else
			{
				st += 1;
				break;
			}
		}
	}
	
	
	std::cin.get();
	return 0;
}


/*
dop+1:
посчитать кол-во повт. элементов
создать строку с таким размером
*/
