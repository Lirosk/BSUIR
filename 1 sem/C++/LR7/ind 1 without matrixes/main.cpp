#include <iostream>

int main()
{
	int sys, num, doppel, len, num10, kolvo, tosys, ost;

	while (1)
	{
		//Entering number system
		sys = 0;
		while ((sys < 2) | (sys > 10))
		{
			std::cout << "\n\n\nEnter the number system [2;10]:\n";
			std::cin >> sys;
		}

		//Entering number
		while (1)
		{

			std::cout << "\nEnter your number:\n";
			std::cin >> num;

			//Cheking the digits of the number
			doppel = num;
			for (len = 0; doppel > 0; len++, doppel /= 10)
			{
				if (doppel % 10 >= sys)
				{
					std::cout << "\nAll digits of your number must be < number system.\n";
					break;
				}
			}

			if (!(doppel > 0))
			{
				break;
			}
		}

		//Entering number system
		tosys = 37;
		while ((tosys < 2) | (tosys > 36))
		{
			std::cout << "\nEnter in which number system [2,36] your number should be:\n";
			std::cin >> tosys;
		}

		//Decimal number
		num10 = 0;
		for (int i = 1; i <= len; i++)
		{
			num10 += ((num / (int)pow(10, len - i)) % 10) * (int)pow(sys, len - i);
		}

		std::cout << "\nYour decimal number:\n" << num10 << "\n";

		kolvo = 0;
		doppel = num10;

		//Lenght of final number
		for (doppel = num10; doppel > 0; doppel /= tosys, kolvo++) {}
		doppel = num10;

		std::cout << "\nYour number in " << tosys << " number system:\n";

		//Transfering from decimal to system number
		for (int i = kolvo; i > 0; i--)
		{

			//Taking the remainder of the division
			doppel = num10;
			for (int j = 1; j <= i; j++, doppel/=tosys)
			{
				ost = doppel % tosys;
			}

			//If remainder of the division is > 9

			if (ost > 9)
			{
				std::cout << char(ost + 55);
			}
			
			//If the remainder of the division is < 10
			else
			{
				std::cout << ost;
			}

		}

		std::cout << "\n\n\n\n\n\n";

	}

	return 0;
}