#include <stdio.h>
#include <string.h>
#include <math.h>

void Input(double* a, char* name)
{
    printf("Enter %s: ", name);
    char temp[11];
    scanf("%s", temp);

    int len = strlen(temp);

    if (len > 10)
    {
        printf("\n\nIncorrect input (very big number).\n\n\n");
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
        else if (numOfPoints == 0)
        {
            int forCheck[11] = {2,   1,4,7,   4,8,3,   6,4,7};
            for (int i = 0; i < len; i++)
            {
                if (temp[i] - '0' > forCheck[i])
                {
                    printf("\n\nIncorrect input.\n\n\n");
                    return;
                }
            }
        }

        //printf("\nNum of points = %d, point at %d\n",numOfPoints, pointLocation);
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

int main(void)
{
    double num = 0;
    Input(&num,"num");

    printf("num = %f",num);

    printf("\n\n%d roubles and %d pennies", (int)num,((int)round(num*100) - ((int)num)*100));

    return 0;
}
