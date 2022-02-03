//---------------------------------------------------------------------------

#ifndef CustomH
#define CustomH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>

int sign (double x)
{
	if (x<0) {
		return (-1);
	}
	else if (x>0)
	{
			 return 1;
	}
    return 0;
}

class Triangle
{
   public:
   int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0,
   s = 0;

   Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
   {
	this->x1=x1;
	this->x2=x2;
	this->x3=x3;
	this->y1=y1;
	this->y2=y2;
	this->y3=y3;
   }

   void Show(TCanvas* Canvas)
   {
        Canvas->Pen->Color=clBlack;

	   Canvas->MoveTo(x1,y1);
	   Canvas->LineTo(x2,y2);
	   Canvas->LineTo(x3,y3);
	   Canvas->LineTo(x1,y1);
   }

   void Coordinates(int x1, int y1, int x2, int y2, int x3, int y3)
   {
      	this->x1=x1;
		this->x2=x2;
		this->x3=x3;
		this->y1=y1;
		this->y2=y2;
		this->y3=y3;
   }

   int TriangleTop (int x, int y)
   {
	   if ((abs(x-x1) < 5) && (abs(y - y1) < 5))
	   {
			return 1;
	   }
	   else if ((abs(x-x2) < 5) && (abs(y-y2) < 5))
	   {
			return 2;
	   }
	   else if ((abs(x-x3) < 5)&&(abs(y-y3) < 5))
	   {
			return 3;
	   }
	   else if (

				(sign((x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y)) ==
				sign((x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y))) &&
				(sign((x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y)) ==
				sign((x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y)))


				)
	   {
            return 4;
	   }

		   return 0;
   }

   void Square()
   {
	  double p = (sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))+
				sqrt((x2-x3)*(x2-x3) + (y2-y3)*(y2-y3))+
				sqrt((x3-x1)*(x3-x1) + (y3-y1)*(y3-y1)))/2;

	s = (int)(sqrt(p*(p-sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)))*
					(p - sqrt((x2-x3)*(x2-x3) + (y2-y3)*(y2-y3)))*
					(p - sqrt((x3-x1)*(x3-x1) + (y3-y1)*(y3-y1)))));
   }

   void ShowRotated(TCanvas* Canvas, double angle)
   {
	   int xCenter = (x1+x2+x3)/3, yCenter = (y1+y2+y3)/3;

	   int 	_x1 = x1 - xCenter,
			_x2 = x2 - xCenter,
			_x3 = x3 - xCenter,

			_y1 = y1 - yCenter,
			_y2 = y2 - yCenter,
       		_y3 = y3 - yCenter;


	   int Ax = (int)(    	(double)(_x1)*Cos(angle) + (double)(_y1)*Sin(angle)    		   		),
	   Ay = (int)(    		(double)(_x1)*(-Sin(angle)) + (double)(_y1)*Cos(angle)		 		),

	   Bx = (int)(    		(double)(_x2)*Cos(angle) + (double)(_y2)*Sin(angle)    		  		),
	   By = (int)(    		(double)(_x2)*(-Sin(angle)) + (double)(_y2)*Cos(angle)		 		),

	   Cx = (int)(    		(double)(_x3)*Cos(angle) + (double)(_y3)*Sin(angle)	   	  			),
	   Cy = (int)(    		(double)(_x3)*(-Sin(angle)) + (double)(_y3)*Cos(angle)	  			);

	   Ax += xCenter;
	   Bx += xCenter;
	   Cx += xCenter;
	   Ay += yCenter;
	   By += yCenter;
       Cy += yCenter;


       Canvas->MoveTo(Ax,Ay);
	   Canvas->LineTo(Bx,By);
	   Canvas->LineTo(Cx,Cy);
	   Canvas->LineTo(Ax,Ay);

   }

 ~Triangle(){};
} ;
