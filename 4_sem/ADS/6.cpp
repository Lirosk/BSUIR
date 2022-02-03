#include <iostream>

using std::cin;
using std::cout;

void print(const int* arr, const int& n)
{
    for (int i = 0; i < n; i ++)
    {
        cout << arr[i] << ' ';
    }
}

int main()
{
    int n, m;
    int i, j, k, v;

    cin >> n >> m;

    int** arr = new int*[n];
    for (i = 0; i < n; i++)
    {
        arr[i] = new int[m];
        for (j = 0; j < m; j++)
        {
            arr[i][j] = 0;
        }
    }    

    for (int _ = 0; _ < m; _++)
    {
        cin >> i >> j >> v;
        i--;
        j--;


    }


    for (i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

// 0 0 0 0 0
// 1 0 0 1 0
// 1 0 1 1 1
// 1 2 2 1 1
// 4 4 2 1 1

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// 1 1               |   .   |   .
//   1             1 |   .   |   .
//   2 2             |   .   |   .
//         4     4   |   .   |   .
// 1         1       |   .   |   .
// 1       1         |   .   |   .
//               1 1 |   .   |   .
//             4 4   |   .   |   .
//                   4   .   4   .
//                       4       4


