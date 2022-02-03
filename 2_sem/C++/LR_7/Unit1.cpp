//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Ht.h"
#include <ctime>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

Ht<int> ht = Ht<int>();



int  ToInt(UnicodeString str)
{
	int num = 0;
    bool minus = false;

	if (str[1] == '-')
	{
        minus = true;
	}

	for (auto i: str)
	{
		if (i >= '0' && i <= '9')
		{
			num *= 10;
			num += i - '0';
		}
	}

	if (minus)
	{
		return -num;
	}
    return num;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowButtonClick(TObject *Sender)
{
	ht.ToRich(RichEdit1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	ht.Add(ToInt(Edit1->Text));
    Edit1->Clear();
	ht.ToRich(RichEdit1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	ht.Del(ToInt(Edit1->Text));
	Edit1->Clear();
	ht.ToRich(RichEdit1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GenButtonClick(TObject *Sender)
{

    ht.Clear();

	if (Edit2->Text == "" || Edit3->Text == "" || Edit4->Text == "")
	{
		ShowMessage("fill the fields.");
        return;
	}

	int quantity = ToInt(Edit4->Text);

	if (!quantity)
	{
		return;
	}

	int down = ToInt(Edit2->Text);
	int up = ToInt(Edit3->Text);

	if (down >= up)
	{
		ShowMessage("incorrect borders.");
        return;
	}

	if (quantity > up - down)
	{
		ShowMessage("no so many numbers on the segment");
        return;
	}

	for (int i = 0; i < quantity; i++)
	{
		ht.Add(rand()%(up + 1 - down) + down);
	}

	ht.ToRich(RichEdit1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DelEvenButtonClick(TObject *Sender)
{
	ht.DelEven();
	ht.ToRich(RichEdit1);
}
//---------------------------------------------------------------------------
