#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{

	srand(time(0));

    int M, N = M = 101, doppel, kolvo, len, input = 0;
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
        {
        	std::cout<<"\nEnter the element of matrix ["<<str<<"]["<<st<<"]";
            while (input == 0)
            	{
            		printf("\nThe number must be with the sign (!= 0): ");
            		std::cin>>input; 
					//input = rand() % 3 + 1;           		
					std::cout<<input;
            	}
            matrix[str][st] = input;
            input = 0;
		}
    //matrix[str][st] = rand() % 4 + 1;
    

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
    
    //int ** newmatrix = new int * [N];

    //--------------------------------------Main cycle
    for (int str = 0; str < N; str++)
    {

		int obkolvo = 0;
        for (int st = 0; st < M; st++)
        {
            kolvo = 0;
            for (int stcopy = 0; stcopy < M; stcopy++)
                if (matrix[str][st] == matrix[str][stcopy])
                {
                    kolvo += 1;
                	//obkolvo += 1;
            	}
            if (kolvo == 1)
                matrix[str][st] = 0;
        }
        
        //newmatrix[str] = new int [obkolvo*4];
        
    }
    
    
    /*
    
    for (int str = 0; str < N; str++)
    {
    	int a = 0;
    	for (int st = 0; st < M; st ++)
    	{
    		if (matrix[str][st] != 0)
    		{
    			newmatrix [str][a] = matrix[str][st];
    			
    		}
    	}
    }
    
    */
    
    
    //--------------------------------------Printing a new array
    std::cout << "\nNew array:\n";
    for (int str = 0; str < N; str++)
    {
		
        std::cout << "|\t";
        /*
        for (int num = 0; num < sizeof(newmatrix)/4; num++)
        {
                std::cout << newmatrix[str][num] << "\t";
        }
        */
    
       	for (int st = 0; st < M; st++)
       		{
				if (matrix[str][st] != 0)
       				std::cout<<matrix[str][st]<<"\t";
       		}

        std::cout << "|\n\n";
    }
    
    for (int str = 0; str < N; str++)
        delete[] matrix[str];
    delete[] matrix;
    
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    std::cin.get();
    return 0;
}
