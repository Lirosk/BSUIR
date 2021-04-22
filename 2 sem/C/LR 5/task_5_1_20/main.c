#include <stdio.h>
#include <malloc.h>
#include

typedef unsigned short ush;

typedef struct binTree
{
    char dig;
    struct binTree* pRight;
    struct binTree* pLeft;
} binTree;

typedef struct string
{
    char a;
    struct string* pNext;
} string;

/*
5.2 (20). Пользователь вводит с клавиатуры целые числа (ввод
прекращается, когда будет введен ‘0’). Построить бинарное дерево
поиска, повторяющиеся значения в дерево не добавлять.
Разработать функцию, возвращающую сумму значений узлов самой
длинной ветви дерева.
*/
int main()
{
    binTree* Tree = NULL;
    string* str = NULL;

    printf("Enter your string:\n");
    int len = 0;
    {
        string* p = &*str;

        for (char a = '\0';;)
        {
            a = getch();

            if ((a < '1') || (a > '9'))
            {
                break;
            }
            p = (string* )malloc(sizeof(string));
            p->a = a;
            p = p->pNext;
            p = NULL;
            len ++;
        }
    }

    return 0;
}
