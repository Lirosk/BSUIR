#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

int n;
int m;
vector<vector<int>> r;

vector<vector<int>>* get_connected(int* i)
{
    vector<vector<int>>* res = new vector<vector<int>>();
    for (int j = 0; j < n; j++)
    {
        if (*i != j && r.at(*i).at(j))
        {
            res->push_back(vector<int>{*i, j});
        }
    }
    return res;
}

int main()
{
    cin >> n >> m;
    r = vector<vector<int>>(n, vector<int>(n, 0));
    

    int i, j, k;

    for (int _ = 0; _ < m; _++)
    {
        cin >> i >> j >> k;

        i -= 1;
        j -= 1;

        if (!r.at(i).at(j) ||r.at(i).at(j) > k)
        {
            r.at(i).at(j) = k;
            r.at(i).at(j) = k;
        }
    }

    int _i, _j;
    cin >> _i >> _j;
    _i -= 1;
    _j -= 1;

    if (_i == _j)
    {
        cout << 0;
        exit(0);
    }

    vector<vector<vector<int>>> pull{*get_connected(&_i), vector<vector<int>>()};

    // bool* w = new bool(n);
    int* d = new int(n);
    for (i = 0; i < n; i++)
    {
        // w[i] = false;
        d[i] = 0;
    }
    
    int b;
    while (!pull.at(0).empty())
    {
        for (auto road: pull.at(0))
        {
            i = road.at(0);
            j = road.at(1);

            // w[i] = true;

            b = r[i][j];

            // if (w[j])
            // {
            //     b += d[i];
            // }

            if ((!d[j] || d[j] > b) && j != _i)
            {
                d[j] = b;
                auto to_proccess = get_connected(&j);
                for (auto next: *to_proccess)
                {
                    if (next.at(1) != i && next.at(1) != _i)
                    {
                        pull.at(1).push_back(next);
                    }
                }
                to_proccess->clear();
            }
        }

        pull.at(0).clear();
        std::swap(pull.at(0), pull.at(1));
    }

    pull.clear();
    r.clear();
    cout << d[_j];
}
/*
6
7
1 3 5
4 2 2
3 6 8
1 5 1
4 5 1
3 4 10
2 3 7
3
5
*/