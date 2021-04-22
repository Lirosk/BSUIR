#include <iostream>
#include <stdlib.h>

int main()

	{
		
		setlocale (0, "");
		int N, sum, exponent;
		std::cout<<"Enter the size N of array: ", std::cin>>N;
		int array[N][N],array2[N][N],array3[N][N];
		
		
		
													//Filling up an array
		for (int st = 0; st < N ; st++)				
			for (int str = 0; str < N; str++)		
		{
				//array2[st][str] = array[st][str] = rand()%15 - 5;	
				std::cin>>array[st][str];
				array2[st][str] = array[st][str];
		}
				
				
		//--------------------------------------------Printing an array
		std::cout<<"\nArray\n";
		for (int st = 0; st< N; st++)
			{
				
				std::cout<<"|\t";
				for (int str = 0; str< N; str++){
					if (st == str) {std::cout<<"["<<array[st][str]<<"]\t";}	//Main diagonal's elements in []
					else {std::cout<<array[st][str]<<"\t";}
					}
					
				std::cout<<"|\n\n";
				
			}
			
			
			
		std::cout<<"\nВ какую степень возвести матрицу? ",std::cin>>exponent;
			
			
			
			
			
		//--------------------------------------------exponentiation
   		for (int i = 1; i<exponent;)
   			{
   				
   				for (int st = 0; st < N; st++)
					for (int str = 0; str < N; str++)
						{
						
							array3[st][str] = 0;
							for (int k = 0; k < N; k++)
								array3[st][str] += array[st][k]*array2[k][str];
						
						}	
						
				i+=1;
   				
   				
   				
   				
   				//--------------------------------------------Printing an array
   				std::cout<<"\nArray^"<<i<<"\n";
				for (int st = 0; st< N; st++)
					{
				
						std::cout<<"|\t";
						for (int str = 0; str< N; str++){
							if (st == str) {std::cout<<"["<<array3[st][str]<<"]\t";}	//Main diagonal's elements in []
							else {std::cout<<array3[st][str]<<"\t";}
						}
					
				std::cout<<"|\n\n";
				
					}
   				
   				
   				
   				
   				for (int st = 0; st < N; st++)
					for (int str = 0; str < N; str++)
						array2[st][str] = array3[st][str];
					
   			}	//the end of the exponentiation
		
		std::cin.get();
		return 0;
		
	}
