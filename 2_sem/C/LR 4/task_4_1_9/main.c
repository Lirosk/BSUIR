#include <stdlib.h>
#include <string.h>
//#include <malloc.h>
#include <stdio.h>
#include <math.h>

void RemoveDouble (double* array, int order, int* len)
{
    for (int i = order; i + 1 < *len; i++)
    {
        array[i] = array[i + 1];
    }

    *len -= 1;
    array[*len] = '\0';
}

void RemoveInt (int* array, int order, int* len)
{
    for (int i = order; i + 1 < *len; i++)
    {
        array[i] = array[i + 1];
    }

    *len -= 1;
    array[*len] = '\0';
}

void RemoveChar (char* array, int order, int len)
{
    for (int i = order; i + 1 < len; i++)
    {
        array[i] = array[i + 1];
    }

    //*len -= 1;
    array[len - 1] = '\0';
}



int Check(char* str, int len)
{
    if (len > 100)
    {
        return 1;
    }

    for (int i = 0; i < len; i ++)
    {
        //printf("\n%c",str[i]);
        if ((str[i] == 42) || (str[i] == 43) || (str[i] == 45) || (str[i] == 47))
        {
            if ((i == 0) || (i == len - 1))
            {
                return 2;
            }

            switch (str[i-1])
            {
                case (42):
                {

                }
                case (43):
                {

                }
                case (45):
                {

                }
                case (47):
                {
                    return 3;
                    break;
                }
            }
        }
        else if ((str[i] < 48) || (str[i] > 57))
        {
            //printf("\ni = %d\n",i);
            return 4;
        }
    }

    return 0;
}
// (int)'+' = 43
// (int)'-' = 45
// (int)'*' = 42
// (int)'/' = 47
// 42, 43, 45, 47


/*
Строка содержит арифмитическое выражение, состоящее из целых
чисел и знаков операций: +, -, *, / (без скобок). Проверить
корректность выражения (в смысле последовательности чисел и
знаков операций). В случае корректности вычислить значение
выражения с учетом приоритетов операций.
*/

int main() //Ctrl + I
{
    char* str = (char* )malloc(100 * sizeof(char));
    if (!str)
    {
        return 1;
    }

    int len = 0;

    int* numOfMultOrDiv = malloc(sizeof(int));
    if (!numOfMultOrDiv)
    {
        return 1;
    }
    *numOfMultOrDiv = 0;

    for (;;)
    {
        system("clear");
        printf ("Enter your arithmetic expression(without spaces)(max len == 100):\n");
        //scanf("%s",str);
        fgets(str, 100, stdin);

        len = strlen(str) - 1;
        //printf("\n%d\n",strlen(str));
        str[len + 1] = '\0';
        str[len] = '\0';

        printf("\nlen = %d\n",len);

        if (!Check(str,len))
        {
            printf("\n%s\n",str);
            break;
        }

        printf("\nCheck = %d\n", Check(str,len));
        printf("\n\nInvalid input\n\n");
        getchar();
        getchar();
        //system("clear");
    }

    int* numOfOperations = malloc(sizeof (int));
    if (!numOfOperations)
    {
        return 1;
    }
    *numOfOperations = 0;

    //get number operations
    for(int i = 1; i < len-1; i++)
    {
        switch (str[i])
        {
            case (42):
            {

            }
            case (43):
            {

            }
            case (45):
            {

            }
            case (47):
            {
                *numOfOperations += 1;
                if ((str[i] == '*') || (str[i] == '/'))
                {
                    *numOfMultOrDiv += 1;
                }
                break;
            }
        }
    }


    char* operations = (char* )malloc(((*numOfOperations) + 1) * sizeof(char));
    if (!operations)
    {
        return 1;
    }

    operations[*numOfOperations] = '\0';


    //int* numOfMultOrDiv = malloc(sizeof(int));

    //get operations
    for(int i = 0, order = 0; i < len; i++)
    {
        switch(str[i])
        {
            case (42):
            {

            }
            case (43):
            {

            }
            case (45):
            {

            }
            case (47):
            {
                operations[order] = str[i];
                //*numOfMultOrDiv += 1;
                order += 1;
                break;
            }
        }
    }


    //int* numbers = (int* )malloc(((*numOfOperations) + 30) * sizeof(int));
    double numbers[(*numOfOperations) + 1];

    /*
    if (!numbers)
    {
        return 1;
    }
    */

    //get numbers
    for(int i = 1, startOfNum = 0, order = 0; i <= len; i++)
    {
        //printf("\ni = %d\norder = %d\n",i,order);
        if ((str[i] == '*') || (str[i] == '+') || (str[i] == '/') || (str[i] == '-') || (i == len))
        {
            numbers[order] = 0;
            for (int j = startOfNum; j < i; j++)
            {
                //printf("\ncalculating\n");
                numbers[order] += (str[j] - '0')*pow(10, i - 1 - j);
            }

            startOfNum = i + 1;
            order += 1;
        }
    }

    double result = 0;

    /*  THERE YOU ARE   */


    //// 6  8  9  4  9  1  *
    //// 0  1  2  3  4  5  6


    //getting the result

    //len = *numOfOperations + 1;

    /*
    printf("\n\narithmetic expression: %s\n", str);
    printf("\noperations: %s\n\nnumbers: ", operations);
    for (unsigned short i = 0; i < sizeof(numbers)/sizeof(double); i++)
    {
        printf("%d ", (int)numbers[i]);
    }
    printf("\n\n\n");
    */


    *numOfOperations += 1;

    for (int i = 0, j = 0; j < *numOfMultOrDiv; i++)
    {
        if (operations[i] == '*')
        {
            numbers[i] *= numbers[i+1];
            RemoveDouble(numbers, i + 1, numOfOperations);
            RemoveChar(operations, i, (short)sizeof(operations)/sizeof(char));
            i -= 1;
            j += 1;
        }
        else if (operations[i] == '/')
        {
            numbers[i] /= numbers[i+1];
            RemoveDouble(numbers, i + 1, numOfOperations);
            RemoveChar(operations, i, (short)sizeof(operations)/sizeof(char));
            i -= 1;
            j += 1;
        }
    }


    for (int i = 0; *numOfOperations > 1; i++)
    {
        if (operations[i] == '+')
        {
            numbers[i] += numbers[i+1];
            RemoveDouble(numbers, i + 1, numOfOperations);
            RemoveChar(operations, i, (short)sizeof(operations)/sizeof(char));
            i -= 1;
        }
        else if (operations[i] == '-')
        {
            numbers[i] -= numbers[i+1];
            RemoveDouble(numbers, i + 1, numOfOperations);
            RemoveChar(operations, i, (short)sizeof(operations)/sizeof(char));
            i -= 1;
        }
    }

    /*
    printf("\n\narithmetic expression: %s\n", str);
    printf("\noperations: %s\n\nnumbers: ", operations);
    for (unsigned short i = 0; i < sizeof(numbers)/sizeof(double); i++)
    {
        printf("%f ", numbers[i]);
    }
    */

    printf("\n\n\nAnswer: %f",numbers[0]);

    free (numOfMultOrDiv);
    free (numbers);
    free (operations);
    free (numOfOperations);
    free (str);
    return 0;
}
