#include <iostream>
#include <stdlib.h>
#include <ctime>

int main()
{
	
	srand(time(0));
	
	int n;
    printf("Enter the number of lines & columns: ");
    std::cin>>n;
	int square[n][n];
	//if (n%4 == 0)
		int four[] = {14,-1,-10,8,-6,1,2,-1,2,1,-6,8,-10,-1,14};

    for (int str = 0; str < n; str++)
        for (int st = 0; st < n; st++)
            square[str][st] = 0;

    int firnum = rand() % 15+1;

	if (n%2 == 1)	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
	
    int str = 0, st = (n-1)/2;
    square[str][st] = firnum;

    for (int i = 1; i < n*n; i++)
    {
		    firnum += 1;
    		str -= 1;
    		st += 1;
    		if (str < 0)
   		        str += n;
			if (st > n-1)
    	        st -= n;	

   		    if (square[str][st] == 0)
   		        square[str][st] = firnum;
   		    else
   		    {
   		        str += 2;
   		        st -= 1;
   		        if (str < 0)
   		            str += n;
   		        if (str > n-1)
   		            str -= n;
   		        if (st > n-1)
   		            st -= n;
   		        if (st < 0)
   		            st += n;
    		square[str][st] = firnum;
   			}
		}
	}	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (n%2 == 0)
	{
		if (n%4 == 0)	//-------n%4 == 0
		{
			
			//int firstr = 0, first = 0;
			int fourstr = 4; int fourst = 4; int str = 0; int st = 0; int a = 0;
			
			for (int one = 0; one < n/4; one ++)
			{
				
				
				for (int two = 0; two < n/4; two ++)
				{
					
					
					str = fourstr - 4;
					for (str; str < fourstr; str ++)
					{
						st = fourst - 4;
						for (st; st < fourst; st ++)
						{
							square[str][st] = firnum;
							firnum += four[a];
							firnum = (a>=15)?(firnum - four[a] + 1):firnum;
							a += 1;
						}
					}
					a = 0;
					fourstr += 4;
					
				}
				
				fourstr = 4;
				fourst += 4;
			}
			
			
	}
		
		
		
	}
    //--------------------------------------Printing an array
    std::cout << "\nSquare:\n";
    for (int str = 0; str < n; str++)
    {

        std::cout << "|\t";
        for (int st = 0; st < n; st++)
        {
            std::cout << square[str][st] << "\t";
        }

        std::cout << "|\n\n";
    }

    int sum = 0;
    for (int num = 0; num < n; num ++)
        sum += square[0][num];

    std::cout << "\nMagical const = " << sum << "\n";

    std::cin.get();
    return 0;
}
