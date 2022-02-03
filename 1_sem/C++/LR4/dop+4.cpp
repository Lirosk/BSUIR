#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{
	
	srand(time(0));
	
	int N, M, diag, maxmin[10000] = {0};
	N=M = 101;
	printf("Enter the number of lines & columns:\n");
	while (N<1 | N>100) std::cout<<"\nEnter the number of lines [1;100]:\n", std::cin>>N;
	while (M<1 | M>100) std::cout<<"\nEnter the number of columns [1;100]:\n", std::cin>>M; 
	
	diag = (N<M)?N:M;
	
	int ** matrix = new int * [N];
	for (int str = 0; str < N; str ++)
		matrix[str] = new int [M];
		
	for (int str = 0; str < N; str ++)		//filling up an array
		for (int st = 0; st < M; st ++)
			matrix[str][st] = rand()%10 + 1;
			
	int ** newmatrix = new int * [N];
	for (int str = 0; str < N; str ++)
		newmatrix[str] = new int [M];
		
	for (int str = 0; str < N; str ++)
		for (int st = 0; st < M; st ++)
			newmatrix[str][st] = matrix[str][st];
			
		std::cout << "\nArray:\n";
    for (int str = 0; str < N; str++)
    {

        std::cout << "|\t";
        for (int st = 0; st < M; st++)
        {
			if (str == diag - 1 - st) std::cout <<"["<< matrix[str][st] << "]\t";
        	else std::cout << matrix[str][st] << "\t";;
        }

        std::cout << "|\n\n";
    }

		
	int max = -9999999999;
	int order = 0;
	
	int doppel = diag + 1, kolvo = 0;
	while (doppel > 0)
		kolvo += doppel -= 1;
	
	for (int proc = 1; proc <= kolvo; proc ++)		//main cycle
	{
		
		max = -9999999999;
		
		for (int str = 0; str < diag; str ++)			//searching for max element
		{
			for (int st = 0; st < diag - str; st ++)
			{
				if (matrix[str][st] > max)
				{
					max = matrix[str][st];
				}
			}
		}
		
		
		for (int str = 0; str < diag; str ++)
		{
			for (int st = 0; st < diag - str; st ++)
			{
				if (matrix[str][st] == max)
				{
					matrix[str][st] = NULL;
					maxmin[order] = max;
					order += 1;
				}
			}
		}
		
	}

	
	printf("\nmax -> min: ");
	for (int str = 0; maxmin[str] != 0; str ++ )
		std::cout<<maxmin[str]<<" ";
	printf ("\n");
	
	

    
    printf("\n\n");
    
    order = 0;
    for (int str = 0; str < diag; str ++)
    {
    	for (int st = 0; st < diag - str; st ++)
    		{
    			newmatrix[str][st] = maxmin[order];
    			order += 1;
    		}
    }
    
    for (int str = 0; str < N; str ++)
    {
    	printf("|\t");
    	for (int st = 0; st < M; st ++)
    	{
    		if (str == diag - 1 - st) std::cout<<"["<<newmatrix[str][st]<<"]\t";
    		else std::cout << newmatrix[str][st] << "\t";
    	}
    	printf("|\n\n");
    }
    

    for (int str = 0; str < N; str++)
        delete[] matrix[str];
    delete[] matrix;

	for (int str = 0; str < N; str++)
        delete[] newmatrix[str];
    delete[] newmatrix;
	
	std::cin.get();
	return 0;
}
