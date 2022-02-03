#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> r;

typedef struct line
{
    int x;
    int y;
    int w;
} line;

int main()
{
    int n, m;
    cin >> n >> m;

    r.resize(n);
    
    int i, j, k;

    int d[n];
    for(i = 0; i < n; i++)
    {
        d[i] = 0;
    }

    for (int _ = 0; _ < m; _++)
    {
        cin >> i >> j >> k;

        i--;
        j--;

        if (i == j)
        {
            continue;
        }

        r[i].push_back({j, k});
        r[j].push_back({i, k});
    }

    int _i, _j;
    cin >> _i >> _j;
    _i--;
    _j--;

    if (_i == _j)
    {
        cout << 0;
        exit(0);
    }

    list<line> pull[2];
    for (k = 0; k < r[_i].size(); k++)
    {
        pull[0].push_back({_i, r[_i][k].first, r[_i][k].second});
    }

    int b;

    while(!pull[0].empty())
    {
        for (auto road: pull[0])
        {
            i = road.x;
            j = road.y;

            b = d[i] + road.w;

            if ((!d[j] || d[j] > b) && j != _i)
            {
                d[j] = b;
                
                for (k = 0; k < r[j].size(); k++)
                {
                    if (i != r[j][k].first && r[j][k].first != _i)
                    {
                        pull[1].push_back({j, r[j][k].first, r[j][k].second});
                    }
                }
            }
        }

        pull[0] = pull[1];
        pull[1].clear();
    }

    cout << d[_j];
}
/*
5
7
1 2 2
1 4 1
2 4 0
2 5 4
4 5 4
2 3 3
3 5 0
1
5

5
7
1 2 2
1 4 1
2 4 0
2 5 4
4 5 4
2 3 3
3 5 1
1
5

5
4
4 3 1
1 2 1
5 1 1
3 2 0
4
5

3
3
1 2 3
2 3 2
1 2 1
1 
3
*/
