#include <iostream>
#include <ctime>
#include <stdlib.h> 
#include <cmath>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
__declspec (dllimport) int prov (int matrix[], int i, int N);



int main() 
{
	
	srand(time(0));
	
	int N;
	printf("Enter the array's size: ");
	std::cin>>N;
	
	int * matrix = new int [N];
	
	printf("|\t");
	for (int i = 0; i < N; i ++)
	{
		matrix[i] = rand()%7-3;
		std::cout<<matrix[i]<<"\t";
	}
	printf("|\n\n");
	

	printf("|");
	prov(matrix,0,N/2);
	prov(matrix,N/2,N);
	printf("\t|\n\n");
	
	
	return 0;
}


