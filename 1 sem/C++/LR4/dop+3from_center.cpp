#include <iostream>

int main()
{
	
	printf("Enter the number of lines & columns: ");
	int N, str, st; std::cin>>N;
	
	int ** matrix = new int * [N];
	for (int str = 0; str < N; str ++)
		matrix[str] = new int [N];
		
	for (int str = 0; str < N; str ++)
		for (int st = 0; st < N; st ++)
			matrix[str][st] = 0;
		
	if (N%2 == 0)
	{
		st = N/2 - 1;
		str = N/2;
	}
	else 
	{
		str = st = (N-1)/2;
	}
	
	int num = 0, step = 1;
	
	while ( num < N*N)
	{
		for(int proc = 0; proc < step & num < N*N; proc ++)	//right
		{
			matrix[str][st] = num += 1;
			st += 1;
			
		}
		
		for(int proc = 0; proc < step & num < N*N; proc ++)	//up
		{
			matrix[str][st] = num += 1;
			str -= 1;
		}
		
		step += 1;
		
		for(int proc = 0; proc < step & num < N*N; proc ++)	// left
		{
			matrix[str][st] = num += 1;
			st -= 1;
		}
		
		for(int proc = 0; proc < step & num < N*N; proc ++)	//down
		{
			matrix[str][st] = num += 1;
			str += 1;
		}
		
		step += 1;
	}
	
	
	printf("\nThe end\n");

    std::cout << "\nArray:\n";
    for (int str = 0; str < N; str++)
    {

        std::cout << "|\t";
        for (int st = 0; st < N; st++)
        {
            std::cout << matrix[str][st] << "\t";
        }

        std::cout << "|\n\n";
    }

    for (int str = 0; str < N; str++)
        delete[] matrix[str];
    delete[] matrix;
	
	
	return 0;
}
