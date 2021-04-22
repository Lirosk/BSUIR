//---------------------------------------------------------------------------

#ifndef TriangleH
#define TriangleH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#include "Rectangle.h"

class MySquare: public MyRectangle
{
	public:
	MySquare(int x1, int y1, int x2, int y2): MyRectangle(x1,y1,x2,y2) {};

	~MySquare(){};
};
