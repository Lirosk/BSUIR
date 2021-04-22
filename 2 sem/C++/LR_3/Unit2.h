//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.WinXPickers.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TButton *AddButton;
	TEdit *NameEdit;
	TEdit *MarkEdit;
	TLabel *NameLabel;
	TLabel *ProductLabel;
	TButton *CancelButton;
	TLabel *MarkLabel;
	TDatePicker *DatePicker;
	TLabel *DateLabel;
	TCheckBox *CheckBox;
	TLabel *ReadyLabel;
	void __fastcall CheckBoxClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall CancelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
