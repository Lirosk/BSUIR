#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
	
	{
		
		setlocale (0, "");
		srand(time(0));
		
		int capacity;
		std::cout<<"Size of array?: ",std::cin>>capacity;
		int array[capacity],reverse[capacity];
		
		for (int t = 0; t < capacity; t++)
		
			{
				
				array[t] = rand()%30 + 1;
				reverse[capacity - 1 - t] = array[t];
				
			}
		
		for (int num = 0; num < capacity; num ++)
			std::cout<<array[num]<<' ';
			
		std::cout<<"\n";
				
		for (int num = 0; num < capacity; num ++)
			std::cout<<reverse[num]<<' ';
		
		std::cin.get();
		return 0;
		
	}
