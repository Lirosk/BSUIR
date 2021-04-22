#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

long double absf(double num)
{
    if (num < 0)
    {
        return (-num);
    }
    return num;
}

void Input(long double* a, char* name)
{
    int max = 15;
    printf("Enter %s: ", name);
    char temp[max];
    scanf("%s", temp);

    int len = strlen(temp);

    if (len > max + 1)
    {
        printf("\n\nIncorrect input (very long number).\n\n\n");
        return;
    }

    {
        int numOfPoints = 0, pointLocation = 0;

        for (int i = 0; i < len;i++)
        {
            if (((temp[i] == '.') || (temp[i] == ',')))
            {
                numOfPoints += 1;
                pointLocation = i;
            }
            else if (((int)temp[i] < 48) || ((int)temp[i] > 57))
            {
                printf("\n\nIncorrect input.\n\n\n");
                return;
            }
        }

        if (numOfPoints > 1)
        {
            printf("\n\nIncorrect input.\n\n\n");
            return;
        }

        if (numOfPoints == 1)
        {
            for (int i = 0; i < pointLocation; i++)
            {
                *a += (temp[i]-'0')*pow(10, pointLocation - i - 1);
            }
            for(int i = pointLocation + 1; i < len; i++)
            {
                *a += (double)(temp[i]-'0')/pow(10, i - pointLocation);
            }
        }
        else
        {
            for (int i = 0; i < len; i ++)
            {
                *a += (temp[i]-'0')*pow(10,len-i-1);
            }
        }
    }

    return;
}

unsigned long long factorial(int x)
{
    if (x < 1)
    {
        return 1;
    }
    return x*factorial(x-1);
}

int main()
{
    printf("Hello World!\n\n");

    long double epsilon = 0;
    long double x = 0;

    while(!epsilon)
    {
        Input(&epsilon,"epsilon");
    }
    epsilon /= 100;

    while(!x)
    {
        Input(&x,"x");
    }

    int n = 0;
    long double S = 0, F = sin(x);

    printf ("\nsin(x) = %Lf",F);

    for (; absf((F)-(S))/(absf(F)) > epsilon; n+=1,S += (((n-1)%2==0)?(1):(-1))*powf(x,2*n-1)/factorial(2*n-1));

    printf("\n\n\nn = %d\n\n",n);

    return 0;
}
