//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "container.h"
#include <ctime>
#include <sstream>
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

typedef unsigned int ui;
typedef unsigned short us;

Container<ui> fst;
Container<ui> scnd;

#define size 13

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void RefreshListBoxes()
{
    Form1->ListBox1->Items->Clear();
	Form1->ListBox2->Items->Clear();

	for (ui i = 0; i < fst.Size(); i++)
	{
		Form1->ListBox1->Items->Add(fst[i]);
	}
	for (ui i = 0; i < scnd.Size(); i++)
	{
		Form1->ListBox2->Items->Add(scnd[i]);
	}
}









void __fastcall TForm1::ReButtonClick(TObject *Sender)
{
	srand(time(0));

	fst.clear();
	scnd.clear();

	for (ui i = 0; i < size; i++)
	{
		fst.push_back(rand() % 26);
		scnd.push_back(rand() % 26);
	}

    RefreshListBoxes();
}
//---------------------------------------------------------------------------




ui USToInt (UnicodeString a)
{
	ui n = 0;
	for (ui i = 1; i <= a.Length(); i++)
	{
		n += (a[i]-'0')*pow(10, a.Length() - i);
	}

	return n;
}

void __fastcall TForm1::Add1ButtonClick(TObject *Sender)
{
	fst.push_back(USToInt(Edit1->Text));
	RefreshListBoxes();

	Edit1->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Add2ButtonClick(TObject *Sender)
{
	scnd.push_back(USToInt(Edit2->Text));
	RefreshListBoxes();

    Edit2->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Del1ButtonClick(TObject *Sender)
{
	fst.remove();
	RefreshListBoxes();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Del2buttonClick(TObject *Sender)
{
    scnd.remove();
	RefreshListBoxes();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DoButtonClick(TObject *Sender)
{
	ListBox3->Items->Clear();

	if (!fst.Size())
	{
		for (us i = 0; i < scnd.Size(); i++)
		{
			ListBox3->Items->Add(scnd[i]);
			fst.push_back(scnd[i]);
		}
		RefreshListBoxes();
        return;
	}

	if (!scnd.Size())
	{
        for (us i = 0; i < fst.Size(); i++)
		{
		  ListBox3->Items->Add(fst[i]);
		}
        return;
	}

	{
		us max = fst[0];
		us order = 0;

		for (us i = 0; i < fst.Size(); i++)
		{
			if (fst[i] > max)
			{
				max = fst[i];
				order = i;
			}
		}

		us sizeTemp = fst.Size();

		for (us i = 0; i <= order; i++)
		{
			fst.push_back(fst[0]);
			fst.remove();
		}
		while (scnd.Size())
		{
			fst.push_back(scnd[0]);
            scnd.remove();
		}
		for (; order < sizeTemp - 1; order++)
		{
			fst.push_back(fst[0]);
            fst.remove();
		}
		/*
		for (us i = 0; i < scnd.Size(); i++)
		{
			fst.insert(scnd[i], ++order);
		}
		*/
	}

	for (us i = 0; i < fst.Size(); i++)
	{
		  ListBox3->Items->Add(fst[i]);
	}

	RefreshListBoxes();
}
//---------------------------------------------------------------------------










