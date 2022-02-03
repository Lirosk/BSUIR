#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>


/*
typedef int bool;
//#define bool int
#define true 1
#define false 0
*/
#define N 100


void RemoveChar (char* array, int order, int len)
{
    for (int i = order; i + 1 < len; i++)
    {
        array[i] = array[i + 1];
    }

    //*len -= 1;
    array[len - 1] = '\0';
}

void RemoveSpaces(char* str, int len, void (*RemoveCharAndLen)(char*, int, int))
{
    for (int i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            RemoveCharAndLen(str, i, len);
            i -= 1;
        }
    }
}

int IsEqual(char* str1, char* str2)
{
    unsigned short len = strlen(str1), len2 = strlen(str2);
    //bool notFound = false;
    int sameChars = 0, sameFound = 0;

    if (len != len2)
    {
        return 1;
    }

    //printf("len = %d\n", len);

    for (int i = 0; i < len; i++)
    {
        sameChars = 0;
        sameFound = 0;

        for (int j = 0; j < len; j++)
        {
            if (tolower(str1[i]) == tolower(str1[j]))
            {
                sameChars += 1;
            }
        }

        for (int j = 0; j < len; j ++)
        {
            if (tolower(str1[i]) == tolower(str2[j]))
            {
                sameFound += 1;
            }
        }

        //printf("\n%c(str1[%d])\nsameChars = %d\nsameFound = %d\n\n\n", str1[i], i, sameChars, sameFound);

        if (sameChars != sameFound)
        {
            return 2;
        }
    }

    return 0;
}


int main()
{
    printf("Hello World!\n%d\n", IsEqual("pteranodon","pteranonod"));

    char buffer[N];

    FILE *file;
    file = fopen("D:\\BSUIR\\Tapping\\C\\LR 4\\task_4_2_9\\task_4_2_9\\data.txt","r+");
    if (!file)
    {
        return 1;
    }

    int lines = 0;
    for (;fgets(buffer, N, file) != NULL; lines += 1);

    printf("amount of lines in file - %d\n\n", lines);

    char forCheck[lines][N];

    rewind(file);

    for (unsigned short i = 0 ; i < lines ; i ++)
    {
        fgets(forCheck[i],N,file);
        forCheck[i][strlen(forCheck[i]) - 1] = '\0';

        printf("\n%s", forCheck[i]);
    }
    free(file);

    printf("\n\n\n");

    for (unsigned short i = 0 ; i < lines; i++)
    {
        for (unsigned short j = i + 1; j < lines; j++)
        {
            if (!IsEqual(forCheck[i], forCheck[j]))
            {
                printf("\n%s and %s\n", forCheck[i], forCheck[j]);
            }
        }
    }


    return 0;
}
