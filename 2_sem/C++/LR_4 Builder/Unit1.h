//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit;
	TButton *CalculateButton;
	TLabel *Label1;
	TEdit *AnswerEdit;
	TComboBox *ComboBox1;
	TLabel *Label2;
	TEdit *ValueEdit;
	TEdit *ReversePolishEdit;
	TButton *EditVariableButton;
	TButton *AddVariableButton;
	void __fastcall EditVariableButtonClick(TObject *Sender);
	void __fastcall AddVariableButtonClick(TObject *Sender);
	void __fastcall CalculateButtonClick(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
