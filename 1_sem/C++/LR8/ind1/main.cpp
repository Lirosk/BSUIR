#include <iostream>
#include <string>
//#include <stdio.h>
#include <cstdlib>
#include <cstring>

using std::cin;
using std::cout;
using std::string;

struct goods {
	string name = "";
	long long int amount = 0;
	double price = 0.0;
	string date = "";
	bool checked = 0;

	

	void printstruct()
	{
		cout << "Name: " << name << "\n";
		cout << "Amount: " << amount << "\n";
		cout << "Price: " << price << "\n";
		cout << "Date: " << date << "\n";
		cout << "Are chekced: ";
		(checked) ? (cout << "true \n\n\n\n") : (cout << "false \n\n\n\n");
	}

	void scanstruct()
	{
		cout << "Name: ";
		cin >> name;
		cout << "Amount: ";
		cin >> amount;
		cout << "Price: ";
		cin >> price;
		cout << "Date: ";
		cin >> date;
		cout << "Are checked (1 - true / 0 - false): ";
		cin >> checked;
		cout << "\n\n\n\n";
	}

/*
	void findname(string str)
	{
		if (strcmp(&str[0], &name[0]) == 0)
		{
			printstruct();
		}
	}

	void findamount(int checkamount)
	{
			if (checkamount == amount)
			{
				printstruct();
			}	
	}

	void findprice(double checkprice)
	{
		if (checkprice == price)
		{
			printstruct();
		}

	}

	void finddate(string str)
	{
		if (strcmp(&str[0], &date[0]) == 0)
		{
			printstruct();
		}
	}

	void findchecked(bool checkchecked)
	{
		if (checkchecked == checked)
		{
			printstruct();
		}
	}
*/

};

void findname(goods* array, int len)
{
	string str = "";
	cout << "Enter name of your product:\n";
	cin >> str;
	bool found = true;

	for (int i = 0; i < len; i++)
	{
		if ( strcmp(&str[0], &(((array[i]).name)[0]) )  ==  0)
		{
			array[i].printstruct();
			found = false;
		}
	}

	if (found)
	{
		cout << "Not found.\n\n";
	}
}

void findamount(goods* array, int len)
{
	int amount = 0;
	cout << "Enter amount of your goods:\n";
	cin >> amount;
	bool found = true;

	for (int i = 0; i < len; i++)
	{
		if (amount == (array[i]).amount)
		{
			array[i].printstruct();
			found = false;
		}
	}

	if (found)
	{
		cout << "Not found.\n\n";
	}
}

void findprice(goods* array, int len)
{
	double price = 0.0;
	cout << "Enter price of your product:\n";
	cin >> price;
	bool found = true;

	for (int i = 0; i < len; i++)
	{
		if (price == (array[i]).price)
		{
			array[i].printstruct();
			found = false;
		}
	}

	if (found)
	{
		cout << "Not found.\n\n";
	}
}

void finddate(goods* array, int len)
{
	string date = "";
	cout << "Enter date of your product:\n";
	cin >> date;
	bool found = true;

	for (int i = 0; i < len; i++)
	{
		if (strcmp(&date[0], &(((array[i]).date)[0])) == 0)
		{
			array[i].printstruct();
			found = false;
		}
	}

	if (found)
	{
		cout << "Not found.\n\n";
	}
}

void findchecked(goods* array, int len)
{
	bool checked = false, found = true;
	cout << "Is your product i checked?\n'1' - yes / '0' - no\n";
	cin >> checked;

	for (int i = 0; i < len; i++)
	{
		if (checked == (array[i]).checked)
		{
			array[i].printstruct();
			found = false;
		}
	}

	if (found)
	{
		cout << "Not found.\n\n";
	}
}

void add(goods*& array, int& len)
{
	cout << "How many elements need to be added?\n";
	int newel = 0;
	cin >> newel;
	cout << "\n";

	goods* newarray = new goods[newel + len];

	for (int i = 0; i < len; i++)
	{
		newarray[i] = array[i];
	}

	for (int i = len; i < len + newel; i++)
	{
		cout << "Product " << i + 1<<"\n";
		newarray[i].scanstruct();
	}

	delete[] array;
	array = newarray;
	//delete[] newarray;
	len += newel;
}

void del(goods*& array, int& len)
{
	if (len == 0)
	{
		cout << "No goods.\n";
		return;
	}

	cout << "Print all the goods again?\ny - yes / n - no\n";
	char* choose = new char;
	cin >> *choose;
	cout << "\n";

	if (*choose == 'y')
	{
		for (int i = 0; i < len; i++)
		{
			cout << "Product " << i + 1 << ":\n";
			array[i].printstruct();
		}
	}

	delete choose;

	cout << "Which product need to be removed (1,2,...,"<<len<<")?\nEnter 0 to cancel the operatin.\n";
	int ordnum = 0;
	cin >> ordnum;

	if (ordnum < 1)
	{
		return;
	}

	ordnum -= 1;

	goods* newarray = new goods[len - 1];

	for (int i = 0; i < ordnum; i++)
	{
		newarray[i] = array[i];
	}

	for (int i = ordnum; i < len - 1; i++)
	{
		newarray[i] = array[i + 1];
	}

	delete[] array;
	array = newarray;
	//delete[] newarray;
	len -= 1;
}

void edit(goods*& array, int len)
{
	if (len == 0)
	{
		cout << "No goods.\n";
		return;
	}

	{
		cout << "Print all the goods again?\ny - yes / n - no\n";
		//char* choose = new char;
		char choose = ' ';
		cin >> choose;

		if (choose == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				cout << "Product " << i + 1 << ":\n";
				array[i].printstruct();
			}
		}

		//delete choose;
	}

	cout << "Which product need to be removed (1,2,...," << len << ")?\nEnter 0 to cancel the operatin.\n";
	int ordnum = 0;
	cin >> ordnum;

	if (ordnum < 1)
	{
		return;
	}

	ordnum -= 1;

	array[ordnum].scanstruct();
}

void sort(goods*& array, int len)
{

	for (int i = 0; i < len; i++)
	{
		long double max = (array[i].price)*(array[i].amount);
		int ord = 0;
		goods temp;

		for (int j = i; j < len; j++)
		{
			long double lastprice = (array[j].price) * (array[j].amount);
			if (lastprice >= max)
			{
				max = lastprice;
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
}

void printmain(goods* array, int len)
{
	bool have = true;
	for (int i = 0, j = 0; i < len; i++)
	{
		if (array[i].price * array[i].amount >= 100000)
		{
			std::cout << "\nProduct " << ++j << "\n";
			array[i].printstruct();
			have = false;
		}
	}

	if (have)
	{
		cout << "\nNo such goods.\n";
	}
}

int main()
{
	int len = 0;


	cout << "Numbers of elemets of array: ";
	cin >> len;

	goods* array;

	if (len != 0)
	{
		array = new goods[len];

		for (int i = 0; i < len; i++)
		{
			cout << "\nProduct " << i + 1 << "\n";
			array[i].scanstruct();
		}
	}
	else
	{
		array = nullptr;
	}

	//goods* array = nullptr;

	system("pause");
	system("cls");

	while (true)
	{
		char selection = '\0';
		//bool exit = false;

		cout << "Enter 'a' if you want to add 1 element.\n";
		cout << "Enter 'd' if you want to delete 1 element.\n";
		cout << "Enter 'e' if you want to edit 1 element.\n";
		cout << "Enter 's' if you want to sort goods.\n";
		cout << "Enter 'f' if you want to find the product (by criterion).\n";
		cout << "Enter 'p' if you want to print all goods.\n";
		cout << "Enter 'm' if you want to print goods with price > 100000\n";
		cout << "Enter 'q' if you wand to exit program...\n";

		cin >> selection;


		bool exit = false;

		if (selection == 'a')
		{
			add(array, len);
		}
		else if (selection == 'd')
		{
			del(array, len);
		}
		else if (selection == 'e')
		{
			edit(array, len);
		}
		else if (selection == 's')
		{

			sort(array, len);
		}
		else if (selection == 'f')
		{
			while (true)
			{
				if (len == 0)
				{
					cout << "No goods.\n";
					break;
				}
				//bool exit = false;
				system("cls");
				cout << "Enter criterion:\n";
				cout << "name - 'n'\namount - 'a'\nprice - 'p'\ndate - 'd'\nare checked - 'c'\ncancel - 'q'\n";
				char choose;
				cin >> choose;

				if (choose == 'n') {
					findname(array, len);
				}
				else if (choose == 'a') {
					findamount(array, len);
				}
				else if (choose == 'p') {
					findprice(array, len);
				}
				else if (choose == 'd') {
					finddate(array, len);
				}
				else if (choose == 'c') {
					findchecked(array, len);
				}
				else if (choose == 'q') {
					//exit = true;
					break;
				}
				else {
					cout << "Incorrect input.\n\n";
					system("pause");
					continue;
				}
/*
				if (exit)
				{
					break;
				}
*/
				system("pause");

			}
		}
		else if (selection == 'm')
		{
			printmain(array, len);
		}
		else if (selection == 'q') {
			//exit = true;
			break;
		}
		else if (selection == 'p')
		{
			for (int i = 0; i < len; i++)
			{
				cout << "\nProduct " << i + 1 << "\n";
				array[i].printstruct();
			}
		}
		else {
			cout << "Input is incorrect.\n";
			continue;
		}
/*
		if (exit)
		{
			break;
		}
*/



		system("pause");
		system("cls");

	}

	delete[] array;
	return 0;
}