//---------------------------------------------------------------------------

#ifndef SmartPointerH
#define SmartPointerH
//---------------------------------------------------------------------------
#endif


template<typename T>
class SmartPointer
{
public:
	SmartPointer(T* ptr = nullptr)
	{
        this->ptr = ptr;
	}

	~SmartPointer()
	{
    	delete ptr;
	}

	T& operator*()
	{
        return *ptr;
	}

private:
    T* ptr;
};
