//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *TakeDataButton;
	TMemo *Memo;
	TFileOpenDialog *FileOpenDialog;
	TLabel *Label;
	TButton *SortButton;
	TButton *AddButton;
	TButton *SearchButton;
	TComboBox *ComboBox;
	TEdit *SearchEdit;
	TLabel *SearchLabel;
	TEdit *FullNameEdit;
	TEdit *SpecialityEdit;
	TEdit *GroupEdit;
	TEdit *MathMarksEdit;
	TLabel *FullNameLabel;
	TLabel *SpecialityLabel;
	TLabel *GroupLabel;
	TLabel *MathMarksLabel;
	TEdit *ProgramMarksEdit;
	TEdit *PhilosophyMarksEdit;
	TLabel *ProgramMarksLabel;
	TLabel *PhilosophyMarksLabel;
	TButton *EditButton;
	TEdit *AverageMarkEdit;
	TLabel *AverageMarkLabel;
	TButton *GoodStudentsButton;
	TButton *FromGroupButton;
	TEdit *FromGroupEdit;
	TLabel *ForGroupLabel;
	TButton *ClearButton;
	TShape *Shape1;
	void __fastcall TakeDataButtonClick(TObject *Sender);
	void __fastcall SortButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall ComboBoxChange(TObject *Sender);
	void __fastcall EditButtonClick(TObject *Sender);
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall GoodStudentsButtonClick(TObject *Sender);
	void __fastcall FromGroupButtonClick(TObject *Sender);
	void __fastcall ClearButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
