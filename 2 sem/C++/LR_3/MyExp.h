//---------------------------------------------------------------------------

#ifndef MyExpH
#define MyExpH
//---------------------------------------------------------------------------
#endif

#include <exception>

class MyException: public std::exception
{
public:
	MyException(char* msg): std::exception(msg)
	{}

private:

};
