#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{

	map <string, string> fuu = {
		{"qu","kv"},{"ce","se"},{"ci","si"},{"cy","sy"},{"w","v"},
	};


	map <string, string> general = {
	{"c","k"},	{"q","k"},
	{"x","ks"},	{"w","v"},	{"ph","f"},
	{"you","u"},{"oo","u"},	{"ee","i"},
	{"th","z"},
	};


	map <string, string> doppel = {
	{"bb","b"},	{"cc","c"},
	{"dd","d"},	{"ff","f"},	{"gg","g"},
	{"hh","h"},	{"jj","j"},	{"kk","k"},
	{"ll","l"},	{"mm","m"},	{"nn","n"},
	{"pp","p"},	{"qq","q"},	{"rr","r"},
	{"ss","s"},	{"tt","t"},	{"vv","v"},
	{"ww","w"},	{"xx","x"},	{"zz","z"},
	};

	string str, first, second;
	int a, b;

	for (int num_of_task = 1; num_of_task++;)
	{
		printf("Enter the string:\n");
		getline(cin, str);

		for (map<string, string>::iterator ser = fuu.begin(); ser != fuu.end(); ser++)	////////////////////////////////////////////////////////////////////////////////////
		{

			first = (ser->first);
			second = (ser->second);

			first[0] = toupper(first[0]);
			second[0] = toupper(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}

			first[0] = tolower(first[0]);
			second[0] = tolower(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}
		}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		for (map<string, string>::iterator ser = general.begin(); ser != general.end(); ser++)///////////////////////////////////////////////////////////////////////////////
		{
			first = (ser->first);
			second = (ser->second);

			first[0] = toupper(first[0]);
			second[0] = toupper(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}

			first[0] = tolower(first[0]);
			second[0] = tolower(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}
		}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		for (map<string, string>::iterator ser = doppel.begin(); ser != doppel.end(); ser++)////////////////////////////////////////////////////////////////////////////////
		{
			first = (ser->first);
			second = (ser->second);

			first[0] = toupper(first[0]);
			second[0] = toupper(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}

			first[0] = tolower(first[0]);
			second[0] = tolower(second[0]);

			a = 5;
			while (a > -1)
			{
				//cout << ser->first<<' ';
				a = str.find(first);
				b = (first).length();
				//cout << " " << a << " " << b << "\n";
				if (a > 0)
				{
					//str.erase(str.find(ser->first), (ser->first).length());
					str.erase(a, b);
					str.insert(a, second);
				}
			}
		}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		cout << "\n" << str << "\n\n\n\n\n\n\n";
	}
	return 0;
}

/*
Too swift for Theex, too quick for Gallow, too strong for young Prince Joseph to follow
*/