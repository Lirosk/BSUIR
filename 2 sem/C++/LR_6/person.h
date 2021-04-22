//---------------------------------------------------------------------------

#include <vcl.h>
#ifndef personH
#define personH
//---------------------------------------------------------------------------
#endif

class person
{
private:
	//name
	UnicodeString name;

    //just number
	long int money;

public:
	//init
	person (UnicodeString name = "", long int money = 0)
	{
		this->name = name;
        this->money = money;
    }

	//to string
	UnicodeString ToString()
	{
		return name + " " + money;
	}

	//return name
	UnicodeString Name()
	{
        return name;
    }

	//operator <
	bool operator<(person a)
	{
		if (this->money < a.money)
		{
			return true;
		}
		return false;
	}

	//operator >
	bool operator>(person a)
	{
		if (this->money > a.money)
		{
			return true;
		}
        return false;
	}

	//operator ==
	bool operator==(person a)
	{
        return (money == a.money);
    }
};

//get person from string
person FromString(UnicodeString str)
{
	UnicodeString strU = "";
	for (unsigned short i = 1; (i <= str.Length()) && (str[i] != '-') &&(str[i] < '0' || str[i] > '9'); i++)
	{
        strU += str[i];
	}

	long int a = 0;
	bool minus = false;

	for (unsigned short i = 1; i <= str.Length(); i++)
	{
		if (str[i] == '-')
		{
			minus = true;
			continue;
		}

		if (str[i] >= '0' && str[i] <= '9')
		{
			a *= 10;
            a += str[i] - 48;
		}
	}

    return person(strU, a * (minus?-1:1));
}
