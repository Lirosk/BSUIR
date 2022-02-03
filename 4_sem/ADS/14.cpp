#include <iostream>

using std::cin;
using std::cout;

typedef unsigned long long ull;

void pow(ull**&, ull);
void mul(ull**&, ull**&);
void set_zero(ull**, bool);
void copy(ull**, ull **);


int n;
ull** buf_mul;
ull** buf_pow;
int mod = 1e9 + 7;

// void pr(ull** a)
// {
//     cout << "\n";
//     // printf("\n");
//     for(int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cout << a[i][j];
//             // printf("%d ", a[i][j]);
//         }
//         cout << "\n";
//         // printf("\n");
//     }
//     cout << "\n";
//     // printf("\n");
// }

int main()
{
    int m, u, v, l, i, j;
    cin >> n >> m;
    // scanf("%d %d", &n, &m);
    cin >> u >> v >> l;
    // scanf("%d %d %d", &u, &v, &l);
    u--;
    v--;

    ull** r = new ull*[n];
    buf_mul = new ull*[n];
    buf_pow = new ull*[n];
    for (i = 0; i < n; i++)
    {
        r[i] = new ull[n];
        buf_mul[i] = new ull[n];
        buf_pow[i] = new ull[n];
        for (j = 0; j < n; j++)
        {
            r[i][j] = 0;
        }
    }

    for (int _ = 0; _ < m; _++)
    {
        cin >> i >> j;
        // scanf("%d %d", &i, &j);

        i--;
        j--;

        r[i][j] = 1;
        r[j][i] = 1;

        if (i == j)
        {
            r[i][j] = 2;
            r[j][i] = 2;
        }
    }

    pow(r, l);
    cout << (r[u][v] % mod);
    // printf("%d", r[u][v]);

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

void pow(ull**& a, ull p)
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

void mul(ull**& a, ull**& b)
{
    set_zero(buf_mul,  false);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            for (int k = 0; k < n; k++)
            {   
                buf_mul[i][j] = (buf_mul[i][j] + ((a[i][k]) * (b[k][j])) % mod) % mod;
            }
        }
    }
    copy(a, buf_mul);
}

void set_zero(ull** m, bool diag)
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

void copy(ull** a, ull** b)
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