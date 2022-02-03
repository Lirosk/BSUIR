#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    int q;
    cin >> s >> q;
    int len = s.length();

    int l;
    int r;

    int* inv = new int[len];

    for (int i = 0; i < len; i++)
    {
        inv[i] = 0;
    }

    for (int i = 0; i < q; i++)
    {
        cin >> l >> r;

        if (l > r)
        {
            swap(l, r);
        }

        l--;

        inv[l]++;
        inv[r]--;
    }

    int b;
    for (int i = 0; i < len; i++)
    {
        if (i > 0)
        {
            inv[i] += inv[i-1];
        }
        if (inv[i] % 2 == 1)
        {
            if (isupper(s[i]))
            {
                s[i] = tolower(s[i]);
            }
            else
            {
                s[i] = toupper(s[i]);
            }
        }
    }

    cout << s;
}