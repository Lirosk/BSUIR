//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "MyExp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

extern void ShowByName(UnicodeString name);
void __fastcall TForm4::SearchButtonClick(TObject *Sender)
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

	 Form4->Visible = false;
	 ShowByName(Edit->Text);
     Edit->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CancelButtonClick(TObject *Sender)
{
	 Form4->Visible = false;
     Edit->Clear();
}
//---------------------------------------------------------------------------
