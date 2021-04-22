#include <iostream>


int main()
{
	//greka was driving through the river

	char string[81], change[16];
	int len, prov = 0, lenchange = 0, lenstring = 0;

	printf("Enter the string:\n");
	gets_s(string);
	printf("\nEnter the substring:\n");
	gets_s(change);
	printf("\nEnter the size of elements must be changed:\n");
	std::cin >> len;
	
	for (lenchange; change[lenchange] != '\0'; lenchange++) {}
	for (lenstring; string[lenstring] != '\0'; lenstring++)	{}

	std::cout << '\n' << lenchange << '\n' << lenstring << '\n';

	for (int i = 0; i < sizeof(string); i++)
	{
		if ((string[i] != ' ') & (string[i] != '\0') & (string[i] != NULL))
		{
			prov += 1;
			std::cout << string[i];
		}
		else
		{
			std::cout << ' ' << prov << '\n';
			if ((prov == len))
			{
				
				if ((lenchange > len))
				{
					for (int j = sizeof(string)-1; j > i; j--)	//			shift
					{
						string[j] = string[j - (lenchange - len)];
					}

					for (int j = 0; j < lenchange; j ++)		//			change
					{
						string[i - len + j] = change[j];
					}
				}

				else if ((lenchange == len))
				{
					for (int j = 0; j < len; j++)				//			change
					{
						string[i - len + j] = change[j];
					}
				}

				else if ((lenchange < len))
				{
					for (int j = i; j < sizeof(string); j++)	//			shift
					{
						string[j - len + lenchange] = string[j];
					}

					for (int j = 0; j < lenchange; j++)			//			change
					{
						string[i - len + j] = change[j];
					}

					i -= len - lenchange;
				}
			}

			prov = 0;
		}
	}

	std::cout<<'\n';
	std::cout << string;

	std::cin.get();
	return 0;
}