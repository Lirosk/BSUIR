#include <iostream>
#include <string>

bool check_the_num(std::string num)
{
	for (int i = 0; i < num.size(); i++)
	{
		if (num[i] - '0' > 1)
		{
			std::cout << "\nYour number must be in binary number system.\n";
			return 1;
		}
	}

	return 0;
}

int main()
{
	std::string num1;
	int len;
	bool check;

	while (1)
	{
		std::cout << "\n\nEnter your number in two's-complement code (without spaces):\n";
		std::cin >> num1;

		len = num1.size();

		if (check_the_num(num1))
		{
			continue;
		}

		if ((len > 8))
		{
			std::cout << "\nYour number must be in 8-bit representation.\n";
			continue;
		}

		if (num1[0] == '0')
		{
			std::cout << "\nYour number in one's complement code:\n"<<num1<<"\n";
			continue;
		}

		check = true;

		for (int i = 7; i > -1; i--)
		{
			if (num1[i] == '0')
			{
				num1[i] = '1';
			}
			else if (num1[i] == '1')
			{
				num1[i] = '0';
				check = false;
				break;
			}
		}

		//Doesnt need !?
		if (check)
		{
			for (int i = 0; i < 7; i++)
			{
				num1[i] = '1';
			}
			num1[7] = '0';
		}

		std::cout << "\nYour number in one's complement code:\n" << num1 << "\n";
	}


	return 0;
}