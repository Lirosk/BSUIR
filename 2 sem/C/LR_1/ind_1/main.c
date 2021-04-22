#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int Input(int* a, char name)
{
    printf("Enter %c: ", name);
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

    *a = 0;
    for (int i = len - 1; i > -1;i--)
    {
        *a += ((temp[i]) - '0')*pow(10,len - i - 1);
    }
    return 1;
}

//////////////////////////////////////////////////////////

/*
Цена на молоко. Фермер в начале каждой зимы повышает
отпускную цену на молоко на p%, а каждым летом – снижает на
столько же процентов. Изменится ли цена на молоко и если да, то в
какую сторону и на сколько через n лет?
*/

    int main()
    {
          printf("\nHello World!\n\n");

          unsigned int p = 0;

          {
              int pTemp = 0;

              for (;;)
              {
                  if (Input(&pTemp,'p'))
                  {
                      break;
                  }
              }

              p = pTemp;
          }

          unsigned int n = 0;
        {
              int nTemp = 0;

              for (;;)
              {

                  if (Input(&nTemp,'n'))
                  {
                      break;
                  }
              }

              n = nTemp;
          }

          long double coefficient = pow((1 - (long double)p*p/10000),n);


          if (p == 0)
          {
               printf("\nPrice won't change.");
          }
          else if (coefficient < 1)
          {
               printf("\nDifference between prices will decrease (by %Lf percents)",(1-coefficient)*100);
          }
          else  //Its will never happens
          {
               printf("\nDifference between prices will increase (by %Lf percents)",(1-coefficient)*100);
          }

          printf("\n\npress any key...\n\n\n");
          getchar();

        return 0;
    }
