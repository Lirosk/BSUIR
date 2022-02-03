#include <iostream>
using namespace std;

int n, m;
int *res;
int rc;
int t;
void print(int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool ij_borders(int i, int j)
{
    return (i != 0) && (i != n - 1) && (j != 0) && (j != m - 1);
}

void set_stable(int **stable, int **land)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((i == 0 || i == n - 1) || (j == 0 || j == m - 1))
            {
                stable[i][j] = false;
                continue;
            }

            if (
                (land[i][j] < land[i - 1][j] || ((land[i][j] == land[i - 1][j]) && ij_borders(i - 1, j))) &&
                (land[i][j] < land[i][j - 1] || ((land[i][j] == land[i][j - 1]) && ij_borders(i, j - 1))) &&
                (land[i][j] < land[i + 1][j] || ((land[i][j] == land[i + 1][j]) && ij_borders(i + 1, j))) &&
                (land[i][j] < land[i][j + 1] || ((land[i][j] == land[i][j + 1]) && ij_borders(i, j + 1))))
            {
                stable[i][j] = 1;
                //res[rc] += 1;
                continue;
            }

            stable[i][j] = 0;
        }
    }
}

int main()
{
    cin >> t;
    // t = 1;
    res = new int[t];
    rc = 0;

    for (int __ = 0; __ < t; __++, rc++)
    {
        res[rc] = 0;
        cin >> n >> m;

        int **land = new int *[n];
        int **stable = new int *[n];
        for (int i = 0; i < n; i++)
        {
            stable[i] = new int[m];
            land[i] = new int[m];
        }
        // srand(time(0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> land[i][j];
                // land[i][j] = rand() % 15;
                // cout << land[i][j] << '\t';
            }
            // cout << "\n";
        }

        set_stable(stable, land);

        // cout << "\n";
        // print(stable);
        // cout << "\n";

        int max = n;
        if (m > n)
        {
            max = m;
        }
        int min;
        int *c;
        int *u;
        int *d;
        int *l;
        int *r;
        int *cs;
        bool no_changes = true;

        for (int k = 0; k < max; k++)
        {
            no_changes = true;
            for (int i = 1; i < n - 1; i++)
            {
                for (int j = 1; j < m - 1; j++)
                {
                    cs = &stable[i][j];
                    c = &land[i][j];
                    u = &land[i + 1][j];
                    d = &land[i - 1][j];
                    l = &land[i][j - 1];
                    r = &land[i][j + 1];

                    if (*cs)
                    {
                        min = *r;
                        if (*l < min)
                        {
                            min = *l;
                        }
                        if (*d < min)
                        {
                            min = *d;
                        }
                        if (*u < min)
                        {
                            min = *u;
                        }
                        min -= (*c + *cs - 1);
                        if (min > 0)
                        {
                            *cs += min;
                            no_changes = false;
                            res[rc] += min;
                        }
                    }

                    if (stable[i + 1][j])
                    {
                        if (
                            ((stable[i][j - 1] ? stable[i][j - 1] + *l : *l) - *c - *cs > 0) &&
                            ((stable[i - 1][j] ? stable[i - 1][j] + *d : *d) - *c - *cs > 0) &&
                            ((stable[i][j + 1] ? stable[i][j + 1] + *r : *r) - *c - *cs > 0))
                        {
                            // stable[i + 1][j] += 1;
                            *cs += 1;
                            res[rc] += 1; // 2;
                            no_changes = false;
                        }
                    }
                    if (stable[i][j + 1])
                    {
                        if (
                            ((stable[i][j - 1] ? stable[i][j - 1] + *l : *l) - *c - *cs > 0) &&
                            ((stable[i + 1][j] ? stable[i + 1][j] + *u : *u) - *c - *cs > 0) &&
                            ((stable[i - 1][j] ? stable[i - 1][j] + *d : *d) - *c - *cs > 0))
                        {
                            // stable[i][j + 1] += 1;
                            *cs += 1;
                            res[rc] += 1; // 2;
                            no_changes = false;
                        }
                    }
                    if (stable[i - 1][j])
                    {
                        if (
                            ((stable[i][j - 1] ? stable[i][j - 1] + *l : *l) - *c - *cs > 0) &&
                            ((stable[i + 1][j] ? stable[i + 1][j] + *u : *u) - *c - *cs > 0) &&
                            ((stable[i][j + 1] ? stable[i][j + 1] + *r : *r) - *c - *cs > 0))
                        {
                            // stable[i - 1][j] += 1;
                            *cs += 1;
                            res[rc] += 1; // 2;
                            no_changes = false;
                        }
                    }
                    if (stable[i][j - 1])
                    {
                        if (
                            ((stable[i][j + 1] ? stable[i][j + 1] + *r : *r) - *c - *cs > 0) &&
                            ((stable[i - 1][j] ? stable[i - 1][j] + *d : *d) - *c - *cs > 0) &&
                            ((stable[i + 1][j] ? stable[i + 1][j] + *u : *u) - *c - *cs > 0))
                        {
                            // stable[i][j - 1] += 1;
                            *cs += 1;
                            res[rc] += 1; // 2;
                            no_changes = false;
                        }
                    }
                }
            }

            // print(stable);
            // cout << "\n";

            if (no_changes)
            {
                break;
            }
        }

        // print(stable);
        // cout << "\n";

        for (int i = 0; i < t; i++)
        {
            cout << res[i] << "\n";
        }

        // delete c;
        // delete u;
        // delete d;
        // delete l;
        // delete r;
        // delete cs;

        for (int i = 0; i < n; i++)
        {
            delete[] stable[i];
            delete[] land[i];
        }
        // delete res
        delete[] stable;
        delete[] land;
    }

    return 0;
}
/*
1
3 6
3 3 4 4 4 2
3 1 3 1 1 4
7 3 1 6 4 1

*/