template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

template<typename T>
class Container
{
public:
	Container();
	~Container();

	void push_back (T data);
	void remove(unsigned int index);
	void insert(T data, unsigned int index);
	T& operator[] (unsigned int index);
	void clear();

	unsigned int GetSize() { return size; }

private:
	unsigned int size;
	Node<T>* head;

};

template<typename T>
Container<T>::Container()
{
	size = 0;
	head = nullptr;
}

template<typename T>
void Container<T>::clear()
{
	head = head->pNext;
	for (Node<T>* temp = head; head; head = head->pNext)
	{
		delete temp;
		temp = head;
	}
}


template<typename T>
Container<T>::~Container()
{
	clear();
}

template<typename T>
void Container<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = head;
		for (; current->pNext; current = current->pNext);
		current->pNext = new Node<T>(data);
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
	if (index == 0)
	{
		Node<T>* temp = head;
		head = head->pNext;
		delete(temp);
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
	if (index == 0)
	{
		Node<T>* temp = new Node<T>(data);
		temp->pNext = head;
		head = temp;
		size++;
		return;
	}

	unsigned int counter = 0;
	for (Node<T>* current = head; current; current = current->pNext)
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