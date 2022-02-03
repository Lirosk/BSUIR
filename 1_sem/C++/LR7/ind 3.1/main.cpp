#include <iostream>

void strcpy_smy(char* num1, char* num2)
{
	for (int i = 0; i < 8; i++)
	{
		num1[i] = num2[i];
	}

	return;
}

//if num == 0 (but 111111...111..)
bool ifone (char* num)
{
	bool ret = true;
	for (int i = 0; i < 8; i++)
	{
		if (num[i] == '0')
		{
			ret = false;
			break;
		}
	}

	return ret;
}

//Printing the array
void printarray(char* num)
{
	std::cout << "\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << num[i];
	}
	std::cout << "\n";
	return;
}

//Summ of 2 digits, yep
void binsum(char a, char b, char* sumrez)
{
	int sum = (a - '0') + (b - '0');

	sumrez[0] = (sum / 2 + '0');
	sumrez[1] = (sum % 2 + '0');

	return;
}

//Main logical part yep
//I proud of it
//it is my own, personal creation, yep
//it is was created by the forse of my mind
bool ssum(char* num1, char* num2, char* rez, char* sumrez, void  (*binsum) (char, char, char*))
{
	bool plusone = false;
	int por = 7;

	for (int i = 7; i > -1; i--)
	{
		if (plusone) {
			binsum(num1[i], (((num2[i] - '0') + 1) + '0'), sumrez);
			plusone = false;
		}
		else {
			binsum(num1[i], num2[i], sumrez);
		}

		rez[por--] = sumrez[1];

		if (sumrez[0] == '1')
		{
			plusone = true;
		}

	}

	return plusone;

}

//checking the num for right digits
bool check_the_num(char* num)
{
	for (int i = 0; i < 8; i++)
	{
		if (num[i] - '0' > 1)
		{
			std::cout << "\nYour number must be in binary number system.\n";
			return false;
		}
	}

	return true;
}


int main()
{
	char num1[9] = { '\0' }, num2[9] = { '\0' }, rez[9] = { '\0' }, sumrez[2] = { '\0' };
	char num1dop[9] = { '\0' }, num2dop[9] = { '\0' }, one[9] = { '0', '0', '0', '0', '0', '0', '0', '1','\0' };
	char num1obr[9] = { '\0' }, num2obr[9] = { '\0' }, rezobr[9] = { '\0' };
	bool check;

	while (true)
	{
		//Entering and checking first number
		while (true)
		{
			std::cout << "\n\nEnter 1st number of sum (8 bit):\n";
			std::cin >> num1;

			if (check_the_num(num1))
			{
				break;
			}
		}

		//Entering and checking 2nd number
		while (true)
		{
			std::cout << "\nEnter 2nd number of sum (8 bit):\n";
			std::cin >> num2;

			if (check_the_num(num2))
			{
				break;
			}
		}

		//num1!!!!
		//num1 to ones complement bla-bla
		if (num1[0] == '1')
		{
			//replasing ones and zeros
			for (int i = 1; i < 8; i++)
			{
				if (num1[i] == '1')
				{
					num1[i] = '0';
				}
				else
				{
					num1[i] = '1';
				}
			}

			strcpy_smy(num1obr, num1);

			//like if (plusone)
			if (ssum(num1, one, num1dop, sumrez, binsum))
			{
				//adding one if needed
				strcpy_smy(num1, num1dop);
				(ssum(num1, one, num1dop, sumrez, binsum));
			}
		}
		//if number is positive (below zero) it is the same in other repres-ons, right?
		else
		{
			strcpy_smy(num1obr, num1);
			strcpy_smy(num1dop, num1);
		}

		std::cout << "\n\n\n1st number in ones complement rep.:\n";
		printarray(num1obr);

		std::cout << "\n1st number in twos complement rep.:\n";
		printarray(num1dop);

		if (ifone(num1dop))
		{
			strcpy_smy(num1dop, one);
			num1dop[7] = '0';
		}

		//num2!!!!
		//num2 to ones complement bla-bla
		if (num2[0] == '1')
		{
			//replasing ones and zeros
			for (int i = 1; i < 8; i++)
			{
				if (num2[i] == '1')
				{
					num2[i] = '0';
				}
				else
				{
					num2[i] = '1';
				}
			}

			strcpy_smy(num2obr, num2);

			//like if (plusone)
			if (ssum(num2, one, num2dop, sumrez, binsum))
			{
				//adding one if needed
				strcpy_smy(num2, num2dop);
				(ssum(num2, one, num2dop, sumrez, binsum));
			}
		}
		//if number is positive (below zero) it is the same in other repres-ons, right?
		else
		{
			strcpy_smy(num2obr, num2);
			strcpy_smy(num2dop, num2);
		}

		std::cout << "\n\n\n2nd number in ones complement rep.:\n";
		printarray(num2obr);

		std::cout << "\n2nd number in twos complement rep.:\n";
		printarray(num2dop);

		if (ifone(num2dop))
		{
			strcpy_smy(num2dop, one);
			num2dop[7] = '0';
		}

		//Summin part, yep
		//like if (plusone)
		if (ssum(num1dop, num2dop, rez, sumrez, binsum))
		{
			strcpy_smy(rezobr, rez);
			ssum(rezobr, one, rez, sumrez, binsum);
		}
		else
		{
			strcpy_smy(rezobr, rez);
		}

		std::cout << "\n\n\nResult of summ in twos complement rep.:\n";
		printarray(rezobr);

		strcpy_smy(rez, rezobr);

		//Minusing one one (converting to ones complement bla-bla)
		for (int i = 7; i > -1; i--)
		{
			if (rez[i] == '0')
			{
				rez[i] = '1';
			}
			else
			{
				rez[i] = '0';
				break;
			}
		}

		std::cout << "\nResult of summ in ones complement rep.:\n";
		printarray(rez);
	}
	return 0;
}