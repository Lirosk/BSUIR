#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

class products
{
public:
	std::string name = "";
	std::string mark = "";
	std::string date = "";
	std::string readiness = "";

	void scan()
	{
		std::cout << "\n\nEnter name of product\n";
		//std::cin >> name;
		getchar();
		getline(std::cin, name);
		std::cout << "Enter mark of your product\n";
		//std::cin >> mark;
		getchar();
		getline(std::cin, mark);
		std::cout << "Enter date of taking product\n";
		std::cin >> date;
		std::cout << "Your product ready? (true/false)\n";
		std::cin >> readiness;
		std::cout << "\n\n";
	}

	void print()
	{
		std::cout << std::setw(22)<<std::left <<name
			<< std::setw(22) << mark
			<< std::setw(22) << date
			<< std::setw(6) << readiness<<"#\n";
	}
};

void add(products*& array, int& len, void (*printtofile) (products*, int))
{
	std::cout << "\n\nHow many elements need to be added? (Enter 0 to cancel)\n";
	int newel;
	std::cin >> newel;
	std::cout << "\n\n\n";
	if (newel < 1)
	{
		return;
	}

	products* newarray = new products[len + 1];

	for (int i = 0; i < len; i++)
	{
		newarray[i] = array[i];
	}

	for (int i = len; i < len + newel; i++)
	{
		std::cout << "Product " << i + 1 << "\n";
		newarray[i].scan();
	}

	delete[] array;
	array = newarray;
	len += newel;

	printtofile(array, len);
}

void del(products*& array, int& len, void(*printall)(products*,int), void (*printtofile) (products*, int))
{
	if (len == 0)
	{
		std::cout << "\n\nNo products.";
		return;
	}

	while (true)
	{
		std::cout << "\nPrint all roducts again? ('y' - yes / 'n' - no / 'q' - exit)\n";
		char decision = ' ';
		std::cin >> decision;

		if (decision == 'y')
		{
			printall(array, len);
			break;
		}
		else if (decision == 'n')
		{
			break;
		}
		else if (decision == 'q')
		{
			return;
		}
		else
		{
			std::cout << "\nIncorrect input.\n";
			system("pause");
			system("cls");
			continue;
		}

	}

	std::cout << "Which product you want to delete? (Enter 0 to cancel)\n";
	int ord = 0;
	std::cin >> ord;
	if (ord < 1)
	{
		return;
	}
	ord -= 1;

	products* newarray = new products[len - 1];

	for (int i = 0; i < ord; i++)
	{
		newarray[i] = array[i];
	}

	for (int i = ord; i < len - 1; i++)
	{
		newarray[i] = array[i + 1];
	}

	delete[] array;
	array = newarray;
	len -= 1;

	printtofile(array, len);
}

void finddate(products* array, int len)
{
	std::cout << "Enter current date:\n";
	std::string str;
	std::cin >> str;
	bool havent = true;

	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n";

	std::cout << std::left << std::setw(13) << "# No" << std::setw(22) << "Name"
		<< std::setw(22) << "Mark"
		<< std::setw(22) << "Date"
		<< /*std::setw(13) <<*/ "Ready #\n";

	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n";

	/*
	for (int i = 0; i < len; i++)
	{
		std::cout << "# " << std::setw(11) << i + 1;
		array[i].print();
	}
	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n\n";
	*/

	for (int i = 0, j = 0; i < len; i++)
	{
		//std::cout << array[i].date << "\n";
		if (str == array[i].date)//(strcmp(&str[0], &(((array[i]).name)[0])) == 0)
		{
			std::cout << "# " << std::setw(11) << ++j;
			array[i].print();
			havent = false;
		}
	}

	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n\n";

	if (havent)
	{
		system("cls");
		std::cout << "No products.\n";
	}
}

void edit(products*& array, int len, void(*printall)(products*, int), void (*printtofile) (products*, int))
{
	if (len == 0)
	{
		std::cout << "\n\nNo products.";
		return;
	}

	while (true)
	{
		std::cout << "\nPrint all roducts again? ('y' - yes / 'n' - no / 'q' - exit)\n";
		char decision = ' ';
		std::cin >> decision;

		if (decision == 'y')
		{
			printall(array, len);
			break;
		}
		else if (decision == 'n')
		{
			break;
		}
		else if (decision == 'q')
		{
			return;
		}
		else
		{
			std::cout << "\nIncorrect input.\n";
			system("pause");
			system("cls");
			continue;
		}
	}

	std::cout << "Which element you want to edit? (enter 0 to cancel)\n";
	int ord = 0;
	std::cin >> ord;

	if (ord < 1)
	{
		return;
	}

	ord -= 1;

	array[ord].scan();

	printtofile(array, len);
}

void sort(products*& array, int len, void(*printall)(products*, int), void (*printtofile) (products*, int))
{

	for (int i = 0; i < len; i++)
	{
		short min = int(toupper(array[i].name[0]));
		short ord = 0;
		products temp;

		for (int j = i; j < len; j++)
		{
			short tempchar = int(toupper(array[j].name[0]));
			if (tempchar <= min)
			{
				min = tempchar;
				ord = j;
				temp = array[ord];
			}
		}

		for (int j = ord; j > i; j--)
		{
			array[j] = array[j - 1];
		}

		array[i] = temp;
	}

	printall(array, len);
	printtofile(array, len);
}

void printall(products* array, int len)
{
	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n";

	std::cout << std::left << std::setw(13) << "# No" << std::setw(22) << "Name"
		<< std::setw(22) << "Mark"
		<< std::setw(22) << "Date"
		<< /*std::setw(13) <<*/ "Ready #\n";

	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n";

	for (int i = 0; i < len; i++)
	{
		std::cout << "# " << std::setw(11) << i + 1;
		array[i].print();
	}
	for (int i = 0; i < 86; i++) std::cout << "#";
	std::cout << "\n\n";
}

void printtofile(products* array, int len)//, std::ofstream& output)
{
	std::ofstream output;
	output.open("output.txt", std::ios::app);

	for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
	output << "\n";//std::cout << "\n";

	output <<std::left<<std::setw(13)<< "# No" << std::setw(22) << "Name"
		<< std::setw(22) << "Mark"
		<< std::setw(22) << "Date"
		<< /*std::setw(13) <<*/ "Ready #\n";

	for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
	output << "\n";//std::cout << "\n";

	for (int i = 0; i < len; i++)
	{
		output << "#" << std::setw(11) << i + 1;//std::cout << "# " << std::setw(11) << i + 1;
		//array[i].print();

		output << std::setw(22) << std::left << array[i].name
			<< std::setw(22) << array[i].mark
			<< std::setw(22) << array[i].date
			<< std::setw(6) << array[i].readiness << "#\n";

	}
	for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
	output << "\n\n\n";//std::cout << "\n\n";

	output.close();
}

int main()
{
	int len = 0;

	std::ifstream datat("datat.txt", std::ios::app);
	//datat.open( "datat.txt", std::ios::app);

	if (!datat.is_open())
	{
		std::cout << "\nCannot open the file\n";
		system("pause");
		return 0;
	}

	std::string str = "";

	for (len = 0; !datat.eof(); len++) { std::getline(datat, str); }
	len = (len + 1) / 5;

	datat.seekg(0);

	products* array = new products[len];

	str = "";

	{
		int productord = 0;
		for (int i = 1; !datat.eof(); i++)
		{

			str = "";
			std::getline(datat, str);

			if (i % 5 == 1)
			{
				array[productord].name = str;
			}
			else if (i % 5 == 2)
			{
				array[productord].mark = str;
			}
			else if (i % 5 == 3)
			{
				array[productord].date = str;
			}
			else if (i % 5 == 4)
			{
				array[productord].readiness = str;
			}

			if (i % 5 == 0)
			{
				productord += 1;
			}
			//datat >> str;
			//array[i].name = str;
		}
	}

	datat.close();

	printtofile(array, len);

	while (true)
	{
		char selection = '\0';
		//bool exit = false;

		std::cout << "Enter 'a' if you want to add 1 element.\n";
		std::cout << "Enter 'd' if you want to delete 1 element.\n";
		std::cout << "Enter 'e' if you want to edit 1 element.\n";
		std::cout << "Enter 's' if you want to sort produts\n";
		std::cout << "Enter 'p' if you want to print all products.\n";
		std::cout << "Enter 'r' if you want to print reparied products\n";
		std::cout << "Enter 'c' if you want to clean the output file\n";
		std::cout << "Enter 'm' if ypu want to print products by date\n";
		std::cout << "Enter 'q' if you wand to exit program...\n";

		std::cin >> selection;

		std::cout << "\n";

		system("pause");
		system("cls");

		bool exit = false;

		if (selection == 'a')
		{
			add(array, len, printtofile);
		}
		else if (selection == 'd')
		{
			del(array, len, printall, printtofile);
		}
		else if (selection == 'e')
		{
			edit(array, len, printall, printtofile);
		}
		else if (selection == 's')
		{
			sort(array, len, printall, printtofile);
		}
		else if (selection == 'q') {
			exit = true;
		}
		else if (selection == 'p')
		{
			printtofile(array, len);
			printall(array, len);
		}
		else if (selection == 'm')
		{
			finddate(array, len);
		}
		else if (selection == 'c')
		{
			std::ofstream output;
			output.open("output.txt");
			output.close();
		}
		else if (selection == 'r')
		{
			for (int i = 0; i < 86; i++) std::cout << "#";
			std::cout << "\n";

			std::cout << std::left << std::setw(13) << "# No" << std::setw(22) << "Name"
				<< std::setw(22) << "Mark"
				<< std::setw(22) << "Date"
				<< /*std::setw(13) <<*/ "Ready #\n";

			for (int i = 0; i < 86; i++) std::cout << "#";
			std::cout << "\n";

			for (int i = 0, j = 0; i < len; i++)
			{
				if (strcmp((&array[i].readiness[0]), "true") == 0)
				{
					std::cout << "# " << std::setw(11) << ++j;
					array[i].print();
				}
			}
			for (int i = 0; i < 86; i++) std::cout << "#";
			std::cout << "\n\n";





			
			std::ofstream output;
			output.open("output.txt", std::ios::app);

			for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
			output << "\n";//std::cout << "\n";

			output << std::left << std::setw(13) << "# No" << std::setw(22) << "Name"
				<< std::setw(22) << "Mark"
				<< std::setw(22) << "Date"
				<< /*std::setw(13) <<*/ "Ready #\n";

			for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
			output << "\n";//std::cout << "\n";

			for (int i = 0, j = 0; i < len; i++)
			{
				if (strcmp(&array[i].readiness[0], "true") == 0)
				{
					output << "#" << std::setw(11) << ++j;//std::cout << "# " << std::setw(11) << i + 1;
					//array[i].print();

					output << std::setw(22) << std::left << array[i].name
						<< std::setw(22) << array[i].mark
						<< std::setw(22) << array[i].date
						<< std::setw(6) << array[i].readiness << "#\n";
				}
			}
			for (int i = 0; i < 86; i++) output << "#";//std::cout << "#";
			output << "\n\n\n";//std::cout << "\n\n";

			output.close();

		}
		else {
			std::cout << "Input is incorrect.\n";
			continue;
		}

		if (exit)
		{
			break;
		}

		system("pause");
		system("cls");

	}

	delete[] array;
	system("pause");

	return 0;
}