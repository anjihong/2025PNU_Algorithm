#include <bits/stdc++.h>

using namespace std;
int n;
vector<int> row, col, diagR, diagL;       // 입력
vector<int> r(10), c(10), dR(19), dL(19); // 현재 상태
vector<vector<bool>> grid;

void input(vector<int> &v, int n)
{
    v.resize(n);
    for (int &x : v)
        cin >> x;
}

void dfs(int idx)
{
    if (idx == n * n)
    {
        for (int i = 0; i < 2 * n - 1; i++)
            if (dR[i] != diagR[i] || dL[i] != diagL[i])
                return;
        for (auto &c : grid)
        {
            for (bool e : c)
            {
                cout << (e ? "B " : "- ");
            }
            cout << '\n';
        }
        exit(0);
    }

    int i = idx / n, j = idx % n, dl = i + j, dr = i - j + n - 1;

    for (int v = 0; v < 2; v++)
    {
        int tempR = r[i], tempC = c[j], tempDR = dR[dr], tempDL = dL[dl];
        if (v)
        {
            r[i]++;
            c[j]++;
            dR[dr]++;
            dL[dl]++;
        }
        bool check = r[i] <= row[i] && c[j] <= col[j] &&
                     dR[dr] <= diagR[dr] && dL[dl] <= diagL[dl] &&
                     (j < n - 1 || r[i] == row[i]) && (i < n - 1 || c[j] == col[j]);
        if (check)
        {
            grid[i][j] = v;
            dfs(idx + 1);
        }
        r[i] = tempR;
        c[j] = tempC;
        dR[dr] = tempDR;
        dL[dl] = tempDL;
    }
}

int main()
{
    // ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    input(col, n);
    input(row, n);
    input(diagR, 2 * n - 1);
    input(diagL, 2 * n - 1);

    grid.resize(n, vector<bool>(n, 0));
    dfs(0);
}