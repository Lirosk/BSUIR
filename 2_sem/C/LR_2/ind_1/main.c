#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void Input(int* a, char* name);
void ShowSquare(int r);
void ShowSquareOfSector(int r, void(*Input)(int*,char*));
void ShowLengthLine(int r);
void ShowSquareSide(int r);
void ShowConeSize(int r);
void ShowVersion();



int main()
{
    printf("Hello World!\n\n");
    int r = 0;

    for (;;)
    {
        system("clear");
        int exit = 0;

        printf("1. Enter circle radius (radius = %d).\n2. Show circle's square.\n3. Show circle's sector square.\n4. Show line's length.\n5. Show square's side (circle in square).\n6. Show size if conus (foundatoin - circle, height - his radius).\n7. Show version.\n8. Exit.\n\n",r);

        switch (getchar())
        {
            case '1':
            {
                Input(&r,"radius");
                break;
            }
            case '2':
            {
                ShowSquare(r);
                break;
            }
            case '3':
            {
                ShowSquareOfSector(r,Input);
                break;
            }
            case '4':
            {
                ShowLengthLine(r);
                break;
            }
            case '5':
            {
                ShowSquareSide(r);
                break;
            }
            case '6':
            {
                ShowConeSize(r);
                break;
            }
            case '7':
            {
                ShowVersion();
                break;
            }
            case '8':
            {
                exit = 1;
                break;
            }
            default:
            {
                printf("\n\nIncorrect input...");
                break;
            }
        }

        getchar();
        getchar();
        getchar();
        //system("pause");

        if (exit)
        {
            break;
        }
    }
}






void Input(int* a, char* name)
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
    for (int i = 0; i < len;i++)
    {
        if (((int)temp[i] < 48) || ((int)temp[i] > 57))
        {
            printf("\n\nIncorrect input.\n\n\n");
            return;
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
                return;
            }
        }
    }

    *a = 0;
    for (int i = len - 1; i > -1;i--)
    {
        *a += ((temp[i]) - '0')*pow(10,len - i - 1);
    }
}

void ShowSquare(int r)
{
    printf("\n\nSquare of circle: %f",3.14159*r*r);
}

void ShowSquareOfSector(int r, void(*Input)(int*,char*))
{
    int angle = 0;
    Input(&angle, "angle (degrees)");

    printf("\n\nSquare of circle's sector: %f",3.14159*r*r*angle/360);
}

void ShowLengthLine(int r)
{
    printf("\n\nLength of circle's line: %f",3.14159*r*2);
}

void ShowSquareSide(int r)
{
    printf("\n\nLenth of square's side: %d",2*r);
}

void ShowConeSize(int r)
{
    printf("\n\nSize of conus: %f",3.14159*r*r*r/3);
}

void ShowVersion()
{
    printf("\n\nVersion: 1.0");
}
