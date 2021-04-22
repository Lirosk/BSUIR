#include <iostream>

int fillchange(char letter, char* change, short int seqlen)
{
	for (int k = 5; k < 24; k++)
	{
		change[k] = ' ';
	}

	int numlen, num = (int)letter, por = 5;
	for (numlen = 0; num > 0; numlen++)
	{
		num /= 10;
	}

	num = (int)letter;

	for (int k = 0; k < numlen; k++)
	{
		change[por + k] = num / (int)pow(10, numlen - 1 - k) + '0';
		num %= (int)pow(10, numlen - 1 - k);
	}

	por += numlen;

	change[por] = ' '; por += 1;

	num = seqlen;
	for (numlen = 0; num > 0; numlen++)
	{
		num /= 10;
	}
	num = seqlen;

	for (int k = 0; k < numlen; k++)
	{
		change[por + k] = (int)(num / (int)pow(10, numlen - 1 - k)) + '0';
		num %= (int)pow(10, numlen - 1 - k);
	}
	por += numlen;

	change[por] = ')'; change[por + 1] = '\0';

	return por + 1;
}



int main()
{
	while (1)
	{
		char change[21] = { '(','2','5','5',' ' };

		const int N = 5, M = 100;
		char array[N][M + 1] = { '\0' }, doppel;
		int seqlen, lenchange;

		for (int i = 0; i < N; i++)
		{
			std::cout << "Enter the " << i + 1 << " line of array:\n";
			gets_s(array[i]);

			for (int j = 0; array[i][j] != '\0'; j++)
			{

				doppel = array[i][j];
				for (seqlen = 0; array[i][j + seqlen] == doppel; seqlen++) {}
				j += seqlen - 1;
				if (seqlen == 1) continue;
				lenchange = fillchange(doppel, change, seqlen);

				if (lenchange > seqlen)	//////////////////////////////////////////////////////////////////////
				{
					for (int k = sizeof(array[i]) - 1; k > j - seqlen; k--)
					{
						array[i][k + (lenchange - seqlen)] = array[i][k];
					}

					for (int k = 0; k < lenchange; k++)
					{
						array[i][j - seqlen + 1 + k] = change[k];
					}
				}
				else if (lenchange < seqlen)	//////////////////////////////////////////////////////////////
				{
					for (int k = j - seqlen + 1; k < sizeof(array[i]) - 1; k++)
					{
						array[i][k] = array[i][k - lenchange + seqlen];
					}

					for (int k = 0; k < lenchange; k++)
					{
						array[i][j - seqlen + 1 + k] = change[k];
					}
				
				}
				else	///////////////////////////////////////////////////////////////////////////////////
				{

					for (int k = 0; k < lenchange; k++)
					{
						array[i][j - seqlen + 1 + k] = change[k];
					}
				
				}

				j += lenchange - seqlen;

			}

		}

		for (int i = 0; i < N; i++)
		{
			printf(array[i]);
			printf("\n");
		}

		printf("\n\n\n\n\n\n");

	}
	return 0;
}
