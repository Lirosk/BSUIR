#include <iostream>

using std::cin;
using std::cout;

int main()
{
	//our array
	int A[5][7]; 

	//1st value is sum, 2nd is line of sum
	//no value greater than max
	int smin[2] = { INT_MAX , 0};
	//no value less then min
	int smax[2] = { INT_MIN , 0};

	//for counting sum of line
	int buf = 0;

	//getting the array and sums
	//going through the lines
	for (int i = 0; i < 5; i++)
	{
		//zeroing to count sum of new line
		buf = 0;

		//getting through the columns
		for (int j = 0; j < 7; j++)
		{
			//entering the value
			cin >> A[i][j];

			//counting the sum of line
			buf += A[i][j];
		}

		//checking if sum of current line is the smallest
		if (buf < smin[0])
		{
			//1st value for sum
			smin[0] = buf;
			//2nd for line of sum
			smin[1] = i;
		}
		//checking if sum of current line is the greatest
		if (buf > smax[0])
		{
			//1st value for sum
			smax[0] = buf;
			//2nd for line of sum
			smax[1] = i;
		}
	}

	//printing the array
	//going through the lines
	for (int i = 0; i < 5; i++)
	{
		//going through the columns
		for (int j = 0; j < 7; j++)
		{
			//printing current element
			cout << A[i][j] << "\t";
		}

		//for printing new line for array elements
		cout << "\n";
	}

	//printing min sum and its line
	cout << "min: " << smin[0] << "\t line: " << smin[1] << "\n";
	//printing max sum and its line
	cout << "max: " << smax[0] << "\t line: " << smax[1] << "\n";

	return 0;
}