//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "MyExp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

extern void ShowByPosition(unsigned int index);

void __fastcall TForm3::SearchButtonClick(TObject *Sender)
{
	try
	{
		if (Edit->Text == "")
		{
			throw MyException("Empty field");
		}
	}
	catch (MyException)
	{
		ShowMessage("Empty field");
        return;
	}
	Form3->Visible = false;
	ShowByPosition(Edit->Text.ToInt());
	Edit->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::CancelButtonClick(TObject *Sender)
{
    Form3->Visible = false;
	Edit->Clear();
}
//---------------------------------------------------------------------------
