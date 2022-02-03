#include <iostream>
#include <string>

bool check_the_num(std::string num, int radix)
{
	for (int i = 0; (i < num.size()); i++)
	{
		if (!isdigit(num[i]))
		{
			if ((int(toupper(num[i])) - 55) >= radix)
			{
				std::cout << "\nIncorrect number (your number system doesn't include some digits from your number).\n";
				return 0;
			}
		}
		else if ((num[i] - '0') >= radix)
		{
			std::cout << "\nIncorrect number (your number system doesn't include some digits from your number).\n";
			return 0;
		}
	}
	return 1;
}

int main()
{
	std::string numstr;
	int sys, tosys, len,kolvo;
	unsigned long long num10, doppel;
	bool otr = 0;

	while (1)
	{
		sys = 37;

		//Entering number system
		while ( (sys < 2) | (sys > 36) )
		{
			std::cout << "\n\nEnter the number system [2;36]:\n";
			std::cin >> sys;
		}

		//Entering number
		while (1)
		{
			std::cout << "\nEnter the number in your number system:\n";
			std::cin >> numstr;

			//Checking the number
			if (check_the_num(numstr, sys))
			{
				break;
			}

		}

		//Number under the zero
		if (numstr[0] == '-')
		{
			numstr.erase(0, 1);
			otr = 1;
		}

		//Entering new number system
		tosys = 37;
		while ((tosys < 2) | (tosys > 36))
		{
			std::cout << "\nEnter in which number system [2,36] your number should be:\n";
			std::cin >> tosys;
		}

		len = numstr.size();

		//Decimal number
		num10 = 0;

		for (int i = 0; i < len; i++)
		{
			if (!isdigit(numstr[i]))
			{
				num10 += (int)(toupper(numstr[i]) - 55) * pow(sys, len - i - 1);
				//num10 += ((int)(toupper(numstr[i]) - 55)) * pow(sys, len - i - 1);
				continue;
			}

			num10 += (int)(numstr[i] - '0') * pow(sys, len - i - 1);
			//num10 += (numstr[i] - '0') * pow(sys, len - i - 1);
		}

		if (otr) {
			std::cout << "\nYour decimal number:\n-" << num10 << "\n";
		}
		else {
			std::cout << "\nYour decimal number:\n" << num10 << "\n";
		}

		doppel = num10;
		len = 0;
		
		//Len of decimal number
		while (doppel > 0)
		{
			doppel /= 10;
			len += 1;
		}

		//Len of final number
		kolvo = 0;
		doppel = num10;
		while (doppel > 0)
		{
			doppel /= tosys;
			kolvo += 1;
		}

		numstr = " ";

		//Transfering to new number system
		for (int i = 0; i < kolvo; i++, num10 /= tosys)
		{
			doppel = num10 % tosys;
			if (doppel > 9)
			{
				numstr.insert(0, 1, char(doppel + 55));
				continue;
			}

			numstr.insert(0, 1, (doppel + '0'));
		}

		//Printing final number     
		std::cout << "\nYour number in " << tosys << " number system:\n";
		len = numstr.size();
		if (otr)
		{
			std::cout << "-";
		}
		for (int i = 0; i < len; i++)
		{
			std::cout << numstr[i];
			if (((len - i + 1) % 3 == 0))
			{
				std::cout << " ";
			}
		}

		std::cout << "\n\n\n\n";
	}

	return 0;

}