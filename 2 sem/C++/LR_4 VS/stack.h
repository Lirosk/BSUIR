#include <exception>

template <typename T>
class Mstack
{
public:

    Mstack() { _top = nullptr; size = 0; }
    ~Mstack();

    unsigned int Size() { return size; }
    void push(T data);
    void pop();
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
    unsigned int size;
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