template<typename T>
class Node
{
public:
	Node(T data = T(), Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
		this->pPrev = pPrev;
	}

	Node<T>* pNext;
	Node<T>* pPrev;
	T data;
};

template<typename T>
class Container
{
public:
	Container();
	~Container();

	void push_back (T data);
	void pop();
	T& top();
	void remove(unsigned int index = 0);
	void insert(T data, unsigned int index = 0);
	T& operator[] (unsigned int index);
	void clear();

	unsigned int Size() { return size; }

private:

	unsigned int size;
	Node<T>* head;
	Node<T>* tale;

};

template<typename T>
T& Container<T>::top()
{
	return tale->data;
}

template<typename T>
void Container<T>::pop()
{
	if (!size)
	{
		return;
	}
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tale = nullptr;
	}
	else
	{
		tale = tale->pPrev;
		delete(tale->pNext);
		tale->pNext = nullptr;
	}
	
	size--;
}

template<typename T>
Container<T>::Container()
{
	size = 0;
	head = nullptr;
	tale = nullptr;
}

template<typename T>
void Container<T>::clear()
{
	if (!size)
	{
		return;
	}

	Node<T>* temp = head;
	head = head->pNext;
	for (; head; head = head->pNext)
	{
		delete temp;
		temp = head;
	}
	delete temp;

	size = 0;
}


template<typename T>
Container<T>::~Container()
{
	clear();
}

template<typename T>
void Container<T>::push_back(T data)
{
	if (!size)
	{
		head = new Node<T>(data);
		tale = head;
	}
	else
	{
		tale->pNext = new Node<T>(data);
		tale->pNext->pPrev = tale;
		tale = tale->pNext;
		tale->pNext = nullptr;
	}

	size++;
}

template<typename T>
T& Container<T>::operator[](unsigned int index)
{
	unsigned int counter = 0;
	for(Node<T>* current = head; current; current = current->pNext, counter++)
	{
		if (counter == index)
		{
			return current->data;
		}
	}
}

template<typename T>
void Container<T>::remove(unsigned int index)
{
	if (!size)
	{
		return;
	}

	if (!index)
	{
		if (size == 1) {
		   delete(head);
		   head = nullptr;
		   size--;
           return;
		}

		head = head->pNext;
		delete(head->pPrev);
		head->pPrev = nullptr;

		size--;

		return;
	}

	if (index == size - 1)
	{
		tale = tale->pPrev;
		delete(tale->pNext);
		tale->pNext = nullptr;
		
		size--;
		return;
	}

	unsigned int counter = 0;


	for (Node<T>* current = head; current; current = current->pNext, counter++)
	{
		if (counter + 1 == index)
		{
			Node<T>* temp = current->pNext;
			current->pNext = temp->pNext;
			delete(temp);
			size--;

			return;
		}
		
	}
}

template<typename T>
void Container<T>::insert(T data, unsigned int index)
{
	if (!index)
	{
		Node<T>* temp = new Node<T>(data);
		temp->pNext = head;
		head = temp;
		size++;
		return;
	}

	if (index == size - 1)
	{
		Node<T>* temp = new Node<T>(data);
		tale->pPrev->pNext = temp;
		temp->pPrev = tale->pPrev;
		temp->pNext = tale;
		tale->pPrev = temp;
		size++;

		return;
	}

	if (index == size)
	{
		tale->pNext = new Node<T>(data);
		tale->pNext->pPrev = tale;
		tale = tale->pNext;
		tale->pNext = nullptr;
		size++;

		return;
	}

	unsigned int counter = 0;
	for (Node<T>* current = head; current; current = current->pNext, counter++)
	{
		if (counter + 1 == index)
		{
			Node<T>* temp = current->pNext;
			current->pNext = new Node<T>(data);
			current->pNext->pNext = temp;

			size++;

			return;
		}
	}
}