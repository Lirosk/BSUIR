#include <iostream>

int main()
{

	char current, supachar;
	char string[81] = {'\n'};
	int len, supalen = 81;

	printf("\nEnter your string:\n");
	gets_s(string);

	for (int i = 0; i < strlen(string);)
	{
		current = string[i];
		len = 0;
		for (int j = i; (j < strlen(string)) & (string[j] == current); j++) { len += 1; }

		i += len;
		if (len > 1)
		{
			if (((i >= strlen(string)) & (len <= supalen)) | (len <= supalen))
			{
				{
					supalen = len;
					supachar = current;
				}
			}
		}
	}

	if (supalen != 81)
	{
		std::cout << "\nThe shortest len of sequense (of " << supachar << " ) is " << supalen << "\n";
	}
	else
	{
		std::cout << "\nNo sequences.\n";
	}

	return 0;
}