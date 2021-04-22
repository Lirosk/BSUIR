//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.WinXPickers.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox;
	TButton *ShowAllButton;
	TButton *ShowReadyButton;
	TButton *AddButton;
	TButton *ShowGroupButton;
	TLabel *Label1;
	TButton *ShowByPositionButton;
	TLabel *Label2;
	TShape *Shape1;
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall ShowAllButtonClick(TObject *Sender);
	void __fastcall ShowByPositionButtonClick(TObject *Sender);
	void __fastcall ShowGroupButtonClick(TObject *Sender);
	void __fastcall ShowReadyButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
