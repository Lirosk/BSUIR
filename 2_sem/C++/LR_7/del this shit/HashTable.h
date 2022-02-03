//---------------------------------------------------------------------------

#ifndef HashTableH
#define HashTableH
//---------------------------------------------------------------------------
#endif

#include "container.h"

template<typename T>
class CodeKey
{
	Container<T> keys;
	int code;

	CodeKey(int code = 0, T key = T())
	{
		keys = Container<T>();

        this->code = code;

		if (key != T())
		{
            keys.push_back(key);
		}
	}

	~CodeKey()
	{}
};


template<typename T>
class HashTable
{
public:
	Container<CodeKey<T>> table;

	HashTable()
	{
        table = Container<CodeKey<T>>();
	}

	~HashTable()
	{}

	void Add(T key)
	{
		int code = GetHashCode(key);

		for (int i = 0; i < table.Size(); i++)
		{
			if (table[i].code == code)
			{
				table[i].keys.push_back(key);
                return;
			}
		}

        table.push_back(CodeKey(code, key));
	}

	void Del(T key)
	{
		int code = GetHashCode(key);

		for (int i = 0; i < table.Size(); i++)
		{
			if (table[i].code == code)
			{
                auto a = table[i].keys;

				for (int j = 0; j < a.Size; j++)
				{
					if (a[j] == key)
					{
						a.remove(j);
                        j--;
					}
				}

                return;
			}
		}
	}

	void DelCode(int code)
	{
		for (int i = 0; i < table.Size(); i++)
		{
			if (table[i].code == code)
			{
				table.remove[i];
                return;
			}
		}
	}

	int GetHashCode(int key)
	{
        return key % 10;
	}

	/*
	int GetHashCode(T key)
	{
		return 0;
	}
    */
};