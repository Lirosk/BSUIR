#include <iostream>
#include <conio.h>

int main()
	{
		
		setlocale (0,"");
		
		std::string s[3];
		const int N = 3;
		int num[N],snum,st,dan;
		std::cout<<"������� ''������'' �����: ",std::cin>>dan;
	
		for (int i = 100;i < 1000; i++)
			
			{
				
				snum = 0;
				st = i;
				
				for (int b = 0; st > 0; b++)
				
					{
						
						num[N-b] = st%10;
						st/=10;
						snum += num[N-b];
						
					}
				
				if (snum==dan)
				
				{
					
					std::cout<<"\n����� ���� ����� "<<i<<" ����� ������� ����� "<<dan;
					
				}

			}
		
		std::cin.get();
		getch();
		return 0;		
	}

