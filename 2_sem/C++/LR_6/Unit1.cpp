//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "person.h"
//#include "SmartPointer.h"
#include "BinTree.h"
#include <windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

typedef unsigned char uc;

node<person>* root = nullptr;

template<typename T>
void treeToView(int* i, node<T>* root)
{
	if (!root)
	{
		return;
	}

	int a = (*i);

	if (root->r)
	{
		Form1->TreeView1->Items->AddChild(Form1->TreeView1->Items->Item[*i], root->r->Data().ToString());
		(*i)++;
		treeToView(i, root->r);
	}

	if (root->l)
	{
		Form1->TreeView1->Items->AddChild(Form1->TreeView1->Items->Item[a], root->l->Data().ToString());
		(*i)++;
        treeToView(i, root->l);
	}


}




template<typename T>
unsigned short numLeaves(node<T>* tree)
{
	int num = 0;

	if (!tree)
	{
		return 0;
	}

	if (!tree->r && !tree->l)
	{
		num++;
	}


	if (tree->r)
	{
		num += numLeaves(tree->r);
	}
	if (tree->l)
	{
		num += numLeaves(tree->l);
	}
    return num;
}

int USToInt (UnicodeString a)
{
	int i = 1;
	bool minus = false;
	if (a[1] == '-')
	{
		minus = true;
		i++;
	}
	int n = 0;
	for (; i <= a.Length(); i++)
	{
		n += (a[i]-'0')*pow(10, a.Length() - i);
	}

	return n*(minus?-1:1);
}

void refreshTree()
{
	TTreeNode* tree = Form1->TreeView1->Items->Item[0];
	Form1->TreeView1->Items->Clear();
	Form1->TreeView1->Items->Add(tree,"root");

	if (root)
	{
		int i = 1;

		Form1->TreeView1->Items->AddChild(tree, root->Data().ToString());
		treeToView(&i, root);
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	StringGrid1->Cells[0][0] = "Иван 5";
	StringGrid1->Cells[0][1] = "Дмитрий 7";
	StringGrid1->Cells[0][2] = "Вадя 6";
	StringGrid1->Cells[0][3] = "Господин Никто 9";
	StringGrid1->Cells[0][4] = "ФИО 9";
	StringGrid1->Cells[1][0] = "name 4";
	StringGrid1->Cells[1][1] = "lal 2";
	StringGrid1->Cells[1][2] = "aga 3";
	StringGrid1->Cells[1][3] = "fu 1";

	for (unsigned int i = 0; i < StringGrid1->RowCount; i++)
	{
		for (unsigned int j = 0; j < StringGrid1->ColCount; j++)
		{
			if (StringGrid1->Cells[i][j] != "")
			{
			   add(root, FromString(StringGrid1->Cells[i][j]));
			}
		}
	}

	refreshTree();
	Edit2->Text = numLeaves(root);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
	if (GetAsyncKeyState(13))
	{
		if (StringGrid1->Cells[ACol][ARow] != "")
		{
			while (GetAsyncKeyState(13)) {};

			add(root, FromString(StringGrid1->Cells[ACol][ARow]));
			refreshTree();

            //StringGrid1->Cells[ACol][ARow] = "";
		}
	}

	Edit2->Text = numLeaves(root);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BalanceButtonClick(TObject *Sender)
{
	balance(root);
    refreshTree();
	Edit2->Text = numLeaves(root);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::DelButtonClick(TObject *Sender)
{
	if (TreeView1->Selected)
	{
		node<person>* temp = new node<person>(FromString(TreeView1->Selected->Text));


		for (unsigned int i = 0; i < StringGrid1->RowCount; i++)
		{
			for (unsigned int j = 0; j < StringGrid1->ColCount; j++)
			{
				if (FromString(StringGrid1->Cells[i][j]) == FromString(TreeView1->Selected->Text))
				{
					StringGrid1->Cells[i][j] = "";
					i = 4000000000;
					j = i;
				}
			}
		}


		del(root, temp);
		refreshTree();
        Edit2->Text = numLeaves(root);
	}
}
//---------------------------------------------------------------------------


template<typename T>
void DirectPass(node<T>* root)
{
	if (root->r)
	{
		DirectPass(root->r);
	}

	Form1->RichEdit1->Lines->Add(root->Data().ToString());

	if (root->l)
	{
		DirectPass(root->l);
	}
}
//---------------------------------------------------------------------------
template<typename T>
void BackPass(node<T>* root)
{
	if (root->l)
	{
		BackPass(root->l);
	}

	Form1->RichEdit1->Lines->Add(root->Data().ToString());

	if (root->r)
	{
		BackPass(root->r);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DirectButtonClick(TObject *Sender)
{
	RichEdit1->Lines->Clear();
	if (root)
	{
		DirectPass(root);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BackwardButtonClick(TObject *Sender)
{
    RichEdit1->Lines->Clear();
	if (root)
	{
		BackPass(root);
	}
}
//---------------------------------------------------------------------------

