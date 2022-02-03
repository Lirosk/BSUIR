#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uc;

typedef struct node
{
	struct node* r;
	struct node* l;
	int data;
	uc height;
} node;


void freeTree(node**); //memory cleaning
void add(node**, int); //adding node
uc height(node*); //height of tree
uc check(char*); //checking input
void printTree(node*, int); //printing the tree to the console
int summOfLongestL(node*, const uc); //sum of longest sub-tree, left sub-tree is 1st checked
int summOfLongestR(node*, const uc); //sum of longest sub-tree, right sub-tree is 1st checked

/*
5.2 (20). Пользователь вводит с клавиатуры целые числа (ввод
прекращается, когда будет введен ‘0’). Построить бинарное дерево
поиска, повторяющиеся значения в дерево не добавлять.
Разработать функцию, возвращающую сумму значений узлов самой
длинной ветви дерева. 
*/

int main()
{
	node* tree = NULL;

	//entering and checking numbers
	puts("Enter numbers, 9 symbols max ('0' to stop):\n\n");
	{
		char buf[256];
		int temp = 1;

		while (1)
		{
			if (!fgets(buf, 256, stdin) || !check(buf))
			{
				continue;
			}

			temp = atoi(buf);

			if (temp)
			{
				add(&tree, temp);
			}
			else
			{
				break;
			}
		} 
	}

	puts("\n");
	printTree(tree, 0);
	puts("\n");

	uc h = height(tree);

	int sumL = sumOfLongestL(tree, h), sumR = sumOfLongestR(tree, h);

	if (((sumL != 0) ^ (sumR != 0)) || sumL == sumR)
	{
		if (sumL)
		{
			printf("height: %d\nsum of longest sub-tree: %d\n", h, sumL);
		}
		else
		{
			printf("height: %d\nsum of longest sub-tree: %d\n", h, sumR);
		}
	}
	else
	{
		printf("height: %d\nthere are 2 longest sub-trees relative to root\nsums: %d and %d (always left-1st and right-1st respectively)\n\n\n", h, sumL, sumR);
	}

	freeTree(&tree);
	return 0;
}


//sum of longest sub-tree, right sub-tree is 1st checked
int sumOfLongestR(node* tree, const uc height)
{
	if (!tree)
	{
		return 0;
	}

	int sumL = 0, sumR = 0;
	if (tree->height != height)
	{
		if (!tree->l && !tree->r)
		{
			return 0;
		}

		if (tree->r)
		{
			sumR = sumOfLongestR(tree->r, height);
		}
		if (tree->l)
		{
			sumL = sumOfLongestR(tree->l, height);
		}

		if (sumR)
		{
			return tree->data + sumR;
		}
		if (sumL)
		{
			return tree->data + sumL;
		}

		return 0;
	}

	return tree->data;
}


//sum of longest sub-tree, left sub-tree is 1st checked
int sumOfLongestL(node* tree, const uc height)
{
	if (!tree)
	{
		return 0;
	}

	int sumL = 0 , sumR = 0;
	if (tree->height != height)
	{
		if (!tree->l && !tree->r)
		{
			return 0;
		}

		if (tree->l)
		{
			sumL = sumOfLongestL(tree->l, height);
		}
		if (tree->r)
		{
			sumR = sumOfLongestL(tree->r, height);
		}

		if (sumL)
		{
			return tree->data + sumL;
		}
		if (sumR)
		{
			return tree->data + sumR;
		}

		return 0;
	}

	return tree->data;
}


//height of tree
uc height(node* tree)
{
	if (!tree)
	{
		return 0;
	}
	if (!tree->l && !tree->r)
	{
		return 1;
	}

	uc hl = 0, hr = 0;

	if (tree->l)
	{
		hl = height(tree->l);
	}

	if (tree->r)
	{
		hr = height(tree->r);
	}

	if (hl > hr)
	{
		return hl + 1;
	}
	return hr + 1;
}


//printing the tree to the console
void printTree(node* tree, int level)
{
	if (tree)
	{
		if (tree->r)
		{
			printTree(tree->r, level + 1);
		}

		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("%d\n", tree->data);

		if (tree->l)
		{
			printTree(tree->l, level + 1);
		}
	}
}


//checking input
uc check(char* str)
{
	if (strlen(str) > 10)
	{
		return 0;
	}

	char* i = str;

	if ((*i) == '-')
	{
		i++;
	}

	for (; (*i) && (*i) != '\n'; i++)
	{
		if ((*i) < '0' || (*i) > '9')
		{
			return 0;
		}
	}

	return 1;
}


//adding node
void add(node** tree, int data)
{
	if (!(*tree))
	{
		(*tree) = (node* )malloc(sizeof(node));
		(*tree)->data = data;
		(*tree)->l = NULL;
		(*tree)->r = NULL;
		(*tree)->height = 1;
		return;
	}

	node* temp = (node*)malloc(sizeof(node));
	temp->data = data;
	temp->l = NULL;
	temp->r = NULL;	
	temp->height = 1;

	for (node* i = (*tree);;)
	{
		if (data > i->data)
		{
			if (i->r)
			{
				i = i->r;
				temp->height++;
			}
			else
			{
				i->r = temp;
				temp->height++;
				return;
			}
		}
		else if (data < i->data)
		{
			if (i->l)
			{
				i = i->l;
				temp->height++;
			}
			else
			{
				i->l = temp;
				temp->height++;
				return;
			}
		}
		else
		{
			free(temp);
			return;
		}
	}
}


//memory cleaning
void freeTree(node** tree)
{
	if (!(*tree))
	{
		return;
	}

	if ((*tree)->l)
	{
		freeTree(&(*tree)->l);
	}

	if ((*tree)->r)
	{
		freeTree(&(*tree)->r);
	}

	if (!(*tree)->l && !(*tree)->r)
	{
		free((*tree));
		(*tree) = NULL;
	}
}