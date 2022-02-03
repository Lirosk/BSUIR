#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main()
{
    ull n;
    cin >> n;
    n %= 10;

    if (n)
    {
        cout << n;
    }
    else
    {
        cout << "NO";
    }
}
