#include <stdio.h>
#include <string.h>
#include <math.h>

void Input(double* a, char* name)
{
    printf("Enter %s: ", name);
    char temp[11];
    scanf("%s", temp);

    int len = strlen(temp);

    if (len > 12)
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

            *a *= pow(10,len - pointLocation)*100;
            for (int i = 0; i < len - pointLocation; i++)
            {
                *a/=10;
                *a = round(*a);
            }

            *a/=100;
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


/*
Составить программу, которая преобразует введенное с клавиатуры
дробное число в денежный формат. Например, число 12,348 должно
быть преобразовано в 12 руб. 35 коп.
*/

int main(void)
{
    double num = 0;

    //while(num)
    {
        Input(&num,"num");
    }
    printf("num = %f",num);

    printf("\n\n%d roubles and %d pennies\n\n", (int)num,((int)round(num*100) - ((int)num)*100));

    return 0;
}
