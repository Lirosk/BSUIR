#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THenlo : public TForm
{
__published:	// IDE-managed Components
	TTimer *TimerUp;
	TImage *Image;
	TButton *StopMovement;
	TButton *MoveUp;
	TButton *MoveLeft;
	TButton *MoveDown;
	TButton *MoveRight;
	TTimer *TimerLeft;
	TTimer *TimerDown;
	TTimer *TimerRight;
	TButton *JustPush;
	TCheckBox *DiscreteMovement;
	TCheckBox *ContinuousMovement;
	void __fastcall MoveUpClick(TObject *Sender);
	void __fastcall MoveLeftClick(TObject *Sender);
	void __fastcall MoveDownClick(TObject *Sender);
	void __fastcall MoveRightClick(TObject *Sender);
	void __fastcall TimerUpTimer(TObject *Sender);
	void __fastcall TimerLeftTimer(TObject *Sender);
	void __fastcall TimerDownTimer(TObject *Sender);
	void __fastcall TimerRightTimer(TObject *Sender);
	void __fastcall StopMovementClick(TObject *Sender);
	void __fastcall JustPushClick(TObject *Sender);
	void __fastcall DiscreteMovementClick(TObject *Sender);
	void __fastcall ContinuousMovementClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THenlo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THenlo *Henlo;
//---------------------------------------------------------------------------
#endif


class MyRect
{
	private:
	int x = 0, y = 0, w = 0, h = 0;

	public:
	MyRect (int x0, int y0, int width, int height)
	{
		x = x0;
		y = y0;
		h = height;
		w = width;
	}

	void Move(TCanvas * Canvas, int x, int y)
	{
		//Hide(Canvas);

		this->x += x;
		this->y += y;

		Show(Canvas);
	}

	void Show(TCanvas * Canvas)
	{
		Canvas->Pen->Color=clBlack;
		Canvas->Brush->Color=clYellow;

		Canvas->Rectangle(x, y, x + w, y + h);
	}

	void Hide (TCanvas * Canvas)
	{
		Canvas->Pen->Color = Henlo->Color;
		Canvas->Brush->Color = Henlo->Color;

		Canvas->Rectangle(x,y,x+w,y+h);
	}

	~MyRect(){};
};

////////////////////////////////////////////////////////////////////////////////////

class Wheels
{
    private:
	int x = 0, y = 0, r = 0, d = 0;

	protected:
	Wheels (int x0, int y0, int radius, int distanceAlongX)
	{
		x = x0;
		y = y0;
		r = radius;
		d = distanceAlongX;
	}

    void Show(TCanvas * Canvas)
	{
		Canvas->Pen->Color=clNavy;
		Canvas->Brush->Color=clBlack;

		Canvas->Ellipse(x-r, y+r, x+r, y-r);
        Canvas->Ellipse(x-r + d, y+r, x+r + d, y-r);
	}

	void Move(TCanvas * Canvas, int x, int y)
	{
		//Hide(Canvas);

		this->x += x;
		this->y += y;

		Show(Canvas);
	}

	void Hide (TCanvas * Canvas)
	{
		Canvas->Pen->Color = Henlo->Color;
		Canvas->Brush->Color = Henlo->Color;

		Canvas->Ellipse(x-r, y-r, x+r, y+r);
		Canvas->Ellipse(x-r + d, y-r, x+r + d, y+r);
	}

	~Wheels(){};
};

////////////////////////////////////////////////////////////////////////////////////

class Car: Wheels,MyRect
{
	private:
	int x = 0, y = 0, r = 0;

	public:
	Car(int x0, int y0, int width, int height, int radius, int distanceAlongX):
	MyRect(x0,y0,width,height),
	Wheels(x0 + width/4, y0 + height, radius, width/2) {}


	void Hide(TCanvas * Canvas)
	{
		MyRect::Hide(Canvas);
		Wheels::Hide(Canvas);
	}

	void Show(TCanvas * Canvas)
	{
		MyRect::Show(Canvas);
		Wheels::Show(Canvas);
	}

	void Move(TCanvas * Canvas, int xNew, int yNew)
	{

		MyRect::Hide(Canvas);
        Wheels::Hide(Canvas);

		MyRect::Move(Canvas, xNew, yNew);
		Wheels::Move(Canvas, xNew, yNew);
	}

};
