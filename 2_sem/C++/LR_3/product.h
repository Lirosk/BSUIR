//---------------------------------------------------------------------------

#ifndef productH
#define productH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#include <sstream>
#include <string>

class Product
{
	UnicodeString name;
	UnicodeString mark;
	unsigned int position;
	TDate whenTaken;
	bool isReady;

	public:

	Product(){};
	Product(unsigned int position, UnicodeString name, UnicodeString mark, TDate whenTaken, bool isReady)
	{
		this->position = position;
		this->name = name;
		this->mark = mark;
		this->whenTaken = whenTaken;
        this->isReady = isReady;
    }

	void SetReady(bool isReady)	{ this->isReady = isReady; }
	bool GetReady() { return isReady; }
	unsigned int GetPosition() { return position; }
    UnicodeString GetName() { return name; }


    UnicodeString NumToString(unsigned int a)
	{
		UnicodeString str = "";

		unsigned int len = 0;


		for (unsigned int doppel = a; doppel; doppel /= 10, len++);

		for (unsigned int i = 0; i < len; i++, a /= 10)
		{
			str[i + 1] = a % (unsigned int)pow(10, len - i - 1) + '0';
		}

        str += '\0';

		return str;
	}



	UnicodeString ToString()
	{
		std::stringstream ss;//
		ss << position;
		UnicodeString numU;//
		std::string numS;//
		ss >> numS;
		numU = numS.c_str();

		if (isReady)
		{
		  return numU + " | " + name + " | " + mark + " | " + DateToStr(whenTaken) + " | Ready";
		} return numU + " | " + name + " | " + mark + " | " + DateToStr(whenTaken) + " | Not ready";
	}
};


