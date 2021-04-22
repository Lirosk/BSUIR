//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "container.h"
#include "product.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
extern TForm *Form2;
extern TForm *Form3;
extern TForm *Form4;

extern UnicodeString name, mark;
extern TDate whenTaken;
extern bool isReady;
unsigned int position = 1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

Container<Product> list;




void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	Form2->Visible = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


void AfterAddButton()
{
    list.push_back(Product(position++, name, mark, whenTaken, isReady));
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowAllButtonClick(TObject *Sender)
{
    ListBox->Clear();

	for (unsigned int i = 0; i < list.GetSize(); i++)
	{
		ListBox->Items->Add(list[i].ToString() + "\n");
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowByPositionButtonClick(TObject *Sender)
{
	Form3->Visible = true;
}
void ShowByPosition(unsigned int index)
{
	for (unsigned int i = 0; i < list.GetSize(); i++)
	{
		if (list[i].GetPosition() == index)
		{
			Form1->ListBox->Items->Clear();
			Form1->ListBox->Items->Add(list[i].ToString());
			return;
		}
	}

	ShowMessage("Not found");
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowGroupButtonClick(TObject *Sender)
{
    Form4->Visible = true;
}
void ShowByName(UnicodeString name)
{
	bool notFound = true;

	for (int  i = 0; i < list.GetSize(); i++)
	{
		if (list[i].GetName() == name)
		{
			 notFound = false;
			 break;
		}
	}

	if (notFound)
	{
		ShowMessage("Not found");
		return;
	}

	Form1->ListBox->Items->Clear();

	for (unsigned int  i = 0; i < list.GetSize(); i++)
	{
		if (list[i].GetName() == name)
		{
			 Form1->ListBox->Items->Add(list[i].ToString());
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowReadyButtonClick(TObject *Sender)
{
	bool notFound = true;

	for (unsigned int i = 0; i < list.GetSize(); i++)
	{
		if (list[i].GetReady())
		{
			notFound = false;
			break;
		}
	}

	if (notFound)
	{
		ShowMessage("Not found");
        return;
	}

	ListBox->Items->Clear();

    for (unsigned int i = 0; i < list.GetSize(); i++)
	{
		if (list[i].GetReady())
		{
			ListBox->Items->Add(list[i].ToString());
		}
	}

}
//---------------------------------------------------------------------------



