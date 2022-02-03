//---------------------------------------------------------------------------

#ifndef RectangleH
#define RectangleH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>


class MyRectangle
{
	public:
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int s = 0;

	public:

	MyRectangle(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
    }

    void Coordinates(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
    }

	void Show(TCanvas * Canvas)
	{
        Canvas->Pen->Color=clBlack;
		Canvas->Rectangle(x1,y1,x2,y2);
        s = abs((x2-x1)*(y2-y1));
	}

	void Show(TCanvas * Canvas,int x1, int y1, int x2, int y2)
	{
		Canvas->Pen->Color=clBlack;
		Canvas->Rectangle(x1,y1,x2,y2);
	}

	void Hide(TCanvas * Canvas)
	{
		Canvas->Pen->Color = clWhite;
		Canvas->Brush->Color = clWhite;

		Canvas->Rectangle(x1,y1,x2,y2);

		Canvas->Pen->Color = clBlack;
		Canvas->Brush->Color = clWhite;
	}

    void Hide(TCanvas * Canvas, int x1, int y1, int x2, int y2)
	{
		Canvas->Pen->Color = clWhite;
		Canvas->Brush->Color = clWhite;

		Canvas->Rectangle(x1,y1,x2,y2);

        Canvas->Pen->Color = clBlack;
		Canvas->Brush->Color = clWhite;
	}

	int RectangleSide(int X, int Y)
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

	void ShowRotated(TCanvas * Canvas, double angle)
	{    /*
		int _x1 = (int)((double)(x1 - (x2+x1)/2)*cos(angle) + (double)(y1 - (y2+y1)/2)*sin(angle));
		int _y1 = (int)((double)(-(x1 - (x2+x1)))*sin(angle) + (double)(y1 - (y2+y1)/2)*cos(angle));

		int _x2 = (int)((double)(x2 - (x2+x1)/2)*cos(angle) + (double)(y2 - (y2+y1)/2)*sin(angle));
		int _y2 = (int)((double)(-(x2 - (x2+x1)/2))*sin(angle) + (double)(y2 - (y2+y1)/2)*cos(angle));

		_x1 += (x2+x1)/2;
		_x2 += (x2+x1)/2;
		_y1 += (y2+y1)/2;
		_y2 += (y2+y1)/2;
		*/

		int _x1 = x1 - (x1+x2)/2;
		int _y1 = y1 - (y1+y2)/2;
		int _x2 = x2 - (x1+x2)/2;
		int _y2 = y2 - (y1+y2)/2;



		//A(x1,y1)
		//B(x2,y1)
		//C(x2,y2)
        //D(x1,y2)

        int Ax=0,Ay=0,Bx=0,By=0,Cx=0,Cy=0,Dx=0,Dy=0;

		Ax = (int)(    (double)(_x1)*Cos(angle) + (double)(_y1)*Sin(angle)    		  	);
		Ay = (int)(    (double)(_x1)*(-Sin(angle)) + (double)(_y1)*Cos(angle)		 	);

		Bx = (int)(    (double)(_x2)*Cos(angle) + (double)(_y1)*Sin(angle)    		  	);
		By = (int)(    (double)(_x2)*(-Sin(angle)) + (double)(_y1)*Cos(angle)		 	);

		Cx = (int)(    (double)(_x2)*Cos(angle) + (double)(_y2)*Sin(angle)	   	  		);
		Cy = (int)(    (double)(_x2)*(-Sin(angle)) + (double)(_y2)*Cos(angle)	  		);

		Dx = (int)(    (double)(_x1)*Cos(angle) + (double)(_y2)*Sin(angle)	   	  		);
		Dy = (int)(    (double)(_x1)*(-Sin(angle)) + (double)(_y2)*Cos(angle)	  		);

		//s =  (   sqrt((Ax-Bx)*(Ax-Bx) + (Ay-By)*(Ay-By))   )*(   sqrt((Bx-Cx)*(Bx-Cx) + (By-Cy)*(By-Cy))   );


		Ax += (x1+x2)/2;
		Bx += (x1+x2)/2;
		Cx += (x1+x2)/2;
		Dx += (x1+x2)/2;

		Ay += (y1+y2)/2;
		By += (y1+y2)/2;
		Cy += (y1+y2)/2;
		Dy += (y1+y2)/2;


		Canvas->MoveTo(Ax,Ay);
		Canvas->LineTo(Bx,By);
		Canvas->LineTo(Cx,Cy);
		Canvas->LineTo(Dx,Dy);
		Canvas->LineTo(Ax,Ay);


		//(0,0) = ((x1-x2)/2,(y1-y2)/2)
	}


	public:
	~MyRectangle(){};
};
