#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream file("data.txt", std::ios::app);

	if (!file.is_open())
	{
		std::cout << "Cannot open.\n";
		system("pause");
		return 0;
	}

	int N = 0;

	{
		std::string str;

		for (; !file.eof(); N++)
		{
			std::getline(file, str);
		}

	}

	{

	}
	
	std::cout << N;

	return 0;
}