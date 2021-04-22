#include <exception>

template <typename T>
class Mstack
{
public:

	//конструктор
	Mstack() { _top = nullptr; size = 0; }

	//деструктор
    ~Mstack();

	//вернуть размер
	unsigned int Size() { return size; }

	//добавить эл-т "вверх"
	void push(T data);

	//удалить "верхний" эл-т
	void pop();

	//вернуть "верхний" эл-т
    T& top();


    //template<typename T>
    class node
    {
    public:
        node(T el, node* pnext = nullptr) : data(el)
        {
            this->pnext = pnext;
        }

        node* pnext;
        T data;
    };


private:
	//размер
	unsigned int size;

	//указатель на "верхний" эл-т
	node* _top;
};


template <typename T>
void Mstack<T>::push(T data)
{
    node* temp = new node(data);
    temp->pnext = _top;
    _top = temp;

    size++;

}

template <typename T>
void Mstack<T>::pop()
{
    node* temp = _top;
    _top = _top->pnext;
    delete temp;
    size--;
}

template <typename T>
T& Mstack<T>::top()
{
    return _top->data;
}

template <typename T>
Mstack<T>::~Mstack<T>()
{
    while (size)
    {
        pop();
    }
}