//---------------------------------------------------------------------------

#ifndef HTH
#define HTH
//---------------------------------------------------------------------------
#endif

#ifndef VCL_H
	#include <vcl.h>
#endif



class HashTable
{
private:
	int** table;
	int len;

public:
	//friend void Add(int*&, int);
	//friend void Add(int*&, int, int);
	//friend void Del(int*&, int);
	//friend void ToMemo(HashTable);
	void ToMemo(TMemo*&);

	HashTable()
	{
		len = 10;
		table = new int*[10];
		for (int i = 0; i < len; i++)
		{
            table[i] = new int[0];
		}
    }

	void Add(int num)
	{
		int code =  GetHashCode(num);
		for (int i = 0; i < len; i++)
		{
			if (code == i)
			{
				Add(table[i], num);
                return;
			}
		}
	}

	int GetHashCode(int a)
	{
		return a%10;
	}

	void Add(int*& arr, int num)
	{
		int len = sizeof(arr)/sizeof(int);
		int* ar = new int[len + 1];

		for (int i = 0; i < len; i++)
		{
			*(ar + i) = *(arr + i);
		}

		ar[len] = num;

		delete[] arr;
		arr = ar;
	}


	void Add(int*& arr, int num, int index)
	{
		int len = sizeof(arr) / sizeof(int);

		int* ar = new int[len + 1];

		int i = 0;
		for (; i < index; i++)
		{
			*(ar + i) = *(arr + i);
		}

		ar[i] = num;

		for (; i < len + 1; i++)
		{
			*(ar + i + 1) = *(arr + i);
		}

		delete[] arr;
		arr = ar;
	}

	void Del(int*& arr, int index)
	{
		int len = sizeof(arr)/sizeof(int);

		int* ar = new int[len - 1];

		int i = 0;
		for (; i < index; i++)
		{
			*(ar + i) = *(arr + i);
		}

		for (; i < len - 1; i++)
		{
			*(ar + i) = *(arr + i + 1);
		}

		delete[] arr;
		arr = ar;
	}
};

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


void HashTable::ToMemo(TMemo*& Memo)
{
    Memo->Clear();
    UnicodeString str = "";
	for (int i = 0; i < len; i++)
	{
        str = "";
		str += i;
		str += ": ";
		for (int j = 0; j < sizeof(table[i])/sizeof(int); j++)
		{
			str += table[i][j];
            str += " ";
		}

        Memo->Lines->Add(str);
	}
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

/*
void Add(int*& arr, int num)
{
	int len = sizeof(arr)/sizeof(int);
	int* ar = new int[len + 1];

	for (int i = 0; i < len; i++)
	{
		*(ar + i) = *(arr + i);
	}

	ar[len] = num;

	delete[] arr;
	arr = ar;
}


void Add(int*& arr, int num, int index)
{
	int len = sizeof(arr) / sizeof(int);

	int* ar = new int[len + 1];

	int i = 0;
	for (; i < index; i++)
	{
        *(ar + i) = *(arr + i);
	}

	ar[i] = num;

	for (; i < len + 1; i++)
	{
		*(ar + i + 1) = *(arr + i);
	}

	delete[] arr;
	arr = ar;
}

void Del(int*& arr, int index)
{
	int len = sizeof(arr)/sizeof(int);

	int* ar = new int[len - 1];

	int i = 0;
	for (; i < index; i++)
	{
		*(ar + i) = *(arr + i);
	}

	for (; i < len - 1; i++)
	{
		*(ar + i) = *(arr + i + 1);
	}

	delete[] arr;
	arr = ar;
}

*/
