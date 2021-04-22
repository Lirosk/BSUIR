#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;

class products
{
public:
	string name = "";
	string mark = "";
	string date = "";
	bool isready = 0;

	void scanproduct()
	{
		cout << "\n\nEnter name of product:\n";
		cin >> name;
		cout << "Enter mark of product:\n";
		cin >> mark;
		cout << "Is product ready? ('1' - yes / '0' - n)\n";
		cin >> isready;
		cout << "\n\n";
	}

	void printproduct()
	{
		cout << "\n\n";
		cout << "Name: " << name;
		cout << "Mark: " << mark;
		cout << "Date: " << date;
		cout << "Is ready: ('1' - yes / '0' - no)" << isready;
		cout << "\n\n";
	}

};

void del(products*& array, int &len)
{
	if (len == 0)
	{
		cout << "\n\nNo goods.";
		return;
	}

	while (true)
	{

		cout << "\n\nPrint all products? ('y' - yes / 'n' - no / 'q' - exit):\n";
		char decision;
		cin >> decision;
		if (decision == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				cout << "\nProduct " << i + 1 << "\n";
				array[i].printproduct();
			}
		}
		else if (decision == 'q')
		{
			return;
		}
		else if (decision != 'n')
		{
			cout << "Incorrect input.\n";
			continue;
		}

		break;

	}

	cout << "Which product you want to delete? (Enter 0 to cancel)\n";
	int ord = 0;
	cin >> ord;
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
}

void add(products*& array, int &len)
{
	cout << "\n\nHow many elements need to be added? (Enter 0 to cancel)\n";
	int newel;
	cin >> newel;
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
		cout << "Product " << i + 1 << "\n";
		newarray[i].scanproduct();
	}

	delete[] array;
	array = newarray;
	len += newel;
}

void edit(products*& array,int len)
{
	if (len == 0)
	{
		cout << "\n\nNo goods.";
		return;
	}

	while (true)
	{

		cout << "\n\nPrint all products? ('y' - yes / 'n' - no / 'q' - exit):\n";
		char decision;
		cin >> decision;
		if (decision == 'y')
		{
			for (int i = 0; i < len; i++)
			{
				cout << "\nProduct " << i + 1 << "\n";
				array[i].printproduct();
			}
		}
		else if (decision == 'q')
		{
			return;
		}
		else if (decision != 'n')
		{
			cout << "Incorrect input.\n";
			continue;
		}

		break;

	}

	cout << "Which element you want to edit? (enter 0 to cancel)\n";
	int ord = 0;
	cin >> ord;

	if (ord < 1)
	{
		return;
	}

	ord -= 1;

	array[ord].scanproduct();
}



int main()
{
	int N;
	cout << "How many products there are?\n";
	cin >> N;

	products* array = new products[N];

	ofstream fout;
	fout.open("date.txt");

	if (!fout.is_open())
	{
		cout << "\nCannot to open file.\n";
		return 0;
	}

	fout << "Date";
	fout.close();

	return 0;
}