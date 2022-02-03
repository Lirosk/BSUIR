//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "MyExp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;


UnicodeString name, mark;
TDate whenTaken;
bool isReady;

extern void AfterAddButton();

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBoxClick(TObject *Sender)
{
	if (CheckBox->Checked)
	{
		CheckBox->Caption = "yep";
	}
	else
	{
        CheckBox->Caption = "nope";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::AddButtonClick(TObject *Sender)
{
	try
	{
		if (NameEdit->Text == "")
		{
			throw MyException("Empty name field");
		}
	}
	catch(MyException)
	{
		ShowMessage("Empty name field");
		return;
	}

    name = NameEdit->Text;

    try
	{
		if (MarkEdit->Text == "")
		{
			throw MyException("Empty mark field");
		}
	}
	catch(MyException)
	{
		ShowMessage("Empty mark field");
        return;
	}

    mark = MarkEdit->Text;

	whenTaken = DatePicker->Date;
	isReady = CheckBox->Checked;

	Form2->Visible = false;

	NameEdit->Clear();
	MarkEdit->Clear();
	CheckBox->Checked = false;

	AfterAddButton();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CancelButtonClick(TObject *Sender)
{
 	Form2->Visible = false;
}
//---------------------------------------------------------------------------


