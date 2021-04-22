#include <iostream>

void ssub(char* num1, char* num2, char* rez, char* sumrez, int sys, int len, void (*for_positive_result) (char, char, bool, char*, int))
{
	bool minusone = false;
	int por = 0;
	for (int i = len - 1; i > -1; i--)
	{
		if (minusone) {
			for_positive_result(num1[i], num2[i], minusone, sumrez, sys);
			minusone = false;
		}
		else {
			for_positive_result(num1[i], num2[i], minusone, sumrez, sys);
		}
		rez[por++] = sumrez[1];
		if (sumrez[0] == '1')
		{
			minusone = true;
		}
	}

	rez[por] = '\0';

	return;
}

void for_positive_result(char a, char b, bool minusone, char* sumrez, int sys)
{
	int dec;
	if (isdigit(a))
	{
		dec = (a - '0');
	}
	else
	{
		dec = (int(toupper(a)) - 55);
	}
	if (isdigit(b))
	{
		dec -= (b - '0');
	}
	else
	{
		dec -= (int(toupper(b)) - 55);
	}

	if (minusone)
	{
		dec -= 1;
	}

	if (((dec + sys) % sys) > 9)
	{
		sumrez[1] = char(((dec + sys) % sys) + 55);
	}
	else
	{
		sumrez[1] = ((dec + sys) % sys) + '0';
	}

	if (dec < 0)
	{
		sumrez[0] = '1';
	}
	else
	{
		sumrez[0] = '0';
	}

	return;
}

void ssum(char* num1, char* num2, char* rez, char* sumrez, int sys, int len, void (*sum2digits) (char,char,bool,char*,int))
{
	bool plusone = false;
	int por = 0;

	for (int i = len - 1; i > -1; i--)
	{
		if (plusone){ 
			sum2digits(num1[i], num2[i], plusone, sumrez, sys);
			plusone = false;
		}
		else {
			sum2digits(num1[i], num2[i], plusone, sumrez, sys);
		}
		rez[por++] = sumrez[1];
		if (sumrez[0] == '1')
		{
			plusone = true;
		}
	}
	if (plusone)
	{
		rez[por++] = '1';
	}
	rez[por] = '\0';

	return;
}

bool check_num(char* num, int sys, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (isalpha(num[i]))
		{
			if ((int(toupper(num[i])) - 55) >= sys)
			{
				std::cout << "\nIncorrect number.\n";
				return false;
			}
		}
		else
		{
			if ((num[i] - '0') >= sys)
			{
				std::cout << "\nIncorrect number.\n";
				return false;
			}
		}
	}

	return true;
}

void sum2digits(char a, char b, bool plusone, char * sumrez, int sys)
{
	int dec;

	if (isdigit(a))
	{
		dec = (a - '0');
	}
	else
	{
		dec = (int(toupper(a)) - 55);
	}
	if (isdigit(b))
	{
		dec += (b - '0');
	}
	else
	{
		dec += (int(toupper(b)) - 55);
	}

	if (plusone)
	{
		dec += 1;
	}
	sumrez[0] = ((dec / sys) + '0');
	dec %= sys;
	
	if (dec >= 10)
	{
		sumrez[1] = char(dec + 55);
		return;
	}
	else
	{
		sumrez[1] = (dec + '0');
		return;
 	}
}

void reverse(char* num, int len, void (*strcopy)(char *, char *, int))
{
	char* copy = new char[len];
	strcopy(copy, num, len);

	for (int i = 0; i < len; i++)
	{
		num[i] = copy[len - 1 - i];
	}

	return;
}

void strcopy(char* str1,char * str2, int len)
{
	for (int i = 0; i < len; i++)
	{
		str1[i] = str2[i];
	}

	return;
}

void printstr(char* str, int len)
{
	std::cout << "\n";
	for (int i = 0; i < len; i++)
	{
		std::cout << str[i];
	}
	std::cout << "\n";

	return;
}

void exitmy (char* rez, int len,/**/ void  (*strcopy) (char*, char*, int),/**/ void (*reverse) (char* ,int, void (*strcopy) (char*, char*, int) ),/**/ void (*printstr) (char *, int), void (*removezeros) (char *, int))
{
	reverse(rez, len, strcopy);
	std::cout << "\n\nThe result:\n";
	removezeros(rez, len);
	for (len = 0 ; rez[len] != '\0'; len++) {}
	printstr(rez, len);

	return;
}

void addzeros(int len1, int len2, char* num1, char* num2, void (*reverse) (char*, int, void (*strcopy) (char*, char*, int)), void (*strcopy) (char*,char*,int))
{
	if (len1 > len2)
	{
		reverse(num2, len2, strcopy);
		for (int i = len2; i < len1; i++)
		{
			num2[i] = '0';
		}
		num2[len1] = '\0';
		reverse(num2, len1, strcopy);
	}
	else if (len2 > len1)
	{
		reverse(num1, len1, strcopy);
		for (int i = len1; i < len2; i++)
		{
			num1[i] = '0';
		}
		num1[len2] = '\0';
		reverse(num1, len2, strcopy);
	}

	return;
}

void removezeros(char* rez, int len)
{

	int i = 0, seqlen = 0;

	if (rez[0] == '-')
	{
		i += 1;
	}

	for (int j = 0; j < 2; j++)
	{
		if (rez[j] == '0')
		{
			for (len = 0; rez[seqlen + j] == '0'; seqlen++) {}
			break;
		}
	}

	while (true)
	{
		if (rez[i + seqlen] == '\0')
		{
			rez[i] = '\0';
			break;
		}
		rez[i] = rez[i + seqlen];

		i += 1;
	}
	
	if (rez[0] == '\0')
	{
		rez[0] = '0';
		rez[1] = '\0';
	}

	return;
}

int main()
{
	char num1[100], num2[100], rez[101], sumrez[2];
	int sys, len1, len2, len;
	bool check;

	while (true)
	{

		//Entering number system
		while (true)
		{
			std::cout << "\n\nEnter number system [2;36]:\n";
			std::cin >> sys;

			if ((sys > 1) & (sys < 37))
			{
				break;
			}
		}

		//Entering and checking 1st number 
		while (true)
		{
			std::cout << "\nEnter 1st num of sum:\n";
			std::cin >> num1;
			for (len1 = 0; num1[len1] != '\0'; len1++) {}

			if (check_num(num1, sys, len1))
			{
				break;
			}
		}

		{
			char operation = '\0';
			
			while (true)
			{
				std::cout<<"\nEnter the operation (+ or -):\n";
				std::cin>>operation;
				
				if ((operation == '+') | (operation == '-'))
				{
					break;
				}
				
			}
		

			//Entering and checking 2nd number
			while (true)
			{
				std::cout << "\nEnter 2nd num of sum:\n";
				std::cin >> num2;
				for (len2 = 0; num2[len2] != '\0'; len2++) {}

				if (check_num(num2, sys, len2))
				{
					break;
				}
			}
			
			if (operation == '-')
			{
				if (num2[0] == '-')
				{
					num2[0] = '0';
				}
				else
				{
					reverse(num2, len2, strcopy);
					for (int i = 0 ; i > -1; i++ )
					{
						if (num2[i] == '\0')
						{
							num2[i] = '-';
							num2[i + 1] = '\0';
							len2 += 1;
							break;
						}
					}
					reverse(num2, len2, strcopy);
				}
			}
		
		}

		//if numbers are positive
		if ((num1[0] != '-') & (num2[0] != '-'))
		{
			//Adding zeros
			len = (len1 > len2) ? (len1) : (len2);
			addzeros(len1, len2, num1, num2, reverse, strcopy);

			ssum(num1, num2, rez, sumrez, sys, len, sum2digits);

			for (len = 0; rez[len] != '\0'; len++) {}

			exitmy (rez, len, strcopy, reverse, printstr, removezeros);
			continue;
		}
		else if (((num1[0] == '-') & (num2[0] != '-')) | ((num1[0] != '-') & (num2[0] == '-')))
		{
			//num1 < 0
			if (num1[0] == '-')
			{
				num1[0] = '0';
				len = (len1 > len2) ? (len1) : (len2);

				//adding zeros
				addzeros(len1, len2, num1, num2, reverse, strcopy);

				//if number are defferent by sing, but the same by module
				check = true;

				//comparing the number to determine the sign of result
				for (int i = 0; i < len; i++)
				{
					if (num1[i] != num2[i])
					{
						check = false;

						if (isdigit(num1[i]) & (isalpha(num2[i])))//num2 > num1
						{
							ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
						}
						else if (isalpha(num1[i]) & (isdigit(num2[i])))//num1 > num2
						{
							ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
							rez[len++] = '-';
							rez[len] = '\0';
						}
						else if ((isalpha(num1[i])) & (isalpha(num2[i])))
						{
							if (int(num1[i]) > int(num2[i]))//num1 > num2
							{
								ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
								rez[len++] = '-';
								rez[len] = '\0';
							}
							else//num1 < num2
							{
								ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
							}
						}
						else if ((isdigit(num1[i])) & (isdigit(num2[i])))
						{
							if (char(num1[i]) > char(num2[i]))//num1 > num2
							{
								ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
								rez[len++] = '-';
								rez[len] = '\0';
							}
							else//num2 > num1
							{
								ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
							}
						}
						break;
					}
				}

				//if number are defferent by sing, but the same by module
				if (check)
				{
					ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
				}

			}
			//if num2 < 0
			else
			{
				num2[0] = '0';
				len = (len1 > len2) ? (len1) : (len2);

				//adding zeros
				addzeros(len1, len2, num1, num2, reverse, strcopy);

				//comparing the number to determine the sign of result
				for (int i = 0; i < len; i++)
				{
					if (num1[i] != num2[i])
					{
						if (isdigit(num1[i]) & (isalpha(num2[i])))//num2 > num1
						{
							ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
							rez[len++] = '-';
							rez[len] = '\0';
						}
						else if (isalpha(num1[i]) & (isdigit(num2[i])))//num1 > num2
						{
							ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
						}
						else if ((isalpha(num1[i])) & (isalpha(num2[i])))
						{
							if (int(num1[i]) > int(num2[i]))//num1 > num2
							{
								ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
							}
							else//num2 > num1
							{
								ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
								rez[len++] = '-';
								rez[len] = '\0';
							}
						}
						else if ((isdigit(num1[i])) & (isdigit(num2[i])))
						{
							if (char(num1[i]) > char(num2[i]))//num1 > num2
							{
								ssub(num1, num2, rez, sumrez, sys, len, for_positive_result);
							}
							else//num2 > num1
							{
								ssub(num2, num1, rez, sumrez, sys, len, for_positive_result);
								rez[len++] = '-';
								rez[len] = '\0';
							}
						}
						break;
					}
				}
			}
		}
		else //if both of numbers negative
		{
			num1[0] = '0';
			num2[0] = '0';

			len = (len1 > len2) ? (len1) : (len2);

			//Adding zeros
			addzeros(len1, len2, num1, num2, reverse, strcopy);

			//Taking summ, later it will be multiplied by -1
			ssum(num1, num2, rez, sumrez, sys, len, sum2digits);

			for (len = 0; rez[len] != '\0'; len++) {}
			//Adding minus to negative number
			rez[len++] = '-';
			rez[len] = '\0';
		}

		exitmy(rez, len, strcopy, reverse, printstr, removezeros);

		//start programm again
		continue;
	}

	return 0;
}
