//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Circle.h"
#include "Custom.h"
//#include "Ellipse.h"
//#include "Rectangle.h"
#include "Triangle.h"

int x1G = 0, x2G = 0, y1G = 0, y2G = 0;

/*
		if (Rectangle->Checked)
		{

		}
		else if (Circle->Checked)
		{

		}
		else if (Ellipse->Checked)
		{

		}
		else if (Triangle->Checked)
		{

		}
		else if (Custom->Checked)
		{

		}
*/







//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THenlo *Henlo;

MyRectangle MyRectangle(0,0,0,0);
MyEllipse MyEllipse(0,0,0,0);
MyCircle MyCircle(0,0,0,0);
MySquare MySquare(0,0,0,0);
Triangle MyTriangle(0,0,0,0,0,0);

//---------------------------------------------------------------------------
__fastcall THenlo::THenlo(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

inline int sign(int x)
{
	if (x > 0)
	{
		return (1);
	}
	else if (x < 0)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void __fastcall THenlo::ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

    x1G = X;
	y1G = Y;

	if (Draw->Checked)
	{
		if (!(Rectangle->Checked) && !(Ellipse->Checked) && !(Circle->Checked) && !(Triangle->Checked) && !(Custom->Checked))
		{
			ShowMessage("Choose figure first");
			return;
		}

        if (Rectangle->Checked)
		{
			TimerForRectangleShow->Enabled = true;
		}
		else if (Circle->Checked)
		{
            TimerForCircleShow->Enabled = true;
		}
		else if (Ellipse->Checked)
		{
            TimerForEllipseShow->Enabled = true;
		}
		else if (Triangle->Checked)
		{
            TimerForSquareShow->Enabled=true;
		}
		else if (Custom->Checked)
		{
            TimerForTriangleShow->Enabled=true;
		}
	}
	else    /// Move units
	{
		if (Rectangle->Checked)
		{
			switch (MyRectangle.RectangleSide(x2G,y2G))
			{
				case (1):
				{
					TimerForRectangleSide->Enabled = true;
					break;
				}
				case (2):
				{
					TimerForRectangleSide2->Enabled = true;
					break;
				}
				case (3):
				{
					TimerForRectangleUp->Enabled = true;
					break;
				}
				case (4):
				{
					TimerForRectangleUp2->Enabled = true;
                    break;
				}
				case (5):
				{
                    TimerForRectangleMove->Enabled = true;
                }
				default:
				{
					break;
                }
			}
		}
		else if (Circle->Checked)
		{
            switch (MyCircle.EllipseSide(x2G,y2G))
			{
				case (1):
				{
					TimerForCircleSide->Enabled = true;
					break;
				}
				case (2):
				{
					TimerForCircleSide2->Enabled = true;
					break;
				}
				case (3):
				{
					TimerForCircleUp->Enabled = true;
					break;
				}
				case (4):
				{
					TimerForCircleUp2->Enabled = true;
                    break;
				}
				case (5):
				{
					TimerForCircleMove->Enabled = true;
                }
				default:
				{
					break;
                }
			}
		}
		else if (Ellipse->Checked)
		{
            switch (MyEllipse.EllipseSide(x2G,y2G))
			{
				case (1):
				{
					TimerForEllipseSide->Enabled = true;
					break;
				}
				case (2):
				{
					TimerForEllipseSide2->Enabled = true;
					break;
				}
				case (3):
				{
					TimerForEllipseUp->Enabled = true;
					break;
				}
				case (4):
				{
					TimerForEllipseUp2->Enabled = true;
                    break;
				}
				case (5):
				{
					TimerForEllipseMove->Enabled = true;
                }
				default:
				{
					break;
                }
			}
		}
		else if (Triangle->Checked)
		{
            switch (MySquare.RectangleSide(x2G,y2G))
			{
				case (1):
				{
					TimerForSquareSide->Enabled = true;
					break;
				}
				case (2):
				{
					TimerForSquareSide2->Enabled = true;
					break;
				}
				case (3):
				{
					TimerForSquareUp->Enabled = true;
					break;
				}
				case (4):
				{
					TimerForSquareUp2->Enabled = true;
                    break;
				}
				case (5):
				{
                    TimerForSquareMove->Enabled = true;
                }
				default:
				{
					break;
                }
			}
		}
		else if (Custom->Checked)
		{
			switch(MyTriangle.TriangleTop(x2G,y2G))
			{
				case (1):
				{
					TimerForTriangleTop1->Enabled = true;
					break;
				}
				case (2):
				{
					TimerForTriangleTop2->Enabled = true;
					break;
				}
				case (3):
				{
					TimerForTriangleTop3->Enabled = true;
					break;
				}
				case (4):
				{
					TimerForTriangleMove->Enabled = true;
					break;
				}
				default:
				{
					break;
                }
			}
		}


    }
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void __fastcall THenlo::ImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if (Draw->Checked)
	{
		if (!(Rectangle->Checked) && !(Ellipse->Checked) && !(Circle->Checked) && !(Triangle->Checked) && !(Custom->Checked))
		{
			return;
		}

		x2G = X;
	   	y2G = Y;

		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);

		/*
		if ((x2G >= Image->Width) || (y2G >= Image->Height) || (x2G <= 0) || (y2G <= 0))
		{
			ShowMessage("Can't draw here");
		   	return;
		}
        */

		if (Rectangle->Checked)
		{
			TimerForRectangleShow->Enabled = false;
			MyRectangle.Coordinates(x1G,y1G,x2G,y2G);
			MyRectangle.Show(Image->Canvas);
		}
		else if (Circle->Checked)
		{
			int r = 0;
			if (abs(x1G-x2G) < abs(y1G-y2G))
			{
				r = abs(x1G-x2G);
				y2G = y1G + r*(sign(y2G-y1G));
			}
			else
			{
				r = abs(y1G-y2G);
				x2G = x1G + r*(sign(x2G-x1G));
			}
			TimerForCircleShow->Enabled = false;
			MyCircle.Coordinates(x1G,y1G,x2G,y2G);
			MyCircle.Show(Image->Canvas);
		}
		else if (Ellipse->Checked)
		{
			TimerForEllipseShow->Enabled = false;
			MyEllipse.Coordinates(x1G,y1G,x2G,y2G);
			MyEllipse.Show(Image->Canvas);
		}
		else if (Triangle->Checked)
		{
            int r = 0;
			if (abs(x1G-x2G) < abs(y1G-y2G))
			{
				r = abs(x1G-x2G);
				y2G = y1G + r*(sign(y2G-y1G));
			}
			else
			{
				r = abs(y1G-y2G);
				x2G = x1G + r*(sign(x2G-x1G));
			}
			TimerForSquareShow->Enabled = false;
			MySquare.Coordinates(x1G,y1G,x2G,y2G);
			MySquare.Show(Image->Canvas);
		}
		else if (Custom->Checked)
		{
			TimerForTriangleShow->Enabled = false;
			MyTriangle.Coordinates(x1G,y1G,x2G,y2G,x1G,y2G);
			MyTriangle.Show(Image->Canvas);
		}
	}
	else    /// Move units
	{
		if (Rectangle->Checked)
		{
            TimerForRectangleSide->Enabled = false;
			TimerForRectangleSide2->Enabled = false;
			TimerForRectangleUp->Enabled = false;
			TimerForRectangleUp2->Enabled = false;
			TimerForRectangleMove->Enabled = false;
		}
		else if (Circle->Checked)
		{
			TimerForCircleSide->Enabled = false;
			TimerForCircleSide2->Enabled = false;
			TimerForCircleUp->Enabled = false;
			TimerForCircleUp2->Enabled = false;
			TimerForCircleMove->Enabled = false;
		}
		else if (Ellipse->Checked)
		{
			TimerForEllipseSide->Enabled = false;
			TimerForEllipseSide2->Enabled = false;
			TimerForEllipseUp->Enabled = false;
			TimerForEllipseUp2->Enabled = false;
			TimerForEllipseMove->Enabled = false;
		}
		else if (Triangle->Checked)
		{
			TimerForSquareSide->Enabled = false;
			TimerForSquareSide2->Enabled = false;
			TimerForSquareUp->Enabled = false;
			TimerForSquareUp2->Enabled = false;
			TimerForSquareMove->Enabled = false;
		}
		else if (Custom->Checked)
		{
			TimerForTriangleTop1->Enabled = false;
			TimerForTriangleTop2->Enabled = false;
			TimerForTriangleTop3->Enabled = false;
			TimerForTriangleMove->Enabled = false;
		}
	}


}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall THenlo::RectangleClick(TObject *Sender)
{
	if (Rectangle->Checked)
	{
		//Rectangle->Checked = false;
		Circle->Checked = false;
		Ellipse->Checked = false;
		Triangle->Checked = false;
        Custom->Checked = false;
	}

}
//---------------------------------------------------------------------------
void __fastcall THenlo::CircleClick(TObject *Sender)
{
	if (Circle->Checked)
	{
    	Rectangle->Checked = false;
		//Circle->Checked = false;
		Ellipse->Checked = false;
		Triangle->Checked = false;
		Custom->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::EllipseClick(TObject *Sender)
{
	if (Ellipse->Checked)
	{
    	Rectangle->Checked = false;
		Circle->Checked = false;
		//Ellipse->Checked = false;
		Triangle->Checked = false;
		Custom->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::TriangleClick(TObject *Sender)
{
	if (Triangle->Checked)
	{
		Rectangle->Checked = false;
		Circle->Checked = false;
		Ellipse->Checked = false;
		//Triangle->Checked = false;
		Custom->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::CustomClick(TObject *Sender)
{
	if (Custom->Checked)
	{
        Rectangle->Checked = false;
		Circle->Checked = false;
		Ellipse->Checked = false;
		Triangle->Checked = false;
		//Custom->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::DrawClick(TObject *Sender)
{
	if (Draw->Checked)
	{
		Move->Checked= false;

		Rotate->Enabled = true;
		Rectangle->Enabled = true;
		Circle->Enabled = true;
		Ellipse->Enabled = true;
		Triangle->Enabled = true;
		Custom->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::MoveClick(TObject *Sender)
{
    if (Move->Checked)
	{
		Draw->Checked= false;

        Rotate->Enabled = false;
		Rectangle->Enabled = false;
		Circle->Enabled = false;
		Ellipse->Enabled = false;
		Triangle->Enabled = false;
		Custom->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall THenlo::ImageMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	x2G = X;
	y2G = Y;
}
//---------------------------------------------------------------------------


void __fastcall THenlo::TimerForRectangleSideTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyRectangle.Coordinates(x2G,MyRectangle.y1,MyRectangle.x2,MyRectangle.y2);
	MyRectangle.Show(Image->Canvas);
	//MyRectangle.Show(Image->Canvas,MyRectangle.x2,MyRectangle.y2,x2G,MyRectangle.y1);
}
//---------------------------------------------------------------------------


void __fastcall THenlo::ImageMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
	//x2G = X;
	//y2G = Y;
}
//---------------------------------------------------------------------------


void __fastcall THenlo::TimerForRectangleSide2Timer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyRectangle.Coordinates(MyRectangle.x1,MyRectangle.y1,x2G,MyRectangle.y2);
	MyRectangle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForRectangleUpTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyRectangle.Coordinates(MyRectangle.x1,y2G,MyRectangle.x2,MyRectangle.y2);
	MyRectangle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForRectangleUp2Timer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyRectangle.Coordinates(MyRectangle.x1,MyRectangle.y1,MyRectangle.x2,y2G);
	MyRectangle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------


void __fastcall THenlo::TimerForRectangleMoveTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);

	//int xDelta = x1G - (MyRectangle.x1 + MyRectangle.x2)/2;
	//int yDelta = x1G - (MyRectangle.y1 + MyRectangle.y2)/2;

	MyRectangle.Coordinates(MyRectangle.x1 + x2G-x1G,MyRectangle.y1 + y2G-y1G,MyRectangle.x2 + x2G-x1G,MyRectangle.y2 + y2G-y1G) ;
	MyRectangle.Show(Image->Canvas);

	x1G = x2G;
	y1G = y2G;

	MyRectangle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForRectangleShowTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyRectangle.Coordinates(x1G,y1G,x2G,y2G);
    MyRectangle.Show(Image->Canvas);
	MyRectangle.s = abs((x1G-x2G)*(y1G-y2G));
}
//---------------------------------------------------------------------------


void __fastcall THenlo::RotateClick(TObject *Sender)
{

	if (Angle->Text == "")
	{
		ShowMessage("Enter the angle");
        return;
	}

    StopRotation->Enabled = true;
	Move->Enabled = false;
		if (Rectangle->Checked)
		{
			TimerForRectangleRotate->Enabled = true;
		}
		else if (Circle->Checked)
		{

		}
		else if (Ellipse->Checked)
		{
            TimerForEllipseRotate->Enabled = true;
		}
		else if (Triangle->Checked)
		{
            TimerForSquareRotate->Enabled = true;
		}
		else if (Custom->Checked)
		{
            TimerForTriangleRotate->Enabled = true;
		}

}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForRectangleRotateTimer(TObject *Sender)
{
	static double angle = 0;
	if (StrToInt(Angle->Text)>0)
	{
		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
		MyRectangle.ShowRotated(Image->Canvas,angle*3.141592653589793238463/180.);
		angle+=0.5;

		if (angle>=(StrToFloat(Angle->Text)+1))
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyRectangle.ShowRotated(Image->Canvas,StrToFloat(Angle->Text)*3.141592653589793238463/180.);
			Move->Enabled = true;
			angle = 0;
			TimerForRectangleRotate->Enabled = false;
			MyRectangle.Coordinates(0,0,0,0);
			Image->Canvas->Pen->Color=clWhite;
		}
	}
	/*
	else if (StrToInt(Angle->Text)<0)
	{
		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
		MyRectangle.ShowRotated(Image->Canvas,angle--);

        if (angle<=StrToInt(Angle->Text))
		{
			angle = 0;
			TimerForRectangleRotate->Enabled = false;
		}
	}
    */
}


//---------------------------------------------------------------------------


void __fastcall THenlo::StopRotationClick(TObject *Sender)
{
	Move->Enabled = true;
		if (Rectangle->Checked)
		{
            TimerForRectangleRotate->Enabled = false;
			MyRectangle.Coordinates(0,0,0,0);
		}
		else if (Circle->Checked)
		{

		}
		else if (Ellipse->Checked)
		{
			TimerForEllipseRotate->Enabled = false;
            MyEllipse.Coordinates(0,0,0,0);
		}
		else if (Triangle->Checked)
		{

		}
		else if (Custom->Checked)
		{

		}

    StopRotation->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall THenlo::SquareTimer(TObject *Sender)
{
		if (Rectangle->Checked)
		{
			SquareText->Caption = MyRectangle.s;
		}
		else if (Circle->Checked)
		{
			SquareText->Caption = MyCircle.s;
		}
		else if (Ellipse->Checked)
		{
			SquareText->Caption = MyEllipse.s;
		}
		else if (Triangle->Checked)
		{
            SquareText->Caption = MySquare.s;
		}
		else if (Custom->Checked)
		{
            SquareText->Caption = MyTriangle.s;
		}
}
//---------------------------------------------------------------------------


void __fastcall THenlo::Timer(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{       	int xD = 2, yD = 2;
		if (Rectangle->Checked)
		{	//y = (y1-y2)/(x1-x2)x
            if ((MyRectangle.x1==MyRectangle.x2)|| (MyRectangle.y1==MyRectangle.y2))
			{
				return;
			}
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyRectangle.Coordinates(MyRectangle.x1-xD,MyRectangle.y1-yD,MyRectangle.x2+xD,MyRectangle.y2+yD);
			MyRectangle.Show(Image->Canvas);
		}
		else if (Circle->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyCircle.Coordinates(MyCircle.x1-xD,MyCircle.y1-yD,MyCircle.x2+xD,MyCircle.y2+yD);
			MyCircle.Show(Image->Canvas);
		}
		else if (Ellipse->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyEllipse.Coordinates(MyEllipse.x1-xD,MyEllipse.y1-yD,MyEllipse.x2+xD,MyEllipse.y2+yD);
			MyEllipse.Show(Image->Canvas);
		}
		else if (Triangle->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MySquare.Coordinates(MySquare.x1-xD,MySquare.y1-yD,MySquare.x2+xD,MySquare.y2+yD);
			MySquare.Show(Image->Canvas);
		}
		else if (Custom->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyTriangle.Coordinates(MyTriangle.x1-xD,MyTriangle.y1-yD,MyTriangle.x2+xD,MyTriangle.y2+yD,MyTriangle.x3-xD,MyTriangle.y3+yD);
            MyTriangle.Square();
			MyTriangle.Show(Image->Canvas);
		}
}
//---------------------------------------------------------------------------

void __fastcall THenlo::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
		int xD = -2, yD = -2;
		if (Rectangle->Checked)
		{
			if ((MyRectangle.x1==MyRectangle.x2)|| (MyRectangle.y1==MyRectangle.y2))
			{
				return;
			}
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyRectangle.Coordinates(MyRectangle.x1-xD,MyRectangle.y1-yD,MyRectangle.x2+xD,MyRectangle.y2+yD);
			MyRectangle.Show(Image->Canvas);
		}
		else if (Circle->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
            if ((MyCircle.x1==MyCircle.x2)|| (MyCircle.y1==MyCircle.y2))
			{
				return;
			}
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyCircle.Coordinates(MyCircle.x1-xD,MyCircle.y1-yD,MyCircle.x2+xD,MyCircle.y2+yD);
			MyCircle.Show(Image->Canvas);
		}
		else if (Ellipse->Checked)
		{
            if ((MyEllipse.x1==MyEllipse.x2)|| (MyEllipse.y1==MyEllipse.y2))
			{
				return;
			}
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyEllipse.Coordinates(MyEllipse.x1-xD,MyEllipse.y1-yD,MyEllipse.x2+xD,MyEllipse.y2+yD);
			MyEllipse.Show(Image->Canvas);
		}
		else if (Triangle->Checked)
		{   if ((MySquare.x1==MySquare.x2)|| (MySquare.y1==MySquare.y2))
			{
				return;
			}
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MySquare.Coordinates(MySquare.x1-xD,MySquare.y1-yD,MySquare.x2+xD,MySquare.y2+yD);
			MySquare.Show(Image->Canvas);
		}
		else if (Custom->Checked)
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyTriangle.Coordinates(MyTriangle.x1-xD,MyTriangle.y1-yD,MyTriangle.x2+xD,MyTriangle.y2+yD,MyTriangle.x3-xD,MyTriangle.y3+yD);
            MyTriangle.Square();
			MyTriangle.Show(Image->Canvas);
		}
}
//---------------------------------------------------------------------------





void __fastcall THenlo::TimerForEllipseShowTimer(TObject *Sender)
{	//
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(x1G,y1G,x2G,y2G);
	MyEllipse.Show(Image->Canvas);
	MyEllipse.s =  3.141592653589793238463*(abs((MyEllipse.x1-MyEllipse.x2)*(MyEllipse.y1 - MyEllipse.y2)))/4;
}
//---------------------------------------------------------------------------




void __fastcall THenlo::TimerForEllipseUp2Timer(TObject *Sender)
{
	//
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(MyEllipse.x1,MyEllipse.y1,MyEllipse.x2,y2G);
	MyEllipse.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForEllipseUpTimer(TObject *Sender)
{
//
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(MyEllipse.x1,y2G,MyEllipse.x2,MyEllipse.y2);
	MyEllipse.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForEllipseSide2Timer(TObject *Sender)
{
//
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(MyEllipse.x1,MyEllipse.y1,x2G,MyEllipse.y2);
	MyEllipse.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForEllipseSideTimer(TObject *Sender)
{
//
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(x2G,MyEllipse.y1,MyEllipse.x2,MyEllipse.y2);
	MyEllipse.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForEllipseRotateTimer(TObject *Sender)
{
//
    static double angle = 0;
	if (StrToInt(Angle->Text)>0)
	{
		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
		MyEllipse.ShowRotated(Image->Canvas,angle*3.141592653589793238463/180.);
		angle+=0.5;

		if (angle>=(StrToFloat(Angle->Text)+1))
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyEllipse.ShowRotated(Image->Canvas,StrToFloat(Angle->Text)*3.141592653589793238463/180.);
			Move->Enabled = true;
			angle = 0;
			TimerForEllipseRotate->Enabled = false;
			MyEllipse.Coordinates(0,0,0,0);
			Image->Canvas->Pen->Color=clWhite;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForEllipseMoveTimer(TObject *Sender)
{
	//
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(MyEllipse.x1 + x2G-x1G,MyEllipse.y1 + y2G-y1G,MyEllipse.x2 + x2G-x1G,MyEllipse.y2 + y2G-y1G) ;
	MyEllipse.Show(Image->Canvas);

	x1G = x2G;
	y1G = y2G;

	MyEllipse.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleShowTimer(TObject *Sender)
{
	int r = 0;
	if (abs(x1G-x2G) < abs(y1G-y2G))
	{
		r = abs(x1G-x2G);
		y2G = y1G + r*(sign(y2G-y1G));
	}
	else
	{
		r = abs(y1G-y2G);
		x2G = x1G + r*(sign(x2G-x1G));
	}
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyCircle.Coordinates(x1G,y1G,x2G,y2G);
	MyCircle.Show(Image->Canvas);



	/*
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	Image->Canvas->Rectangle(x1G,y1G,x2G,y2G);
	MyRectangle.s = abs((x1G-x2G)*(y1G-y2G));
    */
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleMoveTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyCircle.Coordinates(MyCircle.x1 + x2G-x1G,MyCircle.y1 + y2G-y1G,MyCircle.x2 + x2G-x1G,MyCircle.y2 + y2G-y1G) ;
	MyCircle.Show(Image->Canvas);

	x1G = x2G;
	y1G = y2G;

	MyCircle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleUp2Timer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(y2G - MyCircle.y1);
	MyCircle.Coordinates(MyCircle.x1,MyCircle.y1,MyCircle.x1 + d*sign(MyCircle.x2-MyCircle.x1),y2G);
	MyCircle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleUpTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(y2G - MyCircle.y2);
	MyCircle.Coordinates(MyCircle.x1,y2G,MyCircle.x1+d*sign(MyCircle.x2-MyCircle.x1),MyCircle.y2);
	MyCircle.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleSide2Timer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(x2G - MyCircle.x1);
	MyCircle.Coordinates(MyCircle.x1,MyCircle.y1,x2G,MyCircle.y1 + d*sign(MyCircle.y2 - MyCircle.y1));
	MyCircle.Show(Image->Canvas);

	/*MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(MyEllipse.x1,MyEllipse.y1,x2G,MyEllipse.y2);
	MyEllipse.Show(Image->Canvas);*/
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForCircleSideTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(MyCircle.x2 - x2G);
	MyCircle.Coordinates(x2G,MyCircle.y1,MyCircle.x2,MyCircle.y1 + d*sign(MyCircle.y2 - MyCircle.y1));
	MyCircle.Show(Image->Canvas);

    /*MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyEllipse.Coordinates(x2G,MyEllipse.y1,MyEllipse.x2,MyEllipse.y2);
	MyEllipse.Show(Image->Canvas);*/
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareMoveTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MySquare.Coordinates(MySquare.x1 + x2G-x1G,MySquare.y1 + y2G-y1G,MySquare.x2 + x2G-x1G,MySquare.y2 + y2G-y1G) ;
	MySquare.Show(Image->Canvas);

	x1G = x2G;
	y1G = y2G;

	MySquare.Show(Image->Canvas);

	
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareShowTimer(TObject *Sender)
{
    int r = 0;
	if (abs(x1G-x2G) < abs(y1G-y2G))
	{
		r = abs(x1G-x2G);
		y2G = y1G + r*(sign(y2G-y1G));
	}
	else
	{
		r = abs(y1G-y2G);
		x2G = x1G + r*(sign(x2G-x1G));
	}
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MySquare.Coordinates(x1G,y1G,x2G,y2G);
	MySquare.Show(Image->Canvas);
    MySquare.s = (x2G-x1G)*(x2G-x1G);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareUp2Timer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(y2G - MySquare.y1);
	MySquare.Coordinates(MySquare.x1,MySquare.y1,MySquare.x1 + d*sign(MySquare.x2-MySquare.x1),y2G);
	MySquare.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareUpTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(y2G - MySquare.y2);
	MySquare.Coordinates(MySquare.x1,y2G,MySquare.x1+d*sign(MySquare.x2-MySquare.x1),MySquare.y2);
	MySquare.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareSide2Timer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(x2G - MySquare.x1);
	MySquare.Coordinates(MySquare.x1,MySquare.y1,x2G,MySquare.y1 + d*sign(MySquare.y2 - MySquare.y1));
	MySquare.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareSideTimer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	int d = abs(MySquare.x2 - x2G);
	MySquare.Coordinates(x2G,MySquare.y1,MySquare.x2,MySquare.y1 + d*sign(MySquare.y2 - MySquare.y1));
	MySquare.Show(Image->Canvas);
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForSquareRotateTimer(TObject *Sender)
{
    static double angle = 0;
	if (StrToInt(Angle->Text)>0)
	{
		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
		MySquare.ShowRotated(Image->Canvas,angle*3.141592653589793238463/180.);
		angle+=0.5;

		if (angle>=(StrToFloat(Angle->Text)+1))
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MySquare.ShowRotated(Image->Canvas,StrToFloat(Angle->Text)*3.141592653589793238463/180.);
			Move->Enabled = true;
			angle = 0;
			TimerForSquareRotate->Enabled = false;
			MySquare.Coordinates(0,0,0,0);
			Image->Canvas->Pen->Color=clWhite;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForTriangleShowTimer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);

	MyTriangle.Coordinates(x1G,y1G,x2G,y2G,x1G,y2G);
	MyTriangle.Show(Image->Canvas);

	int p = (sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2))+
				sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3))+
				sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))/2;

	MyTriangle.s = sqrt(p*(p-sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2)))*
					(p - sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3)))*
					(p - sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1))));

	/*
	Image->Canvas->MoveTo(x1G,y1G);
	Image->Canvas->LineTo(x2G,y2G);
	Image->Canvas->LineTo(x1G,y2G);
	Image->Canvas->LineTo(x1G,y1G);
	*/
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForTriangleTop1Timer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyTriangle.Coordinates(x2G, y2G, MyTriangle.x2,MyTriangle.y2,MyTriangle.x3,MyTriangle.y3);
	MyTriangle.Show(Image->Canvas);

	double p = (sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2))+
				sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3))+
				sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))/2;

	MyTriangle.s = (int)(sqrt(p*(p-sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2)))*
					(p - sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3)))*
					(p - sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))));
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForTriangleTop2Timer(TObject *Sender)
{
	MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyTriangle.Coordinates(MyTriangle.x1,MyTriangle.y1,x2G,y2G,MyTriangle.x3,MyTriangle.y3);
	MyTriangle.Show(Image->Canvas);

	double p = (sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2))+
				sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3))+
				sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))/2;

	MyTriangle.s = (int)(sqrt(p*(p-sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2)))*
					(p - sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3)))*
					(p - sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))));
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForTriangleTop3Timer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyTriangle.Coordinates(MyTriangle.x1,MyTriangle.y1,MyTriangle.x2,MyTriangle.y2,x2G,y2G);
	MyTriangle.Show(Image->Canvas);

	double p = (sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2))+
				sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3))+
				sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))/2;

	MyTriangle.s = (int)(sqrt(p*(p-sqrt((MyTriangle.x1-MyTriangle.x2)*(MyTriangle.x1-MyTriangle.x2) + (MyTriangle.y1-MyTriangle.y2)*(MyTriangle.y1-MyTriangle.y2)))*
					(p - sqrt((MyTriangle.x2-MyTriangle.x3)*(MyTriangle.x2-MyTriangle.x3) + (MyTriangle.y2-MyTriangle.y3)*(MyTriangle.y2-MyTriangle.y3)))*
					(p - sqrt((MyTriangle.x3-MyTriangle.x1)*(MyTriangle.x3-MyTriangle.x1) + (MyTriangle.y3-MyTriangle.y1)*(MyTriangle.y3-MyTriangle.y1)))));
}
//---------------------------------------------------------------------------

void __fastcall THenlo::TimerForTriangleMoveTimer(TObject *Sender)
{
    MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
	MyTriangle.Coordinates(MyTriangle.x1 + x2G-x1G,MyTriangle.y1 + y2G-y1G,MyTriangle.x2 + x2G-x1G,MyTriangle.y2 + y2G-y1G, MyTriangle.x3 + x2G - x1G, MyTriangle.y3 + y2G - y1G) ;
	MyTriangle.Show(Image->Canvas);

	x1G = x2G;
	y1G = y2G;
}
//---------------------------------------------------------------------------




void __fastcall THenlo::TimerForTriangleRotateTimer(TObject *Sender)
{
    static double angle = 0;
	if (StrToInt(Angle->Text)>0)
	{
		MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
		MyTriangle.ShowRotated(Image->Canvas,angle*3.141592653589793238463/180.);
		angle+=0.5;

		if (angle>=(StrToFloat(Angle->Text)+1))
		{
			MyRectangle.Hide(Image->Canvas,0,0,Image->Width,Image->Height);
			MyTriangle.ShowRotated(Image->Canvas,StrToFloat(Angle->Text)*3.141592653589793238463/180.);
			Move->Enabled = true;
			angle = 0;
			TimerForTriangleRotate->Enabled = false;
			MyTriangle.Coordinates(0,0,0,0,0,0);
			Image->Canvas->Pen->Color=clWhite;
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall THenlo::CenterCoordinatesTimer(TObject *Sender)
{
	int xC = 0, yC = 0;

    if (Rectangle->Checked)
		{
			xC = (MyRectangle.x1 + MyRectangle.x2)/2;
            yC = (MyRectangle.y1 + MyRectangle.y2)/2;
		}
		else if (Circle->Checked)
		{
			xC = (MyCircle.x1 + MyCircle.x2)/2;
			yC = (MyCircle.y1 + MyCircle.y2)/2;
		}
		else if (Ellipse->Checked)
		{
			xC = (MyEllipse.x1 + MyEllipse.x2)/2;
			yC = (MyEllipse.y1 + MyEllipse.y2)/2;
		}
		else if (Triangle->Checked)
		{
			xC = (MySquare.x1 + MySquare.x2)/2;
			yC = (MySquare.y1 + MySquare.y2)/2;
		}
		else if (Custom->Checked)
		{
			xC = (MyTriangle.x1 + MyTriangle.x2 + MyTriangle.x3)/3;
			yC = (MyTriangle.y1 + MyTriangle.y2 + MyTriangle.y3)/3;
		}

		xCenter->Caption = xC;
        yCenter->Caption = yC;
}
//---------------------------------------------------------------------------



