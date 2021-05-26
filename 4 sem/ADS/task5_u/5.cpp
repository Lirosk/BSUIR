#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::list;



int main()
{
    int n;
    int m;

    cin >> n;
    cin >> m;

    int i, j, k;

    int** r = new int*[n];
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

        i--;
        j--;

        if (!r[i][j] || k < r[i][j])
        {
            r[i][j] = k;
            r[j][i] = k;
        }
    }

    int _i, _j;
    cin >> _i >> _j;
    _i--;
    _j--;

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

    
}