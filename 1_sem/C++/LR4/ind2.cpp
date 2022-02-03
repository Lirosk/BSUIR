#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()

	{
		
		setlocale (0, "");
		srand(time(0));
		
		int N,M;
		std::cout<<"Enter the size of array NxM:\n",std::cin>>N>>M;
		int array[N][M],och = 0;
		
		std::cout<<"N (lines) = "<<N<<", M (columns) = "<<M<<"\n";
													//a(N) Ч строки, b(M) Ч столбцы 
		for (int a = 0; a< N; a++)
			for (int b = 0; b< M; b++)
				array[a][b] = rand()%50-30;
				
		for (int a = 0; a< N; a++)
		
			{
				std::cout<<"|\t";
				for (int b = 0; b< M; b++){
					if (a == b) {std::cout<<"["<<array[a][b]<<"]\t";}
					else {std::cout<<array[a][b]<<"\t";}
					}
					
				std::cout<<"|\n\n";
				
			}
			
		int diag = (N>M)?M:N;	
		
		for (int a = 0; a < diag; a++)
			for (int b = 1 + a; b < diag; b++)
				if (array[a][b] < 0) och += 1;
		
		std::cout<<"\nThe number of negativ elements above the main diagonal is: "<<och;
		
		
		std::cin.get();
		return 0;
		
	}
