//---------------------------------------------------------------------------

#ifndef EllipseH
#define EllipseH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>

class MyEllipse
{
	public:
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0,
	s = 0;

	void Show(TCanvas* Canvas)
	{
        Canvas->Pen->Color=clBlack;
		Canvas->Ellipse(x1,y1,x2,y2);
        s = abs((x1-x2)*(y1-y2));
	}

	MyEllipse(int x1,int y1,int x2,int y2)
	{
		this->x1=x1;
		this->y1=y1;
		this->x2=x2;
		this->y2=y2;
	}

	void Coordinates(int x1,int y1,int x2,int y2)
	{
        this->x1=x1;
		this->y1=y1;
		this->x2=x2;
		this->y2=y2;
    }

    int EllipseSide(int X, int Y)
	{
		if ((abs(x1-X) < 5) && (((Y > y1) && (Y < y2)) || ((Y<y1) && (Y>y2))))
		{
			return 1;
		}
		else if ((abs(x2-X) < 5) && (((Y > y1) && (Y < y2)) || ((Y<y1) && (Y>y2))))
		{
			return 2;
		}
		else if ((abs(y1 - Y) < 5) && (((X>x1) && (X<x2)) || ((X<x1) && (X>x2))))
		{
			return 3;
		}
		else if ((abs(y2-Y) < 5) && (((X>x1) && (X<x2)) || ((X<x1) && (X>x2))))
		{
			return 4;
		}
		else if ((((Y > y1) && (Y < y2)) || ((Y<y1) && (Y>y2))) && (((X>x1) && (X<x2)) || ((X<x1) && (X>x2))))
		{
			return 5;
		}

        return 0;
	}

	void ShowRotated(TCanvas* Canvas, double angle)
	{
		int a = abs(x1-x2)/2, b = abs(y1-y2)/2;
		//t = [0,2pi]

		int centerX = (x1+x2)/2, centerY = (y1+y2)/2;

		int t = 0, x = 0, y = 0;
		for (;t <= 360; t++)
		{
			x = a*cos(t*3.141592653589793238463/180.), y = b*sin(t*3.141592653589793238463/180.);
			RotatePoints(x,y,angle);
			//Canvas->Pixels[x+centerX][y+centerY]=clBlack;
			if (t == 0) {
				Canvas->MoveTo(x + centerX,y + centerY);
                continue;
			}
			Canvas->LineTo(x + centerX,y + centerY);
			//Canvas->MoveTo(x,y);
		}

	}

	void RotatePoints(int& X, int& Y, double angle)
	{

	   int	XTemp = (int)(    (double)(X)*Cos(angle) + (double)(Y)*Sin(angle)    		  	);
	   int	YTemp = (int)(    (double)(X)*(-Sin(angle)) + (double)(Y)*Cos(angle)		 	);
	   X = XTemp;
       Y = YTemp;
    }

	~MyEllipse(){};
};
