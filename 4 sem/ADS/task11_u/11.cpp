#include <stdio.h>

int res = 0;
int n;

void cl(int i, int path, bool* checked, int** r);

int main()
{
    int i, j, w;
    scanf("%d", &n);

    int** r = new int*[n];
    for (i = 0; i < n; i ++)
    {
        r[i] = new int[n];
        for (j = 0; j < n; j ++)
        {
            r[i][j] = 0;
        }
    }

    for (int _ = 0; _ < n - 1; _++)
    {
        scanf("%d %d %d", &i, &j, &w);

        i--;
        j--;

        r[i][j] = w;
        r[j][i] = w;
    }

    bool* checked = new bool[n];
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j++)
        {
            checked[j] = false;
        }
        cl(i, 0, checked, r);
    }
    delete[] checked;

    printf("%d", res);
}

void cl(int i, int path, bool* checked, int** r)
{
    checked[i] = true;

    for (int j = 0; j < n; j ++)
    {
        if (checked[j])
        {
            continue;
        }
        if (r[i][j])
        {
            res += path + r[i][j];
            cl(j, path + r[i][j], checked, r);
        }
    }
}
