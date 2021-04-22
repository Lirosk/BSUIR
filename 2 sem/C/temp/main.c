#include <stdio.h>

void plus (double* sum, double a)
{
    *sum += a;
}

int main()
{
    printf("Hello World!\n");

    double sum = 0;

    plus(&sum, 5);

    printf("sum = %f\n",sum);

    return 0;
}
