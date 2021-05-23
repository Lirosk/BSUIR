#include <stdio.h>

void pow(int**&, int);
void mul(int**&, int**&);
void set_zero(int**, bool);
void copy(int**, int **);


int n;
int** buf_mul;
int** buf_pow;
int m = 1e9 + 7;

void pr(int** a)
{
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int m, u, v, l, i, j;
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &u, &v, &l);
    u--;
    v--;

    int** r = new int*[n];
    buf_mul = new int*[n];
    buf_pow = new int*[n];
    for (i = 0; i < n; i++)
    {
        r[i] = new int[n];
        buf_mul[i] = new int[n];
        buf_pow[i] = new int[n];
        for (j = 0; j < n; j++)
        {
            r[i][j] = 0;
        }
    }

    for (int _ = 0; _ < m; _++)
    {
        scanf("%d %d", &i, &j);

        i--;
        j--;

        r[i][j] = 1;
        r[j][i] = 1;
    }

    pr(r);
    pow(r, l);
    printf("%d", r[u][v]);
    pr(r);

    for (i = 0; i < n; i++)
    {
        delete[] buf_pow[i];
        delete[] buf_mul[i];
        delete[] r[i];
    }
    delete[] r;
    delete[] buf_pow;
    delete[] buf_mul;
}

void pow(int**& a, int p)
{
    set_zero(buf_pow, true);

    while (p)
    {
        if (p % 2)
        {
            mul(buf_pow, a);
            p--;
        }
        else
        {
            mul(a, a);
            p /= 2;
        }
    }

    copy(a, buf_pow);
}

void mul(int**& a, int**& b)
{
    set_zero(buf_mul,  false);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            for (int k = 0; k < n; k++)
            {   
                buf_mul[i][j] += ((a[i][k] % m) * (b[k][j] % m)) % m;
                buf_mul[i][j] %= m;
            }
        }
    }
    copy(a, buf_mul);
}

void set_zero(int** m, bool diag)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (i == j && diag)
            {
                m[i][j] = 1;
                continue;
            }
            m[i][j] = 0;
        }
    }
}

void copy(int** a, int** b)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j ++)
        {
            a[i][j] = b[i][j];
        }
    }
}
/*
4 4
1 4 12
1 2
2 4
1 3
3 4

*/