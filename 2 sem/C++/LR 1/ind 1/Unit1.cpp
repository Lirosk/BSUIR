//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


THenlo *Henlo;

Car MyCar (150,150,100,40,10,75);

//---------------------------------------------------------------------------
 __fastcall THenlo::THenlo(TComponent* Owner): TForm(Owner)
{
ShowMessage("Henlo");
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall THenlo::MoveUpClick(TObject *Sender)
{
	//

	if (((!ContinuousMovement->Checked) && (!DiscreteMovement->Checked)))
	{
		  ShowMessage("Choose type of movement");
          return;
	}

	//TimerUp->Enabled=false;
	TimerDown->Enabled=false;
	TimerRight->Enabled=false;
	TimerLeft->Enabled=false;

	if (ContinuousMovement->Checked)
	{
		if (!TimerUp->Enabled)
		{
		TimerUp->Enabled = true;
		}
		else
		{
        TimerUp->Enabled = false;
        }
	}
	else
	{
		MyCar.Move(Canvas,0,-5);
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::MoveLeftClick(TObject *Sender)
{
	//

    if ((!ContinuousMovement->Checked) && (!DiscreteMovement->Checked))
	{
		  ShowMessage("Choose type of movement");
          return;
	}

    TimerUp->Enabled=false;
	TimerDown->Enabled=false;
	TimerRight->Enabled=false;
	//TimerLeft->Enabled=false;

    if (ContinuousMovement->Checked)
	{
		if (!TimerLeft->Enabled)
		{
		TimerLeft->Enabled = true;
		}
		else
		{
		TimerLeft->Enabled = false;
		}
	}
	else
	{
		MyCar.Move(Canvas,-5,0);
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::MoveDownClick(TObject *Sender)
{
	//

    if ((!ContinuousMovement->Checked) && (!DiscreteMovement->Checked))
	{
		  ShowMessage("Choose type of movement");
          return;
	}

    TimerUp->Enabled=false;
	//TimerDown->Enabled=false;
	TimerRight->Enabled=false;
	TimerLeft->Enabled=false;

    if (ContinuousMovement->Checked)
	{
		if (!TimerDown->Enabled)
		{
		TimerDown->Enabled = true;
		}
		else
		{
		TimerDown->Enabled = false;
		}
	}
	else
	{
		MyCar.Move(Canvas,0,5);
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::MoveRightClick(TObject *Sender)
{
	//

    if ((!ContinuousMovement->Checked) && (!DiscreteMovement->Checked))
	{
		  ShowMessage("Choose type of movement");
          return;
	}

	TimerUp->Enabled=false;
	TimerDown->Enabled=false;
	//TimerRight->Enabled=false;
	TimerLeft->Enabled=false;

    if (ContinuousMovement->Checked)
	{
		if (!TimerRight->Enabled)
		{
		TimerRight->Enabled = true;
		}
		else
		{
        TimerRight->Enabled = false;
		}
	}
	else
	{
		MyCar.Move(Canvas,5,0);
	}
}
//---------------------------------------------------------------------------




void __fastcall THenlo::TimerUpTimer(TObject *Sender)
{
	MyCar.Move(Canvas,0,-1);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerLeftTimer(TObject *Sender)
{
	MyCar.Move(Canvas,-1,0);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerDownTimer(TObject *Sender)
{
	MyCar.Move(Canvas,0,1);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerRightTimer(TObject *Sender)
{
	MyCar.Move(Canvas,1,0);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::StopMovementClick(TObject *Sender)
{
	TimerUp->Enabled=false;
	TimerDown->Enabled=false;
	TimerRight->Enabled=false;
	TimerLeft->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall THenlo::JustPushClick(TObject *Sender)
{

    JustPush->Visible = false;


	DiscreteMovement->Visible = true;
	ContinuousMovement->Visible = true;
	MoveUp->Visible = true;
	MoveDown->Visible = true;
	MoveLeft->Visible = true;
	MoveRight->Visible = true;
	StopMovement->Visible = true;

	MyCar.Show(Canvas);

}
//---------------------------------------------------------------------------

void __fastcall THenlo::DiscreteMovementClick(TObject *Sender)
{
	if ((DiscreteMovement->Checked))
	{
		ContinuousMovement->Checked = false;
		StopMovement->Enabled = false;

        TimerUp->Enabled=false;
		TimerDown->Enabled=false;
		TimerRight->Enabled=false;
		TimerLeft->Enabled=false;
	}
}
//---------------------------------------------------------------------------

void __fastcall THenlo::ContinuousMovementClick(TObject *Sender)
{
   if ((ContinuousMovement->Checked))
	{
		DiscreteMovement->Checked = false;
        StopMovement->Enabled = true;
	}
}
//---------------------------------------------------------------------------

