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
const int mod = 1e9 + 7;

int main()
{
    int m, u, v, l, i, j;
    cin >> n >> m;
    cin >> u >> v >> l;
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

        i--;
        j--;

        r[i][j]++;
        r[j][i]++;
    }

    pow(r, l);
    cout << (r[u][v] % mod);

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