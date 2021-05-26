#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::list;

int n;
int m;
int** r;

typedef struct p
{
    int i;
    int j;

    p(int i_, int j_)
    {
        i = i_;
        j = j_;
    }
} p;

int main()
{
    cin >> n >> m;

    int i, j, k;

    r = new int*[n];
    for (i = 0; i < n; i++)
    {
        r[i] = new int[n];
        for (j = 0; j < n; j++)
        {
            r[i][j] = 0;
        }
    }    

    for (int _ = 0; _ < m; _++)
    {
        cin >> i >> j >> k;

        i -= 1;
        j -= 1;

        if (!r[i][j] ||r[i][j] > k)
        {
            r[i][j] = k;
            r[j][i] = k;
        }
    }

    int _i, _j;
    cin >> _i >> _j;
    _i -= 1;
    _j -= 1;

    if (_i == _j)
    {
        for (i = 0; i < n; i++)
        {
            delete[] r[i];
        }
        delete[] r;
        cout << 0;
        exit(0);
    }

    list<p> pull[2];
    for (k = 0; k < n; k++)
    {
        if (_i != k && r[_i][k])
        {
            pull[0].push_back(p(_i, k));
        }
    }    

    int* d = new int(n);
    for (i = 0; i < n; i++)
    {
        d[i] = 0;
    }
    
    int b;
    list<p> to_proccess;

    while (!pull[0].empty())
    {
        for (auto road: pull[0])
        {
            i = road.i;
            j = road.j;

            b = d[i] + r[i][j];

            if ((!d[j] || d[j] > b) && j != _i)
            {
                d[j] = b;
                to_proccess = list<p>();
                for (k = 0; k < n; k++)
                {
                    if (j != k && r[j][k])
                    {
                        to_proccess.push_back(p(j, k));
                    }
                }

                for (auto next: to_proccess)
                {
                    if (next.j != i && next.j != _i)
                    {
                        pull[1].push_back({next.i, next.j});
                    }
                }
                to_proccess.clear();
            }
        }

        pull[0] = pull[1];
        pull[1].clear();
    }

    pull[0].clear();
    pull[1].clear();
    
    for (i = 0; i < n; i++)
    {
        delete[] r[i];
    }
    delete[] r;

    cout << d[_j];    
}
