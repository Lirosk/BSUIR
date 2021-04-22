#include <iostream>

int main()
	
	{
		
		setlocale (0, "");
		
		int k,och;
		
		std::cout<<"Введите номер k эл-та послед-ти ",std::cin>>k;
		
		int sequence [k+20], doppel, len,copyi;
		bool condition = 1;
		
		copyi = 1;
		for (int i = 1, och = 0; och <= k+5;  i ++)
		
			{
				
				len = 0;
				doppel = i;
				
				while (doppel != 0)
				
					{
						
						doppel /= 10;
						len += 1;
						
					}
				
				int num[len];
				doppel = i;
				
				int a = 0;
				copyi += len;
				while (doppel != 0 & och <= k+5)
				
					{
						
						sequence[copyi - 3 + len - a] = doppel % 10;
						doppel /= 10;
						a +=1 ;
						och += 1;
						
					}
				
				
				
			}
		//		/*
		for (int a = 0; a<=k; a++)	
		std::cout<<"\n a = "<<a<<" sec = "<<sequence[a]<<"\n";
		//		*/
				
		std::cout<<sequence[k-1];
	
		
		std::cin.get();
		return 0;
		
	}
