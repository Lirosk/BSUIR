#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int Input(char name, int condOfWin)
{
    int a = 0;
    printf("Enter %c (>=%d): ", name, condOfWin);
    char temp[11];
    scanf("%s", temp);

    int len = strlen(temp);

    if (len > 10)
    {
        printf("\n\nIncorrect input (very big number).\n\n\n");
        return 0;
    }
    for (int i = 0; i < len;i++)
    {
        if (((int)temp[i] < 48) || ((int)temp[i] > 57))
        {
            printf("\n\nIncorrect input.\n\n\n");
            return 0;
        }
    }

    if (len == 10)
    {
        int forCheck[11] = {2, 1,4,7, 4,8,3, 6,4,7};
        for (int i = 0; i < len;i++)
        {
            if (temp[i] - '0' > forCheck[i])
            {
                printf("\n\nIncorrect input.\n\n\n");
                return 0;
            }
        }
    }

    a = 0;
    for (int i = len - 1; i > -1;i--)
    {
        a += ((temp[i]) - '0')*pow(10,len - i - 1);
    }
    return a;
}

char ForField()
{
    switch(rand()%3)
    {
        case (0):
        {
            return ' ';
            break;
        }
        case (1):
        {
            return 'O';
            break;
        }
        case (2):
        {
            return 'X';
            break;
        }
    }

    return ' ';
}

void Show(char** array, int N, int M)
{
    printf ("\n\n\n");

    for (int i = 0; i < N; i ++)
    {
        printf("|");

        for (int j = 0; j < M; j ++)
        {
            printf(" %c |",array[i][j]);
        }

        printf("\n");

        if (i != N-1)
        {
            for (int k = 0; k < 4*M + 1;k++)
            {
                printf("-");
            }
        }

        printf("\n");
    }
}

int CheckHedgehog (char** array, int xi, int xj, int N, int M, int condOfWin)
{
    int numOfCrosses = 0;

    //north
    if (xi - condOfWin >= 0)
    {
        numOfCrosses = 0;

        for (int i = xi; i > xi - condOfWin; i--)
        {
            if (array[i][xj] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }
    //west
    if (xj - condOfWin >= 0)
    {
        numOfCrosses = 0;

        for (int j = xj; j > xj - condOfWin; j--)
        {
            if (array[xi][j] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }
    //north-west
    if ((xi - condOfWin >= 0) && (xj - condOfWin >= 0))
    {
        numOfCrosses = 0;

        for (int i = xi, j = xj; (i > xi - condOfWin) && (j > xj - condOfWin); i -= 1, j -= 1)
        {
            if (array[i][j] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }
    //south
    if (xi + condOfWin <= N)
    {
        numOfCrosses = 0;

        for (int i = xi; i < xi + condOfWin; i++)
        {
            if (array[i][xj] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }
    //east
    if (xj + condOfWin <= M)
    {
        numOfCrosses = 0;

        for (int j = xj; j < xj + condOfWin; j++)
        {
            if (array[xi][j] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }
    //south-east
    if ((xi + condOfWin <= N) && (xj + condOfWin <= M))
    {
        numOfCrosses = 0;

        for (int i = xi, j = xj; (i < xi + condOfWin) && (j < xj + condOfWin); i+=1, i+=1)
        {
            if (array[i][j] == 'X')
            {
                numOfCrosses += 1;
            }
        }

        if (numOfCrosses == 5)
        {
            return 1;
        }
    }

    return 0;
}

/*
3.2 (16). Крестики-нолики. Двумерный массив размером m×n есть результат
игры в крестики-нолики на этом поле. Проверить, не закончена ли
игра выигрышем «крестиков»? Считается, что «крестики» выиграли,
если на поле найдется по горизонтали, вертикали или диагонали
цепочка, состоящая подряд из 5 крестиков.
*/


int main()
{

    srand(time(0));

    printf("Hello World!\n");
    int M = 0, N = 0;

    int condOfWin = 5;

    while (M < 5)
    {
        M = Input('M', condOfWin);
    }

    printf("\n");

    while (N < 5)
    {
        N = Input('N', condOfWin);
    }

    char** array = (char**)malloc(N*sizeof(char *));
    for(int i = 0; i < N; i++)
    {
        array[i] = (char*)malloc(M*sizeof(char));
    }

    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < M; j ++)
        {
            array[i][j] = ForField();
        }
    }


    Show(array,N,M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j ++)
        {
            if (CheckHedgehog(array, i, j, N, M, condOfWin))
            {
                i = N;
                j = M;
                printf("\n\nCrosses won");
            }
        }
    }

    return 0;
}
