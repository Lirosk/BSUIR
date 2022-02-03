//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TTreeView *TreeView1;
	TButton *BalanceButton;
	TButton *DelButton;
	TRichEdit *RichEdit1;
	TButton *DirectButton;
	TButton *BackwardButton;
	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall BalanceButtonClick(TObject *Sender);
	void __fastcall DelButtonClick(TObject *Sender);
	void __fastcall DirectButtonClick(TObject *Sender);
	void __fastcall BackwardButtonClick(TObject *Sender);








private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
