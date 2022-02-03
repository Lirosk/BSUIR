#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

typedef struct v
{
    int to, w;
} v;

int mod = 1e7 + 7;
unsigned long long res = 0;
int n;

int get_num(int i, int from, vector<v>* g)
{
    int ret = 1;
    for (int j = 0; j < g[i].size(); j++)
    {
        int to = g[i][j].to;
        if (g[i][j].to != from)
        {
            ret += get_num(g[i][j].to, i, g);
        }
    }
    return ret;
}

int main()
{
    int i, j, w;

    cin >> n;

    vector<v> g[n];

    for (int _ = 0; _ < n - 1; _++)
    {
        cin >> i >> j >> w;
        i--;
        j--;
        g[i].push_back({j, w});
        g[j].push_back({i, w});
    }

    int l, r;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < g[i].size(); j++)
        {
            l = get_num(g[i][j].to, i, g);
            r = get_num(i, g[i][j].to, g);
            w = g[i][j].w;
            res = (res + w * l * r) % mod;
        }
    }

    res %= mod;
    cout << res;
}

/*
5
1 2 1
2 3 2
2 4 3
2 5 4

*/
