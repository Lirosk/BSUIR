//---------------------------------------------------------------------------

#ifndef EXContainerH
#define EXContainerH
//---------------------------------------------------------------------------
#endif

#include <vector>
#include <string>
#include <vcl.h>
#include <stdlib.h>

using std::vector;
using std::string;

class Student
{
	//protected:
	public:

    UnicodeString FullName = "";
	UnicodeString Speciality = "";

	//int GroupNumber = 0;
    UnicodeString GroupNumber = 0;

	vector<int> MathMarks; //(0, 0);
	vector<int> ProgramMarks; //(0, 0);
	vector<int> PhilosophyMarks; //(0, 0);

	Student(UnicodeString FullName, UnicodeString Speciality, UnicodeString GroupNumber, UnicodeString MathMarks, UnicodeString ProgramMarks, UnicodeString PhilosophyMarks)
	{
		this->FullName = FullName;
		this->Speciality = Speciality;
		this->GroupNumber = GroupNumber;
		NumsFromStrToArr(MathMarks, this->MathMarks);
		NumsFromStrToArr(ProgramMarks, this->ProgramMarks);
		NumsFromStrToArr(PhilosophyMarks, this->PhilosophyMarks);
	}

    Student() {}

    virtual void NumsFromStrToArr(UnicodeString str, vector<int> &nums)
	{
		nums.clear();

		int len = str.Length(), tempNum = 0, startOfNum = 1;
		int i = 1;

		if (str[i] == ' ')
		{
            i += 1;
		}

		for (; i <= len; i++)
		{
            //ShowMessage(i);
			if ((str[i] != ' ') && ((str[i] < 48) || (str[i] > 57)))
			{
				return;
			}
		}

		if (str[len] == ' ')
		{
			str[len] = '\0';
            len -= 1;
		}

		for (int i = 1; i <= len; i++)
		{
			if ((i == len) || (str[i + 1] == ' '))
			{
				for (int j = startOfNum; j <= i; j ++)
				{

					tempNum += (str[j] - '0') * (int)pow(10, i - j);
				}
				nums.push_back(tempNum);
				tempNum = 0;
				startOfNum = i + 2;
			}
		}
	}

	public:
    int AverageMark()
	{
		int averageMark = 0, quantity = 0;//vector<Student>::iterator

		for (vector<int>::iterator i = MathMarks.begin(); i != MathMarks.end(); i++)
		{
			averageMark += *i;
			quantity += 1;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		/*
		for (unsigned short i = 0; i < MathMarks.size(); i++)
		{
			averageMark += MathMarks[i];
			quantity += 1;
		}
		*/
		for (vector<int>::iterator i = ProgramMarks.begin(); i != ProgramMarks.end(); i++)
		{
			averageMark += *i;
			quantity += 1;
		}
		for (vector<int>::iterator i = PhilosophyMarks.begin(); i != PhilosophyMarks.end(); i++)
		{
			averageMark += *i;
			quantity += 1;
		}

		if (!quantity)
		{
			return 0;
		}

		return averageMark/quantity;
	}

	void ReadMath(UnicodeString str)
	{
		NumsFromStrToArr(str, MathMarks);
	}

	void ReadPhilosophy(UnicodeString str)
	{
		NumsFromStrToArr(str, PhilosophyMarks);
	}

	void ReadProgram(UnicodeString str)
	{
        NumsFromStrToArr(str, ProgramMarks);
	}

	void ReadName(UnicodeString str)
	{
		FullName = str;
	}

	void ReadSpeciality(UnicodeString str)
	{
		Speciality = str;
	}

	void ReadGroup(UnicodeString str)
	{
		GroupNumber = str;
	}

	virtual UnicodeString ToString()
	{
		char tempStr[100] = "";
		UnicodeString str = FullName + "\n" + Speciality + "\n" + GroupNumber + "\n";

        for (vector<int>::iterator i = MathMarks.begin(); i != MathMarks.end(); i++)
		{
			itoa(*i, tempStr, 10);
            str += tempStr; str += " ";
		}
		str += "\n";

		for (vector<int>::iterator i = ProgramMarks.begin(); i != ProgramMarks.end(); i++)
		{
            itoa(*i, tempStr, 10);
			str += tempStr; str += " ";
		}
		str += "\n";

		for (vector<int>::iterator i = PhilosophyMarks.begin(); i != PhilosophyMarks.end(); i++)
		{
			itoa(*i, tempStr, 10);
            str += tempStr; str += " ";
		}
		str += "\n-----------------------";

		return str;
	}
} ;


//////////////////////////////////////////////////

class EXContainer//: public Student
{
    public:
	vector<Student> Students; //(0,0);

	public:
	void Size(int n)
	{
        Students.resize(n);
    }

	void SortAllByMarks ()
	{
		if (!Students.size())
		{
            return;
		}

		for (vector<Student>::iterator i = Students.begin(); i != Students.end(); i++)
		{
			for(vector<Student>::iterator j = i; (j != Students.begin()) && ((*(j-1)).AverageMark() < (*j).AverageMark()); j--)
			{
				Student temp = *j;
				*j = *(j-1);
				*(j-1) = temp;
            }
		}
	}

};