//---------------------------------------------------------------------------

#ifndef CircleH
#define CircleH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#include "Ellipse.h"


class MyCircle: public MyEllipse
{
	public:

	MyCircle (int x1, int y1, int x2, int y2): MyEllipse(x1,y1,x2,y2){}
	~MyCircle(){};
};
