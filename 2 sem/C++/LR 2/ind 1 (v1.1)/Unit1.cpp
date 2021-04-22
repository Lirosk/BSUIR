//---------------------------------------------------------------------------

#include <vcl.h>
#include <string.h>
//#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "EXContainer.h"
#include "container.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


EXContainer container;
#define students container.Students


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
void RefreshMemo()
{
	Form1->Memo->Lines->Clear();
    Form1->ComboBox->Items->Clear();
    for(int i = 0; i < students.size(); i++)
	{
		Form1->Memo->Lines->Add(students[i].FullName/* + " (" + students[i].AverageMark() + ")"*/);
		Form1->ComboBox->Items->Add(students[i].FullName);
	}
}
////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
void ShowStudent(Student student)
{
	Form1->FullNameEdit->Text = (student).FullName;
	Form1->SpecialityEdit->Text = (student).Speciality;
	Form1->GroupEdit->Text = (student).GroupNumber;

	UnicodeString tempStr = "";

	for (vector<int>::iterator j = (student).MathMarks.begin(); j != (student).MathMarks.end(); j++)
	{
		tempStr += *j;
		tempStr += " ";
	}

	Form1->MathMarksEdit->Text = tempStr;
	tempStr = "";


	for (vector<int>::iterator j = (student).ProgramMarks.begin(); j != (student).ProgramMarks.end(); j++)
	{
		tempStr += *j;
		tempStr += " ";
	}

	Form1->ProgramMarksEdit->Text = tempStr;
	tempStr = "";


	for (vector<int>::iterator j = (student).PhilosophyMarks.begin(); j != (student).PhilosophyMarks.end(); j++)
	{
		tempStr += *j;
		tempStr += " ";
	}

	Form1->PhilosophyMarksEdit->Text = tempStr;
	tempStr = "";

	Form1->AverageMarkEdit->Text = (double)(student).AverageMark();

    Form1->ComboBox->Text = student.FullName;
}
////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------

void __fastcall TForm1::TakeDataButtonClick(TObject *Sender)
{
	FileOpenDialog->Execute();
	Label->Caption=FileOpenDialog->FileName;

    if (FileOpenDialog->FileName == "")
	{
        return;
	}

	TFileStream*tfile = new TFileStream(FileOpenDialog->FileName, fmOpenRead);
	TStringList *SL = new TStringList;

	SL->LoadFromStream(tfile);

	int lines = 0;
	for (; SL->Strings[lines] != "end" ; lines++);

	students.resize((lines / 7));
    //ShowMessage(lines/7);

	for (int i = 0; i < lines; i+=7)
	{
        //ShowMessage(i);
		students[(int)i/7].ReadName(SL->Strings[i]);
		students[(int)i/7].ReadSpeciality(SL->Strings[i+1]);
		students[(int)i/7].ReadGroup(SL->Strings[i+2]);
		students[(int)i/7].ReadMath(SL->Strings[i+3]);
		students[(int)i/7].ReadProgram(SL->Strings[i+4]);
		students[(int)i/7].ReadPhilosophy(SL->Strings[i+5]);
	}

	//students.pop_back();

	delete tfile;
	delete SL;

	RefreshMemo();
}
//---------------------------------------------------------------------------
//lines = 6*n + n - 1 = 7*n - 1
//n = (lines + 1)/7
void __fastcall TForm1::SortButtonClick(TObject *Sender)
{
	container.SortAllByMarks();
	RefreshMemo();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	if (FullNameEdit->Text == "")
	{
		ShowMessage("Fill name");
		return;
	}
	if (SpecialityEdit->Text == "")
	{
		ShowMessage("Fill speciality");
		return;
	}
	if (GroupEdit->Text == "")
	{
		ShowMessage("Fill group number");
		return;
	}
	if (MathMarksEdit->Text == "")
	{
		ShowMessage("Fill math marks");
		return;
	}
	if (ProgramMarksEdit->Text == "")
	{
		ShowMessage("Fill program marks");
		return;
	}
	if (PhilosophyMarksEdit->Text == "")
	{
		ShowMessage("Fill philosophy marks");
		return;
	}

	Student* temp = new Student(FullNameEdit->Text, SpecialityEdit->Text, GroupEdit->Text, MathMarksEdit->Text, ProgramMarksEdit->Text, PhilosophyMarksEdit->Text);
	students.push_back(*temp);

	RefreshMemo();

    delete temp;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBoxChange(TObject *Sender)
{
	bool found = false;
	vector<Student>::iterator i;

	for (i = students.begin(); i != students.end(); i++)
	{
		if ((*i).FullName == ComboBox->Text)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		ShowMessage("Not found");
		return;
	}

    ShowStudent(*i);

}
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
void __fastcall TForm1::EditButtonClick(TObject *Sender)
{
	if (FullNameEdit->Text == "")
	{
		ShowMessage("Fill name");
		return;
	}
	if (SpecialityEdit->Text == "")
	{
		ShowMessage("Fill speciality");
		return;
	}
	if (GroupEdit->Text == "")
	{
		ShowMessage("Fill group number");
		return;
	}
	if (MathMarksEdit->Text == "")
	{
		ShowMessage("Fill math marks");
		return;
	}
	if (ProgramMarksEdit->Text == "")
	{
		ShowMessage("Fill program marks");
		return;
	}
	if (PhilosophyMarksEdit->Text == "")
	{
		ShowMessage("Fill philosophy marks");
		return;
	}


    bool found = false;
	vector<Student>::iterator i;

    for (i = students.begin(); i != students.end(); i++)
	{
		if ((*i).FullName == ComboBox->Text)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		ShowMessage("Not found");
		return;
	}

	(*i) = Student(FullNameEdit->Text, SpecialityEdit->Text, GroupEdit->Text, MathMarksEdit->Text, ProgramMarksEdit->Text, PhilosophyMarksEdit->Text);

	/////////////////////////////////////////////////

    ShowStudent(*i);

    RefreshMemo();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SearchButtonClick(TObject *Sender)
{
	vector<Student>::iterator i = students.begin();
    bool found = false;

	for (; i != students.end(); i++)
	{
		if ((*i).FullName == SearchEdit->Text)
		{
            found = true;
            break;
		}
	}

	if (!found)
	{
		ShowMessage("Not found");
        return;
	}

    ShowStudent(*i);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GoodStudentsButtonClick(TObject *Sender)
{
	ComboBox->Items->Clear();
    Memo->Lines->Clear();

	bool* badMark = new bool(false);
	for (vector<Student>::iterator i = students.begin(); i != students.end(); i++)
	{
		*badMark = false;

		for (vector<int>::iterator j = (*i).MathMarks.begin(); j != (*i).MathMarks.end(); j++)
		{
			if ((*j) < 4) {
				*badMark = true;
				break;
			}
		}
		for (vector<int>::iterator j = (*i).ProgramMarks.begin(); j != (*i).ProgramMarks.end(); j++)
		{
            if ((*j) < 4) {
				*badMark = true;
				break;
			}
		}
		for (vector<int>::iterator j = (*i).PhilosophyMarks.begin(); j != (*i).PhilosophyMarks.end(); j++)
		{
            if ((*j) < 4) {
				*badMark = true;
				break;
			}
		}

		if (!(*badMark))
		{
			ComboBox->Items->Add((*i).FullName);
			Memo->Lines->Add((*i).FullName);
		}
	}

    delete badMark;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveDataButtonClick(TObject *Sender)
{
	SaveDialog->FileName = Label->Caption;

	if (!SaveDialog->Execute())
	{
		return;
	}

	Label->Caption = SaveDialog->FileName;
	Memo1->Lines->Clear();

	for (vector<Student>::iterator i = students.begin(); i != students.end(); i++)
	{
		Memo1->Lines->Add((*i).ToString());
	}

	Memo1->Lines->Add("end");

	Memo1->Lines->SaveToFile(Label->Caption);
    Memo1->Lines->LoadFromFile(Label->Caption);

}
//---------------------------------------------------------------------------



