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
	TListBox *ListBox1;
	TListBox *ListBox2;
	TLabel *start;
	TButton *ReButton;
	TButton *Add1Button;
	TButton *Add2Button;
	TButton *Del1Button;
	TButton *Del2button;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *DoButton;
	TListBox *ListBox3;
	TLabel *Label1;
	void __fastcall ReButtonClick(TObject *Sender);
	void __fastcall Add1ButtonClick(TObject *Sender);
	void __fastcall Add2ButtonClick(TObject *Sender);
	void __fastcall Del1ButtonClick(TObject *Sender);
	void __fastcall Del2buttonClick(TObject *Sender);
	void __fastcall DoButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
