typedef unsigned char uc;

template<typename T>
class node
{
public:
	//ptr to right
	node* r;

    //ptr to left
	node* l;

private:
	//height
	uc height;

	//item
	T data;

public:
	//init
	node(T data = T(), node<T>* l = nullptr, node<T>* r = nullptr)
	{
		this->data = data;
		this->r = r;
		this->l = l;
		this->height = 0;
	}

	//delete
	~node()
	{
		if (r)
		{
			delete r;
            r = nullptr;
		}

		if (l)
		{
			delete l;
            l = nullptr;
		}
	}

	//return data from node
	T Data() {return data;}

	//add item
	void add(T);

	//find height
	uc heightRec();

	//return height
	uc Height();

	//print tree in console, not used there
	void print(uc level = 0);

	//rotate
	node<T>* rotateL();

	//rotate
	node<T>* rotateR();

	//if need to rotate
	bool isDisbalanced();

	//tree + tree
	void addTree(node<T>*);

    //del node by item(key)
    void del(node<T>* element);
};

template<typename T>
void node<T>::addTree(node<T>* tree)
{
	if (!tree)
	{
		return;
	}

	if (tree->r)
	{
		this->addTree(tree->r);
	}
	if (tree->l)
	{
		this->addTree(tree->l);
	}
	this->add(tree->Data());
}

template<typename T>
void add(node<T>*& root, T data)
{
	if (root == nullptr)
	{
		root = new node<T>(data);
	}
	else
	{
		root->add(data);
	}
}

template<typename T>
bool node<T>::isDisbalanced()
{
	if (!this)
	{
		return false;
	}

	if (this->r)
	{
		if (this->r->isDisbalanced())
		{
			return true;
		}
	}
	if (this->l)
	{
		if (this->l->isDisbalanced())
		{
			return true;
		}
	}

	uc hr = this->r->Height(), hl = this->l->Height();

	if ((hr - hl > 1) || hr - hl < -1)
	{
		return true;
	}
	return false;
}

template<typename T>
void balance(node<T>*& tree)
{
	tree->heightRec();

	uc hl = tree->l->Height(), hr = tree->r->Height();

	while (tree->isDisbalanced())
	{
		balanceTree(tree);
		
		hl = tree->l->Height();
		hr = tree->r->Height();		
	}
}

template<typename T>
void balanceTree(node<T>*& tree)
{
	if (!tree)
	{
		return;
	}
	if (tree->r)
	{
		balanceTree(tree->r);
	}
	if (tree->l)
	{
		balanceTree(tree->l);
	}
	if (tree->r->Height() - tree->l->Height() < -1)
	{
		tree = tree->rotateR();
	}
	else if ((tree->r->Height() - tree->l->Height()) > 1)
	{
		tree = tree->rotateL();
	}
}

template<typename T>
node<T>* node<T>::rotateR()
{
	if (!this->r && !this->l->l)
	{
		node<T>* temp = this->l->r;
		this->l->r = nullptr;
		temp->l = this->l;
		temp->r = this;
		this->l = nullptr;
		return temp;
	}
	node<T>* temp = this->l;
	this->l = temp->r;
	temp->r = this;
	temp->heightRec();
	return temp;
}

template<typename T>
node<T>* node<T>::rotateL()
{
	if (!this->l && !this->r->r)
	{
		node<T>* temp = this->r->l;
		this->r->l = nullptr;
		temp->r = this->r;
		temp->l = this;
		this->r = nullptr;
		return temp;
	}
	node<T>* temp = this->r;
	this->r = temp->l;
	temp->l = this;
	temp->heightRec();
	return temp;
}

template<typename T>
void node<T>::print(uc level)
{
	if (!this)
	{
		return;
	}

	if (this->r)
	{
		this->r->print(level + 1);
	}

	for (uc i = 0; i < level; i++)
	{
		std::cout << "\t";
	}
	std::cout << this->data <<"\n";
	if (this->l)
	{
		this->l->print(level + 1);
	}
}

template<typename T>
uc node<T>::Height()
{
	if (!this)
	{
		return 0;
	}
	return this->height;
}

template<typename T>
uc node<T>::heightRec()
{
	if (!this)
	{
		return 0;
	}
	if (!this->r && !this->l)
	{
		this->height = 1;
		return 1;
	}

	uc hr = 0, hl = 0;
	if (this->r)
	{
		hr = this->r->heightRec();
	}
	if (this->l)
	{
		hl = this->l->heightRec();
	}

	if (hr > hl)
	{
		this->height = hr + 1;
	}
	else
	{
		this->height = hl + 1;
	}
	return this->height;
}

template<typename T>
void node<T>::add(T data)
{
	for (node<T>* i = this;;)
	{

		if (data > i->Data())
		{
			if (i->r)
			{
				i = i->r;
			}
			else
			{
				i->r = new node<T>(data);
				return;
			}
		}
		else if (data < i->Data())
		{
			if (i->l)
			{
				i = i->l;
			}
			else
			{
				i->l = new node<T>(data);
				return;
			}
		}
		else if (data.Name() == this->Data().Name())
		{
			return;
		}
		else
		{
            return;
        }

	}
}



template<typename T>
void freeTree(node<T>*& tree)
{
	if (!tree)
	{
		return;
	}

	if (tree->l)
	{
		freeTree(tree->l);
	}

	if (tree->r)
	{
		freeTree(tree->r);
	}

	if (!tree->l && !tree->r)
	{
		delete (tree);
		tree = nullptr;
	}
}


template<typename T>
void node<T>::del (node<T>* element)
{
	if (element->data == this->data)

	{   node<T>* i = this;
		bool notFound = true;

		while (i)
		{
			if ((element->data > i->data))
			{
				i = i->r;
			}
			else if ((element->data < i->data))
			{
				i = i->l;
			}
			else if (i && (element->data == i->data))
			{
				notFound = false;
				break;
			}
		}

		if (notFound)
		{
            ShowMessage("Not found");
        	return;
		}
    }

	node<T>* i = this;
	bool right= false;

	while (i)
	{
		if (i->r)
		{
			if (i->r->data == element->data)
			{
				right = true;
				break;
			}
		}

		if (i->l)
		{
			if (i->l->data == element->data)
			{
				  break;
			}
		}

		if (element->data > i->data)
		{
		i = i->r;
		continue;
		}
		else if (element->data < i->data)
		{
		i = i->l;
		continue;
		}
	}

	node<T>* temp;

	if (right)
	{
		temp = i->r;
		i->r = nullptr;
	}
	else
	{
		temp = i->l;
        i->l = nullptr;
	}

	this->addTree(temp->r);
	this->addTree(temp->l);

    delete(temp);
}


template<typename T>
void del(node<T>*& root, node<T>* element)
{
	if (root->Data() == element->Data())
	{
		node<T>* temp = root;
		root->r->addTree(root->l);
		root = root->r;

		temp->r = nullptr;
        temp->l = nullptr;
		delete temp;
		return;
	}
    root->del(element);
}
