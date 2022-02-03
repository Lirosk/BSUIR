//---------------------------------------------------------------------------

#ifndef HtH
#define HtH
//---------------------------------------------------------------------------
#endif

#ifndef CONTAINER_H
	#include "Ñontainer.h"
#endif CONTAINER_H

#ifndef VCL_H
    #include <vcl.h>
#endif

template<typename T>
class CodeKey
{
public:
	//code
	int code;

	//list of keys
	Container<T> keys;

	//init
	CodeKey()
	{
		code = 0;
		keys = Container<T>();
	}
};

template<typename T>
class Ht
{
public:
	//table
	Container<CodeKey<T>> table;

	//init
	Ht()
	{
		table = Container<CodeKey<T>>();
	}

	//delete
	~Ht()
	{
		if (table.Size())
		{
			table.clear();
		}
	}

	//add key
	void Add(int key)
	{
		if (!table.Size())
		{
			table.push_back(CodeKey<T>());
			table[0].code = GetHashCode(key);

			table[0].keys.push_back(key);

			return;
		}

		int code = GetHashCode(key);
		int i = 0;

		for (; i < table.Size(); i++)
		{
			if (table[i].code == code)
			{
				table[i].keys.push_back(key);
				return;
			}
		}

		table.push_back(CodeKey<T>());
		table[i].code = GetHashCode(key);

		table[i].keys.push_back(key);
	}

	//del key
	void Del(int key)
	{
        int code = GetHashCode(key);

		Container<int>* a;

		for (int i = 0; i < table.Size(); i++)
		{
			if (table[i].code == code)
			{
				a = &table[i].keys;

				for(int j = 0; j < a->Size(); j++)
				{
					if ((*a)[j] == key)
					{
						a->remove(j);
                        return;
					}
                }
			}
		}

        ShowMessage("Not found");
	}

    //clear the table
	void Clear()
	{
		Container<T>* a;
		for (int i = 0; i < table.Size(); i++)
		{
			a = &table[i].keys;
			for (int j = 0; j < a->Size(); j++)
			{
                a->clear();
			}
		}

        table.clear();
    }

	//print hashtable to rich
	void ToRich(TRichEdit*& RichEdit)
	{
		RichEdit->Clear();

        UnicodeString str = "";

		Container<T> a;
		for (int i = 0; i < table.Size(); i++)
		{
            str = "";
			str += table[i].code;
			str += ": ";
			a = table[i].keys;
			for (int j = 0; j < a.Size(); j++)
			{
				str += a[j];
				str += " ";
			}
			RichEdit->Lines->Add(str);
		}
    }

	//return hash code
	int GetHashCode(int key)
	{
		return (key % 10 + 10) % 10;
	}

    //task by variant
	void DelEven()
	{
		Container<T>* a;
		for (int i = 0; i < table.Size(); i++)
		{
			a = &table[i].keys;
			for (int j = 0; j < a->Size(); j++)
			{
				if ((*a)[j] % 2 == 0)
				{
					a->remove(j);
                    j--;
				}
			}
		}
    }
};