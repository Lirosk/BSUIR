#include <iostream>

int main()
{
	int num1, num2, num3, num, doppel;

	while (true)
	{

		std::cout << "\n\nEnter the numbers must be checked:\n";
		std::cin >> num1 >> num2 >> num3;

		std::cout << "\n\nEnter you number for checking:\n";
		std::cin >> num;

		num = (num < 0) ? (num - num - num) : (num);
		num1 = (num1 < 0) ? (num1 - num1 - num1) : (num1);
		num2 = (num2 < 0) ? (num2 - num2 - num2) : (num2);
		num3 = (num3 < 0) ? (num3 - num3 - num3) : (num3);

		doppel = num;

		if (num1 != 0)
		while (doppel > 0)
		{
			doppel -= num1;
		}

		if (((doppel == 0) | (num1 == 1)) & (num1 != 0))
		{
			std::cout << "\nnum1 is a devider of your number\n";
		}
		else
		{
			std::cout << "\nnum1 is not a devider.\n";
		}

		doppel = num;

		if (num2 != 0)
		while (doppel > 0)
		{
			doppel -= num2;
		}

		if (((doppel == 0) | (num2 == 1)) & (num2 != 0))
		{
			std::cout << "\nnum2 is a devider of your number\n";
		}
		else
		{
			std::cout << "\nnum2 is not a devider.\n";
		}

		doppel = num;

		if (num3 != 0)
		while (doppel > 0)
		{
			doppel -= num3;
		}

		if ( ((doppel == 0) | (num3 == 1)) & ((num3 != 0)) )
		{
			std::cout << "\nnum3 is a devider of your number\n";
		}
		else
		{
			std::cout << "\nnum3 is not a devider.\n";
		}


	}



	return 0;
}