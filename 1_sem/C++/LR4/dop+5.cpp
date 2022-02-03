#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{
	
	srand(time(0));
	
	int N, M;
	N=M = 101;
	printf("Enter the number of lines & columns:\n");
	while (N<1 | N>100) std::cout<<"\nEnter the number of lines [1;100]:\n", std::cin>>N;
	while (M<1 | M>100) std::cout<<"\nEnter the number of columns [1;100]:\n", std::cin>>M; 
		
	int ** matrix = new int * [N];
	for (int str = 0; str < N; str ++)
		matrix[str] = new int [M];
		
	for (int str = 0; str < N; str ++)		//filling up an array
		for (int st = 0; st < M; st ++)
			matrix[str][st] = rand()%10 + 1;

/*			
	int ** newmatrix = new int * [N];
	for (int str = 0; str < N; str ++)
		newmatrix[str] = new int [M];
		
	for (int str = 0; str < N; str ++)
		for (int st = 0; st < M; st ++)
			newmatrix[str][st] = matrix[str][st];
*/
						
		std::cout << "\nArray:\n";
    for (int str = 0; str < N; str++)
    {

        std::cout << "|\t";
        for (int st = 0; st < M; st++)
        {	
        	std::cout << matrix[str][st] << "\t";;
        }

        std::cout << "|\n\n";
    }
    
    int doppel;
    
    for (int str = 0; str < N; str ++)
    {
    	for (int st = 0; st < M; st ++)
    	{
    		
    		if (str == 0 & st == 0)
    			continue;
    		
    		else if (str == 0)
			{
				matrix[0][st] = (matrix[0][st - 1] > matrix[0][st])?matrix[0][st - 1]:matrix[0][st];
			}   
			
			else if (st == 0)
			{
				matrix[str][0] = (matrix[str - 1][0] > matrix[str][0])?matrix[str - 1][0]:matrix[str][0];	
			}
			 		
    		else //else if (str > 0 & st > 0)
    		{
    			doppel = (matrix[str-1][st] > matrix[str][st-1])?matrix[str-1][st]:matrix[str][st-1];
    			matrix[str][st] = (doppel > matrix[str][st])?doppel:matrix[str][st];  		
    		}
    		
    		
    	}
    }
    
    
    std::cout << "\nArray:\n";
    for (int str = 0; str < N; str++)
    {

        std::cout << "|\t";
        for (int st = 0; st < M; st++)
        {	
        	std::cout << matrix[str][st] << "\t";;
        }

        std::cout << "|\n\n";
    }
    
    
    for (int str = 0; str < N; str ++)
    {
    	delete[] matrix[str];
    	//delete[] newmatrix[str];
    }
    delete[] matrix;
    //delete[] newmatrix;
    
    std::cin.get();
	return 0;   
}
