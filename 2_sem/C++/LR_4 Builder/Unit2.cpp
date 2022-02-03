//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CancelButtonClick(TObject *Sender)
{
	Form2->Visible = false;
	NameEdit->Clear();
    ValueEdit->Clear();
}
//---------------------------------------------------------------------------
extern void AddVariable(char, long double);

void __fastcall TForm2::AddButtonClick(TObject *Sender)
{
	try
	{
		if (NameEdit->Text == "")
		{
			  throw "Empty name field";
		}

		if (ValueEdit->Text == "")
		{
			  throw "Empty value field";
		}

	}
	catch (UnicodeString &str)
	{
		ShowMessage(str);
        return;
	}

	AddVariable(NameEdit->Text[1], std::stod(USToString(ValueEdit->Text)));

    Form2->Visible = false;
	NameEdit->Clear();
    ValueEdit->Clear();
}

std::string USToString(UnicodeString strU)
{
	std::string str;
	str.reserve(strU.Length());

	for (unsigned short i = 0; i < strU.Length(); i++)
	{
       str[i] = strU[i + 1];
	}

    return str;
}


//---------------------------------------------------------------------------

