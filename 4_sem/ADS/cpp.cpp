#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

vector<vector<pair<int, int>>> g;
vector<ull> s1, s2, c;
vector<int> v;

void d1(int i)
{
    v[i] = 1;
    ull to;
    ull w;
    for (int j = 0; j < g[i].size(); j++)
    {
        to = g[i][j].first;
        w = g[i][j].second;

        if (v[to])
        {
            continue;
        }
        d1(to);
        s1[i] += s1[to] + c[to] * w;
        c[i] += c[to];
    }
    c[i]++;
}

int n;

void d2(int i)
{
    if (i == 0)
    {
        s2[i] = s1[i];
    }
    v[i] = 1;
    ull to, w;
    for (int j = 0; j < g[i].size(); j++)
    {
        to = g[i][j].first;
        w = g[i][j].second;

        if (v[to])
        {
            continue;
        }

        s2[to] = s1[to] + s2[i] - s1[to] - c[to] * w + w * (n - c[to]);
        d2(to);
    }
}

int main()
{
    int i, j, w;

    cin >> n;
    g.resize(n);
    v.resize(n);
    s1.resize(n);
    s2.resize(n);
    c.resize(n);

    for(int _ = 0; _ < n - 1; _++)
    {
        cin >> i >> j >> w;
        i--;
        j--;

        g[i].push_back({j, w});
        g[j].push_back({i, w});
    }

    d1(0);
    v.clear();
    v.resize(n);
    d2(0);
    ull ans = 0;

    for (i = 0; i < n; i++)
    {
        ans += s2[i];
    }

    cout << ans;
}