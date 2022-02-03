#include <iostream>

void fillchange(char letter, char* change, short int seqlen)
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
		change[por + k] = (int)(num / (int)pow(10, numlen - 1 - k)) + '0'; //((int)(num / (int)pow(10, numlen - 1 - k)) == 0)?('0'):((int)(num / (int)pow(10, numlen - 1 - k)) + '0');
		num %= (int)pow(10, numlen - 1 - k);
	}
	por += numlen;

	change[por] = ')'; change[por + 1] = '\0';

}



int main()
{
	char change[25] = { '(','2','5','5',' ' };

	fillchange('b', change, 60);

	printf(change);
	return 0;
}