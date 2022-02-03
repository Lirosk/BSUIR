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
        if (k != r[_i][k].first)
        {
            pull[0].push_back({_i, k, r[_i][k].second});
        }
    }

    int b;
    list<line> to_proccess;

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
                    if (k != r[j][k].first)
                    {
                        to_proccess.push_back({j, r[j][k].first, r[j][k].second});
                    }
                }

                for (auto next: to_proccess)
                {
                    if (next.y != i && next.y != _i)
                    {
                        pull[1].push_back(next);
                    }
                }

                to_proccess.clear();
            }
        }

        pull[0] = pull[1];
        pull[1].clear();
    }

    cout << d[_j];
}
