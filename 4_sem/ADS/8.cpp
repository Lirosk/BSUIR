#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int l = s.length();
    
    bool pol = true;
    for (int i = 1; i < l; i++)
    {
        if (s[0] != s[i])
        {
            pol = false;
            break;
        }
    }

    if (pol)
    {
        cout << -1;
        return 0;
    }

    pol = true;
    for (int i = 0; i < l/2; i++)
    {
        if (s[i] != s[l-1-i])
        {
            pol = false;
            break;
        }
    }

    if (pol)
    {
        cout << l - 1;
    }
    else
    {
        cout << l;
    }

    return 0;
}