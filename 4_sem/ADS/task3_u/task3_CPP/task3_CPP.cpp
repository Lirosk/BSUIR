#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;

signed long long res;
unsigned m = 1e9 + 7;

int mod()
{
    int ret = res % m;
    if (ret < 0)
    {
        ret += m;
    }
    return ret;
}

signed long long mul(int* nums, short s, short f)
{
    signed long long ret = 1;
    int i = s;
    while (i < f)
    {
        ret *= nums[i];
        i++;
    }
    return ret;
}

int main()
{
    short n, k;

    cin >> n >> k;

    int* nums = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }


    std::sort(nums, nums + n);

    if (k == 1)
    {
        res = nums[n - 1];
        cout << mod();
        exit(0);
    }
    else if (k == n)
    {
        res = mul(nums, 0, n);
        cout << mod();
        exit(0);
    }

    
    short l = 1;
    short r = n + 1 - k;
    signed long long b;


    res = mul(nums, n - k, n);        


    while (r != n + 1)
    {
        b = mul(nums, 0, l);
        
        if (r < n)
        {
            b *= mul(nums, r, n);
        }

        if (b > res)
        {
            res = b;
        }

        r++;
        l++;
    }

    cout << mod();
}
