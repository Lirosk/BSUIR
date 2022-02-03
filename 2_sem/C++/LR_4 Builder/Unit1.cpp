//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <string>
#include <map>
#include <cstdlib>
#include "stack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
extern TForm *Form2;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	ComboBox1->Items->Add('a');
	ComboBox1->Items->Add('b');
	ComboBox1->Items->Add('c');
	ComboBox1->Items->Add('d');
	ComboBox1->Items->Add('e');
}
//---------------------------------------------------------------------------

typedef unsigned short us;
typedef unsigned int ui;

#define start 'a'
#define end 'z'

std::map<char, int> operations
{
    {'(', 0}, {')', 0},
    {'+', 1}, {'-', 1},
	{'*', 2}, {'/', 2},
    {'^', 3}
};

std::map<char, long double> operands
{
	{'0', 0}, {'1', 1},
	{'2', 2}, {'3', 3},
	{'4', 4}, {'4', 4},
	{'5', 5}, {'6', 6},
	{'7', 7}, {'8', 8},
	{'9', 9},
	{'a', 7.4}, {'b', 3.6},
	{'c', 2.8}, {'d', 9.5},
    {'e', 0.9}
};



short int sign (long double a)
{
	if (a > 0)
	{
		return 1;
	}
	if (a < 0)
	{
		return -1;
	}
    return 0;
}


std::string GetReversePolish (std::string);
long double CalculateReversePolish(std::string);

Mstack<long double> operandsForCalc;


//---------------------------------------------------------------------------

UnicodeString GetReversePolish(UnicodeString equation)
{
	UnicodeString str = "";
	Mstack<char> opers;

	for (char buffer: equation)
	{
		if (((buffer < start) || (buffer > end)) && (buffer == '+' || buffer == '-' || buffer == '*' || buffer == '/' || buffer == '(' || buffer == ')'))
		{
			if (opers.Size() && buffer != '(')
			{
				while (opers.Size() && (operations.find(buffer)->second <= operations.find(opers.top())->second) && (opers.top() != '('))
				{
					str += opers.top();
					opers.pop();
				}

				if (buffer == ')' && opers.top() == '(')
				{
					opers.pop();
				}
			}
			if (buffer != ')')
			{
				opers.push(buffer);
			}
		}
		else
		{
			str += buffer;
		}
	}

	while (opers.Size())
	{
		str += opers.top();
		opers.pop();
	}

	return str;
}

//---------------------------------------------------------------------------


long double CalculateReversePolish(UnicodeString str)
{

	long double a = 0;

	for (char i: str)
	{
		if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9'))
		{
			operandsForCalc.push(operands.find(i)->second) ;
		}
		else if (i != ' ')
		{
			a = operandsForCalc.top();
            operandsForCalc.pop();

			switch(i)
			{
                case ('+'):
                {
                    operandsForCalc.top() += a;
                    break;
                }
                case ('-'):
                {
                    operandsForCalc.top() -= a;
                    break;
                }
                case ('*'):
                {
                    operandsForCalc.top() *= a;
                    break;
                }
                case ('/'):
                {
                    operandsForCalc.top() /= a;
                    break;
				}
				case ('^'):
				{
					operandsForCalc.top() = pow(operandsForCalc.top(), a);
                    break;
                }
            }
		}


	}


	a = operandsForCalc.top();
	operandsForCalc.pop();
	return a;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditVariableButtonClick(TObject *Sender)
{
	operands.find(ComboBox1->Text[1])->second = std::stod(ValueEdit->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddVariableButtonClick(TObject *Sender)
{
	Form2->Visible = true;
}
//---------------------------------------------------------------------------

void AddVariable(char name, long double value)
{
	for (auto i: operands)
	{
		if (name == i.first)
		{
			ShowMessage("This variable already exist");
            return;
		}
	}

	operands.insert({name, value});
	Form1->ComboBox1->Items->Add(name);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::CalculateButtonClick(TObject *Sender)
{
	ReversePolishEdit->Text = GetReversePolish(Edit->Text);
	AnswerEdit->Text = (std::to_string(CalculateReversePolish(ReversePolishEdit->Text))).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	ValueEdit->Text = (std::to_string(operands.find(ComboBox1->Text[1])->second)).c_str();
}
//---------------------------------------------------------------------------


