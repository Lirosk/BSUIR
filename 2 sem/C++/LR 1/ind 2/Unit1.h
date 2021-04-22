//---------------------------------------------------------------------------

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
	TImage *Image;
	TCheckBox *Rectangle;
	TCheckBox *Circle;
	TCheckBox *Ellipse;
	TCheckBox *Triangle;
	TCheckBox *Custom;
	TRadioButton *Draw;
	TRadioButton *Move;
	TTimer *TimerForRectangleSide;
	TTimer *TimerForRectangleSide2;
	TTimer *TimerForRectangleUp;
	TTimer *TimerForRectangleUp2;
	TTimer *TimerForRectangleMove;
	TTimer *TimerForRectangleShow;
	TEdit *Angle;
	TLabel *Label;
	TButton *Rotate;
	TTimer *TimerForRectangleRotate;
	TButton *StopRotation;
	TLabel *LabelBeforeSquare;
	TLabel *Label1;
	TStaticText *SquareText;
	TTimer *Square;
	TTimer *TimerForEllipseShow;
	TTimer *TimerForCircleShow;
	TTimer *TimerForEllipseMove;
	TTimer *TimerForEllipseUp;
	TTimer *TimerForEllipseUp2;
	TTimer *TimerForEllipseSide2;
	TTimer *TimerForEllipseSide;
	TTimer *TimerForEllipseRotate;
	TTimer *TimerForCircleMove;
	TTimer *TimerForCircleUp2;
	TTimer *TimerForCircleUp;
	TTimer *TimerForCircleSide2;
	TTimer *TimerForCircleSide;
	TTimer *TimerForSquareMove;
	TTimer *TimerForSquareUp2;
	TTimer *TimerForSquareUp;
	TTimer *TimerForSquareSide2;
	TTimer *TimerForSquareSide;
	TTimer *TimerForSquareShow;
	TTimer *TimerForSquareRotate;
	TTimer *TimerForTriangleMove;
	TTimer *TimerForTriangleTop1;
	TTimer *TimerForTriangleTop2;
	TTimer *TimerForTriangleTop3;
	TTimer *TimerForTriangleShow;
	TTimer *TimerForTriangleRotate;
	TLabel *Center;
	TLabel *xCenter;
	TLabel *yCenter;
	TLabel *x;
	TLabel *y;
	TTimer *CenterCoordinates;
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RectangleClick(TObject *Sender);
	void __fastcall CircleClick(TObject *Sender);
	void __fastcall EllipseClick(TObject *Sender);
	void __fastcall TriangleClick(TObject *Sender);
	void __fastcall CustomClick(TObject *Sender);
	void __fastcall DrawClick(TObject *Sender);
	void __fastcall MoveClick(TObject *Sender);
	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall TimerForRectangleSideTimer(TObject *Sender);
	void __fastcall ImageMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y, int HitTest, TMouseActivate &MouseActivate);
	void __fastcall TimerForRectangleSide2Timer(TObject *Sender);
	void __fastcall TimerForRectangleUpTimer(TObject *Sender);
	void __fastcall TimerForRectangleUp2Timer(TObject *Sender);
	void __fastcall TimerForRectangleMoveTimer(TObject *Sender);
	void __fastcall TimerForRectangleShowTimer(TObject *Sender);
	void __fastcall RotateClick(TObject *Sender);
	void __fastcall TimerForRectangleRotateTimer(TObject *Sender);
	void __fastcall StopRotationClick(TObject *Sender);
	void __fastcall SquareTimer(TObject *Sender);
	void __fastcall Timer(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled);
	void __fastcall TimerForEllipseShowTimer(TObject *Sender);
	void __fastcall TimerForEllipseUp2Timer(TObject *Sender);
	void __fastcall TimerForEllipseUpTimer(TObject *Sender);
	void __fastcall TimerForEllipseSide2Timer(TObject *Sender);
	void __fastcall TimerForEllipseSideTimer(TObject *Sender);
	void __fastcall TimerForEllipseRotateTimer(TObject *Sender);
	void __fastcall TimerForEllipseMoveTimer(TObject *Sender);
	void __fastcall TimerForCircleShowTimer(TObject *Sender);
	void __fastcall TimerForCircleMoveTimer(TObject *Sender);
	void __fastcall TimerForCircleUp2Timer(TObject *Sender);
	void __fastcall TimerForCircleUpTimer(TObject *Sender);
	void __fastcall TimerForCircleSide2Timer(TObject *Sender);
	void __fastcall TimerForCircleSideTimer(TObject *Sender);
	void __fastcall TimerForSquareMoveTimer(TObject *Sender);
	void __fastcall TimerForSquareShowTimer(TObject *Sender);
	void __fastcall TimerForSquareUp2Timer(TObject *Sender);
	void __fastcall TimerForSquareUpTimer(TObject *Sender);
	void __fastcall TimerForSquareSide2Timer(TObject *Sender);
	void __fastcall TimerForSquareSideTimer(TObject *Sender);
	void __fastcall TimerForSquareRotateTimer(TObject *Sender);
	void __fastcall TimerForTriangleShowTimer(TObject *Sender);
	void __fastcall TimerForTriangleTop1Timer(TObject *Sender);
	void __fastcall TimerForTriangleTop2Timer(TObject *Sender);
	void __fastcall TimerForTriangleTop3Timer(TObject *Sender);
	void __fastcall TimerForTriangleMoveTimer(TObject *Sender);
	void __fastcall TimerForTriangleRotateTimer(TObject *Sender);
	void __fastcall CenterCoordinatesTimer(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall THenlo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THenlo *Henlo;
//---------------------------------------------------------------------------
#endif
