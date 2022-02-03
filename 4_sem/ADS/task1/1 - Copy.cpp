#include <stdio.h>
#include <vector>

using std::vector;

vector<vector<bool>> d(vector<vector<bool>>* v);
void cl(int i, vector<bool>* comp, vector<bool>* c, vector <vector<bool>>* v);

int N; // 1 <= N <= 1e4

int main()
{
    int M; // 0 <= M <= 1e5
    scanf("%d %d", &N, &M);

    // vector
    vector<vector<bool>> v(N, vector<bool>(N, false));

    int i = 0;
    int j = 0;

    for (int k = 0; k < M; k++)
    {
        scanf("%d %d", &i, &j);
        i--;
        j--;
        v[i][j] = true;
        v[j][i] = true;
    }

    auto comps = d(&v);
    int res = comps.size() - 1;
    printf("%d", res);
    printf("\nPress enter...");
    scanf("%d");
}

vector<vector<bool>> d(vector<vector<bool>>* v)
{
    vector<vector<bool>> comps; // connectivity components
    int ccomps = 0; // counter of comps
    vector<bool> c(N, false); // checked

    for (int i = 0; i < N; i++)
    {
        if (c[i])
        {
            continue;
        }

        c[i] = true;

        comps.push_back(vector<bool>(N, false));
        comps[ccomps][i] = true;

        for (int j = i + 1; j < N; j++)
        {
            if (c[j])
            {
                continue;
            }
            if ((*v)[i][j])
            {
                comps[ccomps][j] = true;
                cl(j, &comps[ccomps], &c, v);
            }
        }

        ccomps++;
    }

    return comps;
}

//check line
void cl(int i, vector<bool>* comp, vector<bool>* c, vector <vector<bool>>* v)
{
    (*c)[i] = true;
    for (int j = 0; j < N; j++)
    {
        if ((*c)[j])
        {
            continue;
        }
        if ((*v)[i][j])
        {
            (*comp)[j] = true;
            cl(j, comp, c, v);
        }
    }
}
